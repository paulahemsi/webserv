/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:47:31 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/19 09:42:27 by phemsi-a         ###   ########.fr       */
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
	ft::LocationData new_location;

	_set_prefix(new_location);
	while (this->_file_stream.good())
	{
		std::getline(this->_file_stream, this->_line);
		if (ft::is_not_empty(this->_line))
		{
			if (this->_line == LOCATION_END)
			{
				server.set_location(new_location);
				return ;
			}
			_set_location_conf(new_location);
		}
	}
}

void ft::Parser::_set_location_conf(ft::LocationData &location)
{
	if (ft::begins_with(this->_line, ACCEPTED_METHODS))
		_set_accepted_methods_conf(location);
	else if (ft::begins_with(this->_line, INDEX))
		_set_index_conf(location);
	else if (ft::begins_with(this->_line, REDIRECTION))
		_set_redirection_conf(location);
	else if (ft::begins_with(this->_line, ROOT))
		_set_root_conf(location);
	else if (ft::begins_with(this->_line, AUTOINDEX))
		_set_autoindex_conf(location);
	else if (ft::begins_with(this->_line, BODY_SIZE))
		_set_body_size_conf(location);
	else
		throw (LocationConfigurationError());
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
	ft::check_if_only_one_argument(this->_line);
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
	ft::check_if_only_one_argument(this->_line);
	server.set_root(this->_line);
}

void ft::Parser::_set_error_page_conf(ft::ServerData &server)
{
	ft::reduce_to_value(this->_line, ERROR_PAGE);
	ft::check_if_only_one_argument(this->_line);
	server.set_error_pages(this->_line);
}

void ft::Parser::_set_body_size_conf(ft::ServerData &server)
{
	ft::reduce_to_value(this->_line, BODY_SIZE);
	ft::check_if_only_one_argument(this->_line);
	if (ft::is_number(this->_line))
		server.set_body_size(atoi(this->_line.c_str()));
	else
		throw (ServerConfigurationError());
}

void ft::Parser::_set_prefix(ft::LocationData &location)
{
	ft::reduce_to_value(this->_line, LOCATION_BEGIN);

	std::stringstream location_line(this->_line);
	std::string splited;

	std::getline(location_line, splited, ' ');
	location.set_prefix(splited);
	std::getline(location_line, splited, ' ');
	splited.erase(splited.find_last_not_of(" \t") + 1);
	if (splited != "{")
		throw (LocationConfigurationError());
}

void ft::Parser::_set_body_size_conf(ft::LocationData &location)
{
	ft::reduce_to_value(this->_line, BODY_SIZE);
	ft::check_if_only_one_argument(this->_line);
	if (ft::is_number(this->_line))
		location.set_body_size(atoi(this->_line.c_str()));
	else
		throw (LocationConfigurationError());
}

void ft::Parser::_set_root_conf(ft::LocationData &location)
{
	ft::reduce_to_value(this->_line, ROOT);
	ft::check_if_only_one_argument(this->_line);
	location.set_root(this->_line);
}

void ft::Parser::_set_index_conf(ft::LocationData &location)
{
	ft::reduce_to_value(this->_line, INDEX);

	std::stringstream index_line(this->_line);
	std::string index_value;
	while (index_line.good())
	{
		std::getline(index_line, index_value, ' ');
		location.add_index(index_value);
	}
}

void ft::Parser::_set_redirection_conf(ft::LocationData &location)
{
	ft::reduce_to_value(this->_line, REDIRECTION);
	ft::check_if_only_one_argument(this->_line);
	location.set_redirection(this->_line);
}

void ft::Parser::_set_autoindex_conf(ft::LocationData &location)
{
	ft::reduce_to_value(this->_line, AUTOINDEX);
	if (this->_line == "on")
		location.set_autoindex(true);
	else if (this->_line == "off")
		location.set_autoindex(false);
	else
		throw (LocationConfigurationError());
}

void ft::Parser::_set_accepted_methods_conf(ft::LocationData &location)
{
	ft::reduce_to_value(this->_line, ACCEPTED_METHODS);
	
	std::stringstream accepted_methods_line(this->_line);
	std::string accepted_methods_value;
	while (accepted_methods_line.good())
	{
		std::getline(accepted_methods_line, accepted_methods_value, ' ');
		location.add_accepted_method(accepted_methods_value);
	}
}

std::vector<ft::ServerData> ft::Parser::get_servers(void)
{
	return (this->_servers);
}
