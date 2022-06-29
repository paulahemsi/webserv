/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPages.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:10:20 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/29 20:08:02 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorPages.hpp"

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

ft::ErrorPages &ft::ErrorPages::operator=(ft::ErrorPages const &right_hand_side)
{
	this->_pages = right_hand_side._pages;
	return (*this);
}

std::map<std::string, std::string> ft::ErrorPages::getPages(void) const
{
	return (this->_pages);
}

std::ostream &operator<<(std::ostream &outputFile, const ft::ErrorPages &object)
{
	std::map<std::string, std::string>::const_iterator it;
	std::map<std::string, std::string>::const_iterator end;

	it = object.getPages().begin();
	end = object.getPages().end();
	for (; it != end; it++)
		outputFile << it->first << " - " << it->second;

	return (outputFile);
}