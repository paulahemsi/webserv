/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:47:31 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/17 12:00:52 by phemsi-a         ###   ########.fr       */
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

void ft::Parser::_parse_file(void)
{
	std::string line;
	while (this->_file_stream.good())
	{
		std::getline(this->_file_stream, line);
		std::cout << line << std::endl;
	}
}

std::vector<ft::Server> ft::Parser::get_servers(void)
{
	return (this->_servers);
}

