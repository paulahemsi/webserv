/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:04:45 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 15:29:37 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

ft::Server::Server(void): _sockets(1)
{
	return ;
}

ft::Server::Server(size_t size, int *ports): _sockets(ports, ports + size)
{
	return ;
}

void	ft::Server::create_sockets()
{
	std::vector<ft::Socket>::iterator socket;

	socket = this->_sockets.begin();
	for (; socket != this->_sockets.end(); socket++)
		socket->create();
}

void ft::Server::start_listening(int backlog)
{
	std::vector<ft::Socket>::iterator socket;

	socket = this->_sockets.begin();
	for (; socket != this->_sockets.end(); socket++)
		socket->start_listening(backlog);
}

int ft::Server::get_socket_fd(void)
{
	//TODO: return a socket get from event poll
	return (this->_sockets.begin()->get_fd());
}

ft::Server::~Server(void)
{
	return ;
}
