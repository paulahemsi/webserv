/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:47:31 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/17 14:41:21 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

ft::Parser::Parser(void)
{
	return ;
}

ft::Parser::Parser(const char* filename)
{
	std::cout << filename << std::endl;
	this->_file_stream.open(filename, std::ifstream::in);
	if(!this->_file_stream)
		throw (OpenFileError());
	this->_parse_file();
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
			if (line.find(SERVER_CONF_BEGIN, 0) != std::string::npos)
				this->_parse_server_block(line);
			else
				throw (ServerConfigurationError());
		}
	}
}

void ft::Parser::_parse_server_block(std::string &line)
{
	std::cout << line << std::endl;
	while (this->_file_stream.good())
	{
		std::getline(this->_file_stream, line);
		if (not_empty(line))
		{
			if (line == SERVER_CONF_END)
				return ;
			std::cout << line << std::endl;
		}
	}
}

std::vector<ft::Server> ft::Parser::get_servers(void)
{
	return (this->_servers);
}

