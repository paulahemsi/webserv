/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:57:45 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/09 00:11:59 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

ft::Request::Request(const ft::Request& other)
{
	*this = other;
}

ft::Request::Request(void)
{
	return ;
}

void ft::Request::init(std::string request_string, int client_fd)
{
	std::stringstream request_(request_string);
	std::string line;
	std::getline(request_, line, '\r');
	this->_parse_request_line(line);
	this->_parse_header(request_);
	this->_parse_body(request_string, client_fd);
}

void ft::Request::_parse_request_line(std::string request_line)
{
	std::string field[3] = { "Method:", "URI:", "Protocol-Version:" };

	for (std::size_t i = 0; i < 3; i++)
	{
		std::size_t pos = request_line.find(' ');
		std::string value = request_line.substr(0, pos);
		this->_request.insert(ft::request_pair(field[i], value));
		request_line.erase(0, pos + 1);
	}
}

void ft::Request::_parse_header(std::stringstream &header)
{
	for (std::string line; line != "\n"; std::getline(header, line, '\r'))
	{
		std::size_t pos = line.find(' ');
		std::string key = line.substr(0, pos);
		std::string value = line.substr(pos + 1, std::string::npos);
		this->_request.insert(ft::request_pair(key, value));
	}
}

#include "RequestProcessor.hpp"
void ft::Request::_parse_body(std::string request_string, int client_fd)
{
	//int bytes_received;
	char buffer[1];

	this->_body = request_string;
	while (recv(client_fd, buffer, 1, MSG_DONTWAIT) > 0)
		this->_body += buffer;

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
	this->_request.insert(ft::request_pair("Body:", this->_body));
}

std::string ft::Request::get_request_field(std::string key)
{
	return (this->_request[(key + ":")]);
}

std::string ft::Request::get_server_name(void)
{
	std::string host = get_request_field("\nHost");
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
