/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:04:45 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 18:46:21 by lfrasson         ###   ########.fr       */
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
	while(1)
	{
		std::cout << "waiting........." << std::endl;
	//	server.event_poll();
		int client_socket = get_client_connection(this->get_socket_fd());
		deal_with_requests(client_socket);
		close(client_socket);
	}
}

void ft::Server::_start_listening(void)
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
