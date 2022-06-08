/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:41:10 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/08 03:04:00 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

#define HELLO_WORLD	"<html><body><h1>Hello, World!</h1></body></html>"

ft::Response::Response(void):	_http_version("HTTP/1.1"),
								_status_code(200),
								_reason_phrase("OK"),
								_header(),
								_body(HELLO_WORLD)
{
	this->_header["Date"] = "Mon, 27 Jul 2009 12:28:53 GMT";
	this->_header["Server"] = "webserv";
	this->_header["Last-Modified"] = "Wed, 22 Jul 2009 19:15:56 GMT";
	this->_header["Content-Length"] = "88";
	this->_header["Content-Type"] = "text/html";
	this->_header["Connection"] = "Closed";
	return ;
}

ft::Response::~Response(void)
{
	return ;
}

std::string ft::Response::_headerToString(void)
{
	std::string					header;
	ft::header_map::iterator	it = this->_header.begin();

	while (it != this->_header.end())
	{
		header += it->first + ": " + it->second + '\n';
		it++;
	}
	return (header);
}

std::string ft::Response::toString(void)
{
	std::stringstream status_code;
	std::string status_line;
	std::string header;

	status_code << this->_status_code;
	status_line = this->_http_version + SP
				+ status_code.str() + SP
				+ this->_reason_phrase + CRLF;
	header = _headerToString();
	return (status_line + header + CRLF + CRLF + this->_body );
}

void	ft::Response::send(int client)
{
	std::string response;

	response = this->toString();
	write(client, response.c_str(), response.length());
}