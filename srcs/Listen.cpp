/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:18:36 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/16 18:33:00 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Listen.hpp"

ft::Listen::Listen(void):
_listen(std::pair<std::string, std::string>())
{
	return ;
}

ft::Listen::Listen(std::pair<std::string, std::string> const other):
_listen(std::pair<std::string, std::string>())
{
	*this = other;
}

ft::Listen &ft::Listen::operator=(ft::Listen const &right_hand_side)
{
	this->_listen = right_hand_side._listen;
	return (*this);
}

ft::Listen::~Listen(void)
{
	return ;
}

void ft::Listen::set_host(std::string host)
{
	this->_listen.first = host;
}

void ft::Listen::set_port(std::string port)
{
	this->_listen.second = port;
}

std::string ft::Listen::get_host(void)
{
	return (this->_listen.first);
}

std::string ft::Listen::get_port(void)
{
	return (this->_listen.second);
}
