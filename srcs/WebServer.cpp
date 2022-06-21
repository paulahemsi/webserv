/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:04:45 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/20 21:27:14 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"

ft::WebServer::WebServer(void)
{
	return ;
}

ft::WebServer::WebServer(std::vector<ft::ServerData> server_data, size_t backlog):
_size(server_data.size()),
_backlog(backlog)
{
	server_data_map ports;

	ports = _group_servers_by_port(server_data);
	_init_servers(ports);
}

void ft::WebServer::_init_servers(ft::WebServer::server_data_map &ports)
{
	server_data_map::iterator it_begin = ports.begin();
	server_data_map::iterator it_end = ports.end();
	
	for (; it_begin != it_end; it_begin++)
	{
		ft::Socket new_server(it_begin->first, it_begin->second);
		_sockets.push_back(new_server);
	}
	return ;
}

ft::WebServer::server_data_map ft::WebServer::_group_servers_by_port(std::vector<ft::ServerData> server_data)
{
	server_data_map ports;

	for (size_t i = 0; i < server_data.size(); i++)
	{
		int port = server_data[i].get_listen().get_port();
		ports[port].push_back(server_data[i]);
	}
	return (ports);
}

void	ft::WebServer::create_sockets(void)
{
	std::vector<ft::Socket>::iterator socket;

	socket = this->_sockets.begin();
	for (; socket != this->_sockets.end(); socket++)
		socket->create();
}

void	ft::WebServer::run(void)
{
	this->_start_listening();
	this->_event_loop();
}

void ft::WebServer::_event_loop(void)
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

void	ft::WebServer::_connect_with_client(ft::Socket &socket)
{
	ft::Client	client;
	size_t		size = 10000;
	char		buffer[size];

	client.connect(socket.get_fd());
	while(client.send_request(buffer, size))
	{
		ft::Request	request(buffer);
		std::cout << "Executing the request" << std::endl;
		ft::Response response;
		response.send(client.get_fd());
	}
}

void	ft::WebServer::_check_event(ft::Poll &poll, size_t index)
{
	if (this->_check_event_mask(poll.get_event_return(index)))
		this->_connect_with_client(poll.get_socket(index));
}

void ft::WebServer::_start_listening(void)
{
	std::vector<ft::Socket>::iterator socket;

	socket = this->_sockets.begin();
	for (; socket != this->_sockets.end(); socket++)
		socket->start_listening(this->_backlog);
}

bool	ft::WebServer::_check_event_mask(short revents)
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

ft::WebServer::~WebServer(void)
{
	return ;
}
