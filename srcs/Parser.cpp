/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:47:31 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/19 11:42:23 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

ft::Parser::Parser(void)
{
	return ;
}

ft::Parser::Parser(ft::Parser const &other)
{
	*this = other;
}

ft::Parser &ft::Parser::operator=(ft::Parser const &right_hand_side)
{
	this->_servers = right_hand_side._servers;
	return (*this);
}

ft::Parser::~Parser(void)
{
	_file_stream.close();
}

void ft::Parser::exec(const char* filename)
{
	this->_file_stream.open(filename, std::ifstream::in);
	if(!this->_file_stream)
		throw (OpenFileError());
	_parse_file();
}

void ft::Parser::_parse_file(void)
{
	while (this->_file_stream.good())
	{
		std::getline(this->_file_stream, this->_line);
		if (ft::is_not_empty(this->_line))
		{
			if (this->_line == SERVER_BEGIN)
				_parse_server_block();
			else
				throw (ServerConfigurationError());
		}
	}
}

void ft::Parser::_parse_server_block(void)
{
	ft::ServerData new_server;

	while (this->_file_stream.good())
	{
		std::getline(this->_file_stream, this->_line);
		if (ft::is_not_empty(this->_line))
		{
			if (this->_line == SERVER_END)
			{
				this->_servers.push_back(new_server);
				return ;
			}
			_set_server_conf(new_server);
		}
	}
}

void ft::Parser::_parse_location_block(ft::ServerData &server)
{
	ft::LocationParser new_location;

	new_location.exec(this->_file_stream, this->_line);
	server.set_location(new_location.get_location());
}

void ft::Parser::_set_server_conf(ft::ServerData &server)
{
	if (ft::begins_with(this->_line, LOCATION_BEGIN))
		_parse_location_block(server);
	else if (ft::begins_with(this->_line, LISTEN))
		_set_listen_conf(server);
	else if (ft::begins_with(this->_line, SERVER_NAME))
		_set_server_name_conf(server);
	else if (ft::begins_with(this->_line, ROOT))
		_set_root_conf(server);
	else if (ft::begins_with(this->_line, ERROR_PAGE))
		_set_error_page_conf(server);
	else if (ft::begins_with(this->_line, BODY_SIZE))
		_set_body_size_conf(server);
	else
		throw (ServerConfigurationError());
}

void ft::Parser::_set_listen_conf(ft::ServerData &server)
{
	ft::Listen listen;

	ft::reduce_to_value(this->_line, LISTEN);
	if (ft::more_than_one_argument(this->_line))
		throw (ServerConfigurationError());
	if (this->_line.find(":") == std::string::npos)
	{
		listen.set_port(this->_line);
	}
	else
	{
		std::stringstream host_port(this->_line);
		std::string host;
		std::string port;
		std::getline(host_port, host, ':');
		listen.set_host(host);
		std::getline(host_port, port);
		listen.set_port(port);
	}
	server.set_listen(listen);
}

void ft::Parser::_set_server_name_conf(ft::ServerData &server)
{
	ft::reduce_to_value(this->_line, SERVER_NAME);

	std::stringstream server_name_line(this->_line);
	std::string server_name_value;
	while (server_name_line.good())
	{
		std::getline(server_name_line, server_name_value, ' ');
		server.set_server_name(server_name_value);
	}
}

void ft::Parser::_set_root_conf(ft::ServerData &server)
{
	ft::reduce_to_value(this->_line, ROOT);
	if (ft::more_than_one_argument(this->_line))
		throw (ServerConfigurationError());
	server.set_root(this->_line);
}

void ft::Parser::_set_error_page_conf(ft::ServerData &server)
{
	ft::reduce_to_value(this->_line, ERROR_PAGE);
	if (ft::more_than_one_argument(this->_line))
		throw (ServerConfigurationError());
	server.set_error_pages(this->_line);
}

void ft::Parser::_set_body_size_conf(ft::ServerData &server)
{
	ft::reduce_to_value(this->_line, BODY_SIZE);
	if (ft::more_than_one_argument(this->_line))
		throw (ServerConfigurationError());
	if (ft::is_number(this->_line))
		server.set_body_size(atoi(this->_line.c_str()));
	else
		throw (ServerConfigurationError());
}

std::vector<ft::ServerData> ft::Parser::get_servers(void)
{
	return (this->_servers);
}
