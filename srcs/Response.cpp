/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:41:10 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/27 21:11:26 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

#define HELLO_WORLD	"<html>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>\n"

ft::Response::Response(void):	_http_version("HTTP/1.1"),
								_status_code(200),
								_reason_phrase("OK"),
								_header(),
								_body(HELLO_WORLD)
{
	this->_header["Date"] = "Mon, 27 Jul 2009 12:28:53 GMT";
	this->_header["Server"] = "webserv";
	this->_header["Last-Modified"] = "Wed, 22 Jul 2009 19:15:56 GMT";
	this->_header["Content-Length"] = "53";
	this->_header["Content-Type"] = "text/html";
	this->_header["Connection"] = "close";
	this->_header["Accept-Ranges"] = "bytes";
	return ;
}

ft::Response::~Response(void)
{
	return ;
}

std::string ft::Response::_header_to_string(void)
{
	std::string					header;
	ft::header_map::iterator	it = this->_header.begin();

	while (it != this->_header.end())
	{
		header += it->first + ": " + it->second + CRLF;
		it++;
	}
	return (header);
}

std::string ft::Response::_int_to_string(int integer)
{
	std::stringstream str_stream;

	str_stream << integer;
	return (str_stream.str());
}

std::string ft::Response::_to_string(void)
{
	std::string status_line;
	std::string header;

	status_line = this->_http_version + SP
				+ _int_to_string(this->_status_code) + SP
				+ this->_reason_phrase + CRLF;
	header = _header_to_string();
	return (status_line + header + CRLF + this->_body );
}

void	ft::Response::set_header_field(std::string key, std::string value)
{
	this->_header[key] = value;
}

void	ft::Response::set_status_code(unsigned int stauts_code)
{
	this->_status_code = stauts_code;
}

void	ft::Response::set_reason_phrase(std::string reason)
{
	this->_reason_phrase = reason;
}

void	ft::Response::set_body(std::string body)
{
	this->_body = body;
}

void	ft::Response::set_content_length(unsigned int length)
{
	this->_header["Content-Length"] = _int_to_string(length);
}

void	ft::Response::send(int client)
{
	std::string response;

	response = this->_to_string();
	write(client, response.c_str(), response.length());
}

void	ft::Response::show(void)
{
	std::cout << this->_to_string();
}
