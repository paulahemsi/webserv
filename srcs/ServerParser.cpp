/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:50:18 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/21 21:38:49 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerParser.hpp"

ft::ServerParser::ServerParser(void)
{
	return ;
}

ft::ServerParser::~ServerParser(void)
{
	return ;
}

ft::ServerParser::ServerParser(ft::ServerParser const &other)
{
	*this = other;
}

ft::ServerParser &ft::ServerParser::operator=(ft::ServerParser const &right_hand_side)
{
	this->_server = right_hand_side._server;
	this->_line = right_hand_side._line;
	return (*this);
}

void ft::ServerParser::exec(std::ifstream &file_stream, std::string line)
{
	this->_line = line;
	while (file_stream.good())
	{
		std::getline(file_stream, this->_line);
		if (ft::line_is_valid(this->_line))
		{
			if (this->_line == SERVER_END)
				return ;
			if (ft::begins_with(this->_line, LOCATION_BEGIN))
				_parse_location_block(file_stream);
			else
				_set_server_conf();
		}
	}
}

ft::ServerData ft::ServerParser::get_server(void)
{
	return (this->_server);
}

void ft::ServerParser::_parse_location_block(std::ifstream &file_stream)
{
	ft::LocationParser new_location;

	new_location.exec(file_stream, this->_line);
	this->_server.add_location(new_location.get_location());
}

void ft::ServerParser::_set_server_conf()
{
	if (ft::begins_with(this->_line, LISTEN))
		_check_listen_conf();
	else if (ft::begins_with(this->_line, SERVER_NAME))
		_set_server_name_conf();
	else if (ft::begins_with(this->_line, ROOT))
		_set_root_conf();
	else if (ft::begins_with(this->_line, ERROR_PAGE))
		_set_error_page_conf();
	else if (ft::begins_with(this->_line, CGI))
		_set_cgi_conf();
	else if (ft::begins_with(this->_line, BODY_SIZE))
		_set_body_size_conf();
	else
		throw (ServerConfigurationError());
}


void ft::ServerParser::_check_listen_conf()
{
	ft::Listen listen;

	ft::reduce_to_value(this->_line, LISTEN);
	
	if (this->_server.has_listen_set())
		throw (ServerConfigurationError());
	if (this->_line.empty())
		throw (ServerConfigurationError());
	if (ft::more_than_one_argument(this->_line))
		throw (ServerConfigurationError());
	if (this->_line.find(":") == std::string::npos)
		_set_port_conf(listen, this->_line);
	else
		_set_listen_conf(listen);
	this->_server.set_listen(listen);
}

void ft::ServerParser::_set_listen_conf(ft::Listen &listen)
{
	std::stringstream host_port(this->_line);
	std::string host;
	std::string port;
	std::getline(host_port, host, ':');
	listen.set_host(host);
	std::getline(host_port, port);
	_set_port_conf(listen, port);
}

void ft::ServerParser::_set_port_conf(ft::Listen &listen, std::string port)
{
	if (ft::is_number(port))
		listen.set_port(atoi(port.c_str()));
	else
		throw (ServerConfigurationError());
}

void ft::ServerParser::_set_server_name_conf()
{
	ft::reduce_to_value(this->_line, SERVER_NAME);

	if (this->_server.has_server_name_set())
		throw (ServerConfigurationError());
	if (this->_line.empty())
		throw (ServerConfigurationError());
	std::stringstream server_name_line(this->_line);
	std::string server_name_value;
	while (server_name_line.good())
	{
		std::getline(server_name_line, server_name_value, ' ');
		this->_server.add_server_name(server_name_value);
	}
}

void ft::ServerParser::_set_root_conf()
{
	ft::reduce_to_value(this->_line, ROOT);
	
	if (this->_server.has_root_set())
		throw (ServerConfigurationError());
	if (this->_line.empty())
		throw (ServerConfigurationError());
	if (ft::more_than_one_argument(this->_line))
		throw (ServerConfigurationError());
	this->_server.set_root(this->_line);
}

void ft::ServerParser::_set_error_page_conf()
{
	ft::reduce_to_value(this->_line, ERROR_PAGE);
	if (!ft::more_than_one_argument(this->_line))
		throw (ServerConfigurationError());

	size_t				pos = this->_line.find_last_of(' ');
	std::string 		page_path = this->_line.substr(pos + 1);
	std::string			codes= this->_line.substr(0, pos);
	ft::trim(codes, " \t");

	std::stringstream 	ss_codes(codes);
	std::string 		code;
	while (ss_codes.good())
	{
		std::getline(ss_codes, code, ' ');
		this->_server.add_error_page(code, page_path);
	}
}

void ft::ServerParser::_set_cgi_conf()
{
	ft::reduce_to_value(this->_line, CGI);
	if (!ft::more_than_one_argument(this->_line))
		throw (ServerConfigurationError());

	std::stringstream cgi_line(this->_line);
	std::string extension;
	std::string path;

	for (size_t i = 1; cgi_line.good(); i++)
	{
		switch (i)
		{
		case 1:
			std::getline(cgi_line, extension, ' ');
			break;
		case 2:
			std::getline(cgi_line, path, ' ');
			break;
		case 3:
			throw (ServerConfigurationError());
		}
	}
	this->_server.add_cgi_conf(extension, path);
}

void ft::ServerParser::_set_body_size_conf()
{
	ft::reduce_to_value(this->_line, BODY_SIZE);
	
	if (this->_line.empty())
		throw (ServerConfigurationError());
	if (ft::more_than_one_argument(this->_line))
		throw (ServerConfigurationError());
	if (ft::is_number(this->_line))
		this->_server.set_body_size(atoi(this->_line.c_str()));
	else
		throw (ServerConfigurationError());
}
