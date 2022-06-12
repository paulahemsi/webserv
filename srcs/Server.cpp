/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:04:45 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 19:44:46 by lfrasson         ###   ########.fr       */
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
typedef struct sockaddr_in socket_address;

static int get_client_connection(int server_socket)
{
	socket_address	client_infos;
	unsigned int	client_infos_size;

	client_infos_size = sizeof(client_infos);
	return (accept(server_socket,
					(struct sockaddr *)&client_infos,
					&client_infos_size));
}


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
	std::cout << "waiting........." << std::endl;
	while(1)
		this->_event_poll();

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

void	ft::Server::_event_poll()
{
	size_t								size = this->_size;
	struct pollfd						interest_list[size];
	std::vector<ft::Socket>::iterator	socket;

	for (size_t i = 0; i < size; i++)
	{
		interest_list[i].fd = this->_sockets[i].get_fd();
		interest_list[i].events = POLLIN | POLLPRI | POLLOUT | POLLWRBAND;
	}
	int ret;
	while ((ret = poll(interest_list, size, 0)))
	{
		if (ret == -1)
			return ;
		for (size_t i = 0; i < size; i++)
		{
			if (this->_check_event(interest_list[i].revents))
			{
				int client_socket = get_client_connection(interest_list[i].fd);
				deal_with_requests(client_socket);
				close(client_socket);
			}
		}
	}
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
