/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:52:18 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/15 18:02:31 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Cgi.hpp"

ft::Cgi::Cgi(void)
{
	return ;
}

ft::Cgi::Cgi(ft::Cgi const &other)
{
	*this = other;
}

ft::Cgi::~Cgi(void)
{
	return ;
}

void	ft::Cgi::add_program(std::string extension, std::string path)
{
	this->_program[extension] = path;
}

ft::Cgi &ft::Cgi::operator=(ft::Cgi const &right_hand_side)
{
	this->_program = right_hand_side._program;
	return (*this);
}

std::string ft::Cgi::get_program(std::string extension) const
{
	try
	{
		return (this->_program.at(extension));
	}
	catch(const std::out_of_range& e)
	{
		return ("");
	}
}

std::map<std::string, std::string> ft::Cgi::get_program_map(void) const
{
	return (this->_program);
}

bool	ft::Cgi::has_extension(std::string extension)
{
	if (this->_program.count(extension))
		return (true);
	return (false);
}

size_t	ft::Cgi::size(void)
{
	return (this->_program.size());
}


std::ostream &operator<<(std::ostream &outputFile, const ft::Cgi &object)
{
	std::map<std::string, std::string>					programs;
	std::map<std::string, std::string>::const_iterator	it;
	std::map<std::string, std::string>::const_iterator	end;

	programs = object.get_program_map();
	for (it = programs.begin(); it != programs.end(); it++)
		outputFile << it->first << " " << it->second << std::endl;

	return (outputFile);
}
