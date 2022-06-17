/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:47:31 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/17 17:32:13 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

ft::Parser::Parser(void)
{
	return ;
}

ft::Parser::Parser(const char* filename)
{
	this->_file_stream.open(filename, std::ifstream::in);
	if(!this->_file_stream)
		throw (OpenFileError());
	_parse_file();
}

ft::Parser::~Parser(void)
{
	_file_stream.close();
}

static bool not_empty(std::string &line)
{
	line.erase(line.find_last_not_of(' ') + 1);
	line.erase(0, line.find_first_not_of(' '));
	return (line != "");
}

void ft::Parser::_parse_file(void)
{
	std::string line;
	while (this->_file_stream.good())
	{
		std::getline(this->_file_stream, line);
		if (not_empty(line))
		{
			if (line == SERVER_BEGIN)
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
		if (not_empty(this->_line))
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
	ft::LocationData location;

	while (this->_file_stream.good())
	{
		std::getline(this->_file_stream, this->_line);
		if (not_empty(this->_line))
		{
			if (this->_line == LOCATION_END)
			{
				server.set_location(location);
				return ;
			}
			_set_location_conf(location);
		}
	}
}

void ft::Parser::_set_location_conf(ft::LocationData &location)
{
	if (_line_begins_with(ACCEPTED_METHODS))
		_set_accepted_methods_conf(location);
	if (_line_begins_with(INDEX))
		_set_index_conf(location);
	else if (_line_begins_with(REDIRECTION))
		_set_redirection_conf(location);
	else if (_line_begins_with(ROOT))
		_set_root_conf(location);
	else if (_line_begins_with(AUTOINDEX))
		_set_autoindex_conf(location);
	else if (_line_begins_with(BODY_SIZE))
		_set_body_size_conf(location);
}

bool ft::Parser::_line_begins_with(const char *directive)
{
	return (this->_line.find(directive, 0) == 0);
}

void ft::Parser::_set_server_conf(ft::ServerData &server)
{
	if (_line_begins_with(LOCATION_BEGIN))
		_parse_location_block(server);
	else if (_line_begins_with(LISTEN))
		_set_listen_conf(server);
	else if (_line_begins_with(SERVER_NAME))
		_set_server_name_conf(server);
	else if (_line_begins_with(ROOT))
		_set_root_conf(server);
	else if (_line_begins_with(ERROR_PAGE))
		_set_error_page_conf(server);
	else if (_line_begins_with(BODY_SIZE))
		_set_body_size_conf(server);
	else
		throw (ServerConfigurationError());
}

void ft::Parser::_set_listen_conf(ft::ServerData &server)
{
	std::cout << "****************************" << LISTEN << std::endl;
}

void ft::Parser::_set_server_name_conf(ft::ServerData &server)
{
	std::cout << "****************************" << SERVER_NAME << std::endl;
}

void ft::Parser::_set_root_conf(ft::ServerData &server)
{
	std::cout << "****************************" << ROOT << std::endl;
}

void ft::Parser::_set_error_page_conf(ft::ServerData &server)
{
	std::cout << "****************************" << ERROR_PAGE << std::endl;
}

void ft::Parser::_set_body_size_conf(ft::ServerData &server)
{
	std::cout << "****************************" << BODY_SIZE << std::endl;
}

void ft::Parser::_set_body_size_conf(ft::LocationData &location)
{
	std::cout << "-----------------------" << BODY_SIZE << std::endl;
}

void ft::Parser::_set_root_conf(ft::LocationData &location)
{
	std::cout << "-----------------------" << ROOT << std::endl;
}

void ft::Parser::_set_index_conf(ft::LocationData &location)
{
	std::cout << "-----------------------" << INDEX << std::endl;
}

void ft::Parser::_set_redirection_conf(ft::LocationData &location)
{
	std::cout << "-----------------------" << REDIRECTION << std::endl;
}

void ft::Parser::_set_autoindex_conf(ft::LocationData &location)
{
	std::cout << "-----------------------" << AUTOINDEX << std::endl;
}

void ft::Parser::_set_accepted_methods_conf(ft::LocationData &location)
{
	std::cout << "-----------------------" << ACCEPTED_METHODS << std::endl;
}

std::vector<ft::ServerData> ft::Parser::get_servers(void)
{
	return (this->_servers);
}
