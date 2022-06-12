/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:04:45 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 20:57:11 by lfrasson         ###   ########.fr       */
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

#include "Request.hpp"
#include "Response.hpp"

static void deal_with_requests(int client_socket)
{
	char		buffer[10000];
	int			reading;

	while((reading = read(client_socket, buffer, 10000)))
	{
		ft::Request	request(buffer);
		request.debugging_request();
		std::cout << "Executing the request" << std::endl;

		ft::Response response;
		response.show();
		response.send(client_socket);
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
		{
			if (this->_check_event(poll.get_revent(i)))
			{
				Client client;

				int client_socket = client.connect(poll.get_fd(i));
				deal_with_requests(client_socket);
				close(client_socket);
			}
		}
	}
}

void ft::Server::_start_listening(void)
{
	std::vector<ft::Socket>::iterator socket;

	socket = this->_sockets.begin();
	for (; socket != this->_sockets.end(); socket++)
		socket->start_listening(this->_backlog);
}


bool	ft::Server::_check_event(short revents)
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
