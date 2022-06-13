/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:04:45 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 21:39:07 by phemsi-a         ###   ########.fr       */
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

void	ft::Server::create_sockets(void)
{
	std::vector<ft::Socket>::iterator socket;

	socket = this->_sockets.begin();
	for (; socket != this->_sockets.end(); socket++)
		socket->create();
}

static void deal_with_requests(ft::Client &client)
{
	size_t		size = 10000;
	char		buffer[size];

	while(client.send_request(buffer, size))
	{
		ft::Request	request(buffer);
		std::cout << "Executing the request" << std::endl;
		ft::Response response;
		response.send(client.get_fd());
	}
}

void	ft::Server::run(void)
{
	this->_start_listening();
	this->_event_loop();
}

void ft::Server::_event_loop(void)
{
	Poll	poll(this->_sockets);

	std::cout << "waiting........." << std::endl;
	while (true)
	{
		poll.exec();
		for (size_t i = 0; i < this->_size; i++)
			this->_check_event(poll, i);
	}
}

void	ft::Server::_check_event(ft::Poll &poll, size_t index)
{
	if (this->_check_event_mask(poll.get_event_return(index)))
	{
		ft::Client client;

		client.connect(poll.get_fd(index));
		deal_with_requests(client);
	}
}


void ft::Server::_start_listening(void)
{
	std::vector<ft::Socket>::iterator socket;

	socket = this->_sockets.begin();
	for (; socket != this->_sockets.end(); socket++)
		socket->start_listening(this->_backlog);
}


bool	ft::Server::_check_event_mask(short revents)
{
	if ((revents & POLLIN) == POLLIN)
		return (true);
	if ((revents & POLLPRI) == POLLPRI)
		return (true);
	if ((revents & POLLOUT) == POLLOUT)
		return (true);
	if ((revents & POLLWRBAND) == POLLWRBAND)
		return (true);
	return (false);
}

ft::Server::~Server(void)
{
	return ;
}
