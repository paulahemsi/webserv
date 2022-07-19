/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPages.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:10:20 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/18 21:23:06 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorPages.hpp"

#define DEFAUT_PATH "./www/error/"

ft::ErrorPages::ErrorPages(void)
{
	return ;
}

ft::ErrorPages::ErrorPages(ft::ErrorPages const &other)
{
	*this = other;
}

ft::ErrorPages::~ErrorPages(void)
{
	return ;
}

void	ft::ErrorPages::add_page(std::string code, std::string path)
{
	this->_pages[code] = path;
}

void	ft::ErrorPages::_add_default_page(std::string code)
{
	add_page(code, _get_default_path(code));
}

std::string	ft::ErrorPages::_get_default_path(std::string code)
{
	return (std::string(DEFAUT_PATH).append(code).append(".html"));
}

ft::ErrorPages &ft::ErrorPages::operator=(ft::ErrorPages const &right_hand_side)
{
	this->_pages = right_hand_side._pages;
	return (*this);
}

std::map<std::string, std::string> ft::ErrorPages::get_pages(void) const
{
	return (this->_pages);
}

std::string    ft::ErrorPages::get_page(std::string code) const
{
	if (has_page(code))
		return (this->_pages.at(code));
	return ("");
}

bool	ft::ErrorPages::has_page(std::string code) const
{
	if (this->_pages.count(code) == 1)
		return (true);
	return (false);
}

void	ft::ErrorPages::set_defaults(void)
{
	_add_default_page("400");
	_add_default_page("403");
	_add_default_page("404");
	_add_default_page("405");
	_add_default_page("413");
	_add_default_page("500");
}

std::ostream &operator<<(std::ostream &outputFile, const ft::ErrorPages &object)
{
	std::map<std::string, std::string>					pages;
	std::map<std::string, std::string>::const_iterator	it;
	std::map<std::string, std::string>::const_iterator	end;

	pages = object.get_pages();
	for (it = pages.begin(); it != pages.end(); it++)
		outputFile << it->first << " - " << it->second << std::endl;

	return (outputFile);
}
