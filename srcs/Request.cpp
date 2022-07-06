/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:57:45 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/06 18:27:12 by lfrasson         ###   ########.fr       */
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

void ft::Request::init(std::string request_string)
{
	std::stringstream request_(request_string);
	std::string line;
	std::getline(request_, line, '\r');
	this->_parse_request_line(line);
	this->_parse_header(request_);
	this->_parse_body(request_string);
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

void ft::Request::_parse_body(std::string request_string)
{
	std::size_t pos = request_string.find("\r\n\r\n");
	std::string value = request_string.substr(pos + 4, std::string::npos);
	this->_request.insert(ft::request_pair("Body:", value));
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
