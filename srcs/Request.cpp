/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:57:45 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/18 23:42:02 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

#define SP				" "
#define CRLF			"\r\n"
#define CRLF_DOUBLE		"\r\n\r\n"
#define FILENAME_ID		"filename=\""
#define DOUBLE_QUOTE	"\""
#define BUFFER_SIZE		20

ft::Request::Request(const ft::Request& other)
{
	*this = other;
}

ft::Request::Request(void)
{
	return ;
}

void ft::Request::init(int client_fd)
{
	this->_client_fd = client_fd;
	this->_parse_request_line();
	this->_parse_header();
	this->_parse_body();
}

void ft::Request::_parse_request_line(void)
{
	std::string line;
	std::string field[3] = { "Method:", "URI:", "Protocol-Version:" };

	receive_line(this->_client_fd, line, CRLF);
	for (std::size_t i = 0; i < 3; i++)
	{
		std::size_t pos = line.find(SP);
		std::string value = line.substr(0, pos);
		this->_request.insert(ft::request_pair(field[i], value));
		line.erase(0, pos + 1);
	}
}

void ft::Request::_parse_header(void)
{
	std::string line;
	
	receive_line(_client_fd, line, CRLF);
	for (; line != CRLF && line != ""; receive_line(_client_fd, line, CRLF))
	{
		std::size_t pos = line.find(SP);
		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1, std::string::npos);
		this->_request.insert(ft::request_pair(key, value));
	}
}

void ft::Request::_parse_body(void)
{
	if (this->_has_no_body())
		return;
	if (this->get_request_field("Transfer-Encoding:") == "chunked")
		_receive_chunked_body();
	else if (this->_has("Content-Length:"))
		_read_message_body();
	this->_request.insert(ft::request_pair("Body:", this->_body));
}

bool ft::Request::_has_no_body(void)
{
	if (this->_has("Content-Length:"))
		return (false);
	if (this->_has("Transfer-Encoding:"))
		return (false);
	return (true);
}

void ft::Request::_read_message_body(void)
{
	int			length;
	ssize_t		num_of_bytes;
	char		buffer[BUFFER_SIZE] = {0};
	std::string temp_line;

	length = get_content_length();
	
	while (true)
	{
		if (!length)
			break;
		num_of_bytes = recv(this->_client_fd, buffer, BUFFER_SIZE, 0);
		if (num_of_bytes == ERROR)
			throw (std::exception());
		if (num_of_bytes == 0)
			break;
		length -= num_of_bytes;
		temp_line.append(buffer, num_of_bytes);
		memset(buffer, 0, BUFFER_SIZE);
	}
	this->_body = _extract_entity_body(temp_line);
}

std::string ft::Request::_extract_entity_body(std::string message_body)
{
	if (this->is_multipart_form_data())
	{
		_clean_header(message_body);
		_clean_footer(message_body);
	}
	return (message_body);
}

int ft::Request::get_content_length(void)
{
	std::string	length;

	length = this->_request["Content-Length:"];
	return(atoi(length.c_str()));
}

void ft::Request::_clean_header(std::string &temp_line)
{
	std::string header;
	header = temp_line.substr(0, temp_line.find(CRLF_DOUBLE));
	_parse_filename(header);
	temp_line.erase(0, header.length() + strlen(CRLF_DOUBLE));
}

void ft::Request::_clean_footer(std::string &temp_line)
{
	std::string footer;
	footer = temp_line.substr(temp_line.rfind(CRLF), temp_line.npos);
	temp_line.erase(temp_line.length() - footer.length(), temp_line.npos);
}

void ft::Request::_parse_filename(std::string header)
{
	std::string filename;
	size_t index_begin;
	size_t index_end;

	index_begin = header.find(FILENAME_ID) + strlen(FILENAME_ID);
	index_end = header.find(DOUBLE_QUOTE, index_begin);
	filename = header.substr(index_begin, (index_end - index_begin));
	this->_request["filename:"] = filename;
}

size_t ft::Request::_get_chunk_size(void)
{
	std::string line;
	std::size_t pos;

	receive_line(this->_client_fd, line, CRLF);
	if (line == "")
		return (0);
	pos = line.find(SP);
	return (_convert_chunk_size(line.substr(0, pos)));
}

size_t ft::Request::_convert_chunk_size(std::string chunk_size)
{
	std::size_t			size;
	std::stringstream	s_stream(chunk_size);

	s_stream >> std::hex >> size;
	return (size);
}

void ft::Request::_receive_chunked_body(void)
{
	int			length = 0;
	std::string temp_line;
	std::size_t chunk_size;

	chunk_size = _get_chunk_size();	
	while (chunk_size > 0)
	{
		receive_line(this->_client_fd, temp_line, CRLF);
		this->_body += temp_line;
		length += chunk_size;
		receive_line(this->_client_fd, temp_line, CRLF);
		chunk_size = _get_chunk_size();
    }
	this->_request["Content-Length:"] = int_to_string(length);
}

std::string ft::Request::get_request_field(std::string key)
{
	if (this->_has(key + ":"))
		return (this->_request[(key + ":")]);
	return ("");
}

std::string ft::Request::get_server_name(void)
{
	std::string host = get_request_field("Host");
	return (host.substr(0, host.find(':')));
}

std::map<std::string, std::string> ft::Request::get_request(void) const
{
	return (this->_request);
}

std::string	ft::Request::get_method(void)
{
	return (get_request_field("Method"));
}

ft::Request& ft::Request::operator= (const Request& other)
{
	this->_request = other._request;
	return (*this);
}

ft::Request::~Request(void)
{
	return ;
}

void	ft::Request::check_request(void)
{
	if (!_has_mandatory_fields())
		throw (ft::BadRequest());
}

bool ft::Request::is_multipart_form_data(void)
{
	std::string content_type;
	content_type = this->get_request_field("Content-Type");
	return (content_type.find("multipart/form-data") != std::string::npos);
}

bool	ft::Request::_has_mandatory_fields(void)
{
	if (!_has("Method:") ||
		!_has("URI:") ||
		!_has("Protocol-Version:"))
		return (false);
	return (true);
}

bool	ft::Request::_has(std::string key)
{
	return (this->_request.find(key) != this->_request.end());
}

std::ostream &operator<<(std::ostream &outputFile, const ft::Request &object)
{
	std::map<std::string, std::string> request = object.get_request();
	std::map<std::string, std::string>::iterator it = request.begin();
	while (it != request.end())
	{
		outputFile << it->first << " " << it->second << std::endl;
		it++;
	}
	return (outputFile);
}
