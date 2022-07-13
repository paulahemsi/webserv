/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:47:31 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/12 21:06:20 by phemsi-a         ###   ########.fr       */
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
	return ;
}

void ft::Parser::exec(std::string filename)
{
	this->_file_stream.open(filename.c_str(), std::ifstream::in);
	if(!this->_file_stream)
		throw (OpenFileError());
	_parse_file();
	this->_file_stream.close();
}

void ft::Parser::_parse_file(void)
{
	while (this->_file_stream.good())
	{
		std::getline(this->_file_stream, this->_line);
		if (ft::line_is_valid(this->_line))
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
	ft::ServerParser new_server;

	new_server.exec(this->_file_stream, this->_line);
	this->_servers.push_back(new_server.get_server());
}

const std::vector<ft::ServerData> &ft::Parser::get_servers(void) const
{
	return (this->_servers);
}

std::ostream &operator<<(std::ostream &outputFile, const ft::Parser &object)
{
	for (size_t i = 0; i < object.get_servers().size(); i++)
		outputFile	<< object.get_servers()[i] << std::endl;
	
	return outputFile;
}
