/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:04:45 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 18:34:52 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

ft::Server::Server(void):
_size(1),
_sockets(_size)
{
	return ;
}

ft::Server::Server(size_t size, int *ports, size_t backlog):
_size(size),
_backlog(backlog),
_sockets(ports, ports + size)
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

void ft::Server::start_listening(void)
{
	std::vector<ft::Socket>::iterator socket;

	socket = this->_sockets.begin();
	for (; socket != this->_sockets.end(); socket++)
		socket->start_listening(this->_backlog);
}

//void	ft::Server::event_poll()
//{
//	size_t								size = this->_size;
//	struct pollfd						poll_fds[size];
//	std::vector<ft::Socket>::iterator	socket;
//
//	for (int i = 0; size; i++)
//	{
//		poll_fds[i].fd = this->_sockets[i].get_fd();
//		poll_fds[i].events = POLLIN | POLLPRI | POLLOUT | POLLWRBAND;
//	}
//	int ret = poll(poll_fds, size, 0);
//	if (ret == -1)
//		return ;
//	for (int i = 0; size; i++)
//		if ((poll_fds[i].revents & (POLLIN | POLLPRI | POLLOUT | POLLWRBAND)) == (POLLIN | POLLPRI | POLLOUT | POLLWRBAND))
//			//set what fd
//}

int ft::Server::get_socket_fd(void)
{
	//TODO: return a socket get from event poll
	return (this->_sockets.begin()->get_fd());
}

ft::Server::~Server(void)
{
	return ;
}
