/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:04:45 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/09 19:01:49 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"

ft::WebServer::WebServer(void)
{
	return ;
}

void ft::WebServer::init(std::vector<ft::ServerData> server_data, size_t backlog)
{
	server_data_map ports;

	ports = _group_servers_by_port(server_data);
	this->_backlog = backlog;
	this->_size = ports.size();
	_init_servers(ports);
}

void ft::WebServer::_init_servers(ft::WebServer::server_data_map &ports)
{
	server_data_map::iterator it_begin = ports.begin();
	server_data_map::iterator it_end = ports.end();
	
	for (; it_begin != it_end; it_begin++)
	{
		ft::Socket *new_socket = new ft::Socket(it_begin->first, it_begin->second);
		_sockets.push_back(new_socket);
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
	std::vector<ft::Socket *>::iterator socket;

	socket = this->_sockets.begin();
	for (; socket != this->_sockets.end(); socket++)
		(*socket)->create();
}

void	ft::WebServer::run(void)
{
	this->_start_listening();
	this->_event_loop();
}

void ft::WebServer::_event_loop(void)
{
	this->_poll.init(this->_sockets);

	std::cout << WEBSERV << std::endl;
	while (true)
	{
		this->_poll.exec();
		for (size_t i = 0; i < this->_size; i++)
			this->_check_event(this->_poll, i);
	}
}

void	ft::WebServer::_connect_with_client(ft::Socket *socket)
{
	ft::Client				client;
	ft::RequestProcessor	request_processor(socket);
	size_t					size = 10000;
	char					buffer[size];

	client.connect(socket->get_fd());
	while(client.send_request(buffer, size))
		request_processor.run(buffer, client.get_fd());
}

void	ft::WebServer::_check_event(ft::Poll &poll, size_t index)
{
	if (this->_check_event_mask(poll.get_event_return(index)))
		this->_connect_with_client(poll.get_socket(index));
}

void ft::WebServer::_start_listening(void)
{
	std::vector<ft::Socket *>::iterator socket;

	socket = this->_sockets.begin();
	for (; socket != this->_sockets.end(); socket++)
		(*socket)->start_listening(this->_backlog);
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
	for (size_t i = 0; i < this->_sockets.size(); i++)
	{
		if (this->_sockets[i])
		{
			this->_sockets[i]->close_fd();
			delete this->_sockets[i];
		}
	}
}
