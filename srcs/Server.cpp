/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:04:45 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 14:21:33 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

ft::Server::Server(void)
{
	return ;
}

void	ft::Server::create_sockets()
{
	this->_socket.create();
}

void ft::Server::start_listening(int backlog)
{
	this->_socket.start_listening(backlog);
}

int ft::Server::get_socket_fd(void)
{
	return (this->_socket.get_fd());
}

ft::Server::~Server(void)
{
	return ;
}
