/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:41:10 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/18 23:53:36 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

ft::Response::Response(void):	_http_version("HTTP/1.1"),
								_status_code("200"),
								_reason_phrase("OK"),
								_header(),
								_body("")
{
	this->_header["Server"] = "webserv";
	this->_header["Content-Length"] = "0";
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

std::string ft::Response::_to_string(void)
{
	std::string status_line;
	std::string header;

	status_line = this->_http_version + SP
				+ this->_status_code + SP
				+ this->_reason_phrase + CRLF;
	header = _header_to_string();
	return (status_line + header + CRLF + this->_body );
}

void	ft::Response::set_header_field(std::string key, std::string value)
{
	this->_header[key] = value;
}

void	ft::Response::set_status_code(std::string stauts_code)
{
	this->_status_code = stauts_code;
}

void	ft::Response::set_reason_phrase(std::string reason)
{
	this->_reason_phrase = reason;
}

void	ft::Response::_set_body(std::string body)
{
	this->_body = body;
}

void	ft::Response::_set_body_type(std::string path)
{
	if (path.find(".jpg") != std::string::npos)
		this->_set_content_type("jpg");
	if (path.find(".css") != std::string::npos)
		this->_set_content_type("text/css");
}

void	ft::Response::_set_content_length(unsigned int length)
{
	this->_header["Content-Length"] = int_to_string(length);
}

void	ft::Response::_set_content_type(std::string type)
{
	this->_header["Content-Type"] = type;
}

void	ft::Response::_set_current_date(void)
{
	this->_header["Date"] = current_date_time(); 
}

void	ft::Response::_set_last_modified(std::string path)
{
	this->_header["Last-Modified"] = last_modification_time(path);
}

void	ft::Response::send(int client)
{
	std::string response;

	_set_current_date();
	response = this->_to_string();
	if (write(client, response.c_str(), response.length()) == ERROR)
		throw (std::exception());
}

void	ft::Response::show(void)
{
	std::cout << this->_to_string();
}

void	ft::Response::build_body(std::string body, std::string path)
{
	this->_set_body(body);
	this->_set_content_length(body.length());
	this->_set_last_modified(path);
	_set_body_type(path);
}

void	ft::Response::build_body(std::string body)
{
	this->_set_body(body);
	this->_set_content_length(body.length());
}
