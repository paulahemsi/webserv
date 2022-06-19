/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:18:36 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/19 08:45:35 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Listen.hpp"

ft::Listen::Listen(void):
_host(std::string()),
_port(std::string())
{
	return ;
}

ft::Listen::Listen(ft::Listen const &other)
{
	*this = other;
}

ft::Listen &ft::Listen::operator=(ft::Listen const &right_hand_side)
{
	this->_host = right_hand_side._host;
	this->_port = right_hand_side._port;
	return (*this);
}

ft::Listen::~Listen(void)
{
	return ;
}

void ft::Listen::set_host(std::string host)
{
	this->_host = host;
}

void ft::Listen::set_port(std::string port)
{
	this->_port = port;
}

std::string ft::Listen::get_host(void) const
{
	return (this->_host);
}

int	ft::Listen::get_port(void) const
{
	return (std::stoi(this->_port));
}

std::ostream &operator<<(std::ostream &outputFile, const ft::Listen &object)
{
	outputFile	<< "Host : " << object.get_host() << std::endl
				<< "Port : " << object.get_port() << std::endl;
	
	return outputFile;
}
