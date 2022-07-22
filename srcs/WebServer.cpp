/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:04:45 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/21 21:15:37 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"

ft::WebServer::WebServer(void)
{
	return ;
}

void ft::WebServer::init(const std::vector<ft::ServerData>& server_data, size_t backlog)
{
	_group_servers_by_port(server_data);
	this->_backlog = backlog;
	this->_size = this->_ports.size();
	_init_servers(this->_ports);
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

void ft::WebServer::_group_servers_by_port(const std::vector<ft::ServerData> &server_data)
{
	for (size_t i = 0; i < server_data.size(); i++)
	{
		int port = server_data[i].get_listen().get_port();
		this->_ports[port].push_back(server_data[i]);
	}
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

	try {
		client.connect(socket->get_fd());
		request_processor.run(client.get_fd());
	} catch (std::exception& e) {
		return ;
	}
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
