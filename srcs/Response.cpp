/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:41:10 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/07 02:54:47 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

#define HELLO_WORLD	"<html><body><h1>Hello, World!</h1></body></html>"

ft::Response::Response(void):	_http_version("HTTP/1.1"),
								_status_code(200),
								_reason_phrase("OK"),
								_body(HELLO_WORLD)
{
	return ;
}

ft::Response::~Response(void)
{
	return ;
}

std::string ft::Response::toString(void)
{
	std::stringstream status_code;
	std::string status_line;

	status_code << this->_status_code;
	status_line = this->_http_version + SP
				+ status_code.str() + SP
				+ this->_reason_phrase + CRLF;
	return (status_line + CRLF + this->_body );
}

void	ft::Response::send(int client)
{
	std::string response;

	response = this->toString();
	write(client, response.c_str(), response.length());
}