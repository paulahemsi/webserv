/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:47:31 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/17 21:52:04 by phemsi-a         ###   ########.fr       */
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

void ft::Parser::_trim_line(const std::string chars_to_trim)
{
	this->_line.erase(this->_line.find_last_not_of(chars_to_trim) + 1);
	this->_line.erase(0, this->_line.find_first_not_of(chars_to_trim));
}

bool ft::Parser::_line_is_not_empty(void)
{
	_trim_line(" \t");
	return (this->_line != "");
}

bool ft::Parser::_line_is_number(void)
{
	return (this->_line.find_first_not_of("0123456789") == std::string::npos);
}

bool ft::Parser::_line_begins_with(const char *directive)
{
	return (this->_line.find(directive, 0) == 0);
}

void ft::Parser::_parse_file(void)
{
	while (this->_file_stream.good())
	{
		std::getline(this->_file_stream, this->_line);
		if (_line_is_not_empty())
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
		if (_line_is_not_empty())
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
		if (_line_is_not_empty())
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
	else if (_line_begins_with(INDEX))
		_set_index_conf(location);
	else if (_line_begins_with(REDIRECTION))
		_set_redirection_conf(location);
	else if (_line_begins_with(ROOT))
		_set_root_conf(location);
	else if (_line_begins_with(AUTOINDEX))
		_set_autoindex_conf(location);
	else if (_line_begins_with(BODY_SIZE))
		_set_body_size_conf(location);
	else
		throw (LocationConfigurationError());
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

void ft::Parser::_reduce_line_to_value(const char *directive)
{
	this->_line.erase(0, strlen(directive));
	_trim_line(" \t");
}

void ft::Parser::_set_body_size_conf(ft::LocationData &location)
{
	_reduce_line_to_value(BODY_SIZE);
	_check_if_only_one_argument();
	if (_line_is_number())
		location.set_body_size(atoi(this->_line.c_str()));
	else
		throw (LocationConfigurationError());
}

void ft::Parser::_set_root_conf(ft::LocationData &location)
{
	_reduce_line_to_value(ROOT);
	_check_if_only_one_argument();
	location.set_root(this->_line);
}

void ft::Parser::_set_index_conf(ft::LocationData &location)
{
	_reduce_line_to_value(INDEX);

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
	_reduce_line_to_value(REDIRECTION);
	_check_if_only_one_argument();
	location.set_redirection(this->_line);
}

void ft::Parser::_set_autoindex_conf(ft::LocationData &location)
{
	_reduce_line_to_value(AUTOINDEX);
	if (this->_line == "on")
		location.set_autoindex(true);
	else if (this->_line == "off")
		location.set_autoindex(false);
	else
		throw (LocationConfigurationError());
}

void ft::Parser::_set_accepted_methods_conf(ft::LocationData &location)
{
	_reduce_line_to_value(ACCEPTED_METHODS);
	
	std::stringstream accepted_methods_line(this->_line);
	std::string accepted_methods_value;
	while (accepted_methods_line.good())
	{
		std::getline(accepted_methods_line, accepted_methods_value, ' ');
		location.add_accepted_method(accepted_methods_value);
	}
}
void ft::Parser::_check_if_only_one_argument(void)
{ 
	if (this->_line.find(' ') != std::string::npos)
		throw (LocationConfigurationError());
	if (this->_line.find('\t') != std::string::npos)
		throw (LocationConfigurationError());
}

std::vector<ft::ServerData> ft::Parser::get_servers(void)
{
	return (this->_servers);
}
