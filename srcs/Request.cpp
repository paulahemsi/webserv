/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:57:45 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/09 22:43:33 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

#define SP		" "
#define CRLF	"\r\n"

ft::Request::Request(const ft::Request& other)
{
	*this = other;
}

ft::Request::Request(void)
{
	return ;
}

#include "receive_line.hpp"

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

#include "RequestProcessor.hpp"
void ft::Request::_parse_body(void)
{
	if (this->_has_no_body())
		return;
	if (this->_request["Transfer-Encoding:"] == "chunked")
		_receive_chunked_body();
	else if (this->_has("Content-Length:"))
		_read_message_body();
	this->_request.insert(ft::request_pair("Body:", this->_body));
	
	std::string file_name = "./www/uploads/files/default";
	this->_request["filename:"] = file_name;
	std::ofstream new_file(file_name);
	new_file << this->_body;
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
	int			ret;
	char		buffer[20] = {0};
	std::string temp_line;

	length = _get_body_message_length();
	
	while (length && (ret = recv(this->_client_fd, buffer, 20, 0)) > 0)
	{
		length -= ret;
		temp_line += buffer;
		memset(buffer, 0, 20);
	}
	
	this->_body = temp_line;
}

int ft::Request::_get_body_message_length(void)
{
	std::string	length;

	length = this->_request["Content-Length:"];
	return(atoi(length.c_str()));
}

#include "receive_line.hpp"

void ft::Request::_receive_chunked_body(void)
{
	receive_line(this->_client_fd, this->_body, CRLF);

	//size_t index_begin =  this->_body.find("filename=\"");
	//if (index_begin == std::string::npos)
	//{
	//	std::cout << this->_body << std::endl;
	//	std::cout << "500" << std::endl;//throw (ft::RequestProcessor::InternalServerError());
	//	return ;
	//}
		
	//index_begin += 10;
	//size_t index_end = this->_body.find("\"", index_begin);
	std::string file_name = "./www/uploads/files/default";
	this->_request["filename:"] = file_name;
	//file_name += this->_body.substr(index_begin, index_end - index_begin);
	//this->_body.erase(0, (this->_body.find("\r\n\r\n") + 4));
	//this->_body.erase((this->_body.rfind("\r\n")), this->_body.length());
	//this->_body.erase((this->_body.rfind("\r\n")), this->_body.length());
	std::ofstream new_file;

	//std::size_t pos = request_string.find("\r\n\r\n");
	//std::string value = request_string.substr(pos + 4, std::string::npos);
}

std::string ft::Request::get_request_field(std::string key)
{
	return (this->_request[(key + ":")]);
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
		throw (BadRequest());
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
