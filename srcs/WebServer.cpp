/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:04:45 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/24 20:18:50 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"

ft::WebServer::WebServer(void)
{
	return ;
}

ft::WebServer::WebServer(std::vector<ft::ServerData> server_data, size_t backlog):
_backlog(backlog)
{
	server_data_map ports;

	ports = _group_servers_by_port(server_data);
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
	Poll	poll(this->_sockets);

	std::cout << "waiting........." << std::endl;
	while (true)
	{
		poll.exec();
		for (size_t i = 0; i < this->_size; i++)
			this->_check_event(poll, i);
	}
}

bool	ft::WebServer::_is_server_name_match(std::string request_server_name, std::vector<std::string> server_names)
{
	for (size_t i = 0; i < server_names.size(); i++)
		if (server_names[i] == request_server_name)
			return (true);
	return (false);
}

ft::ServerData	ft::WebServer::_define_server_block(std::string	server_name, ft::Socket *socket)
{
	server_data_vector confs;

	std::cout << server_name << std::endl;
	confs = socket->get_confs();
	
	server_data_vector::iterator it = confs.begin();
	server_data_vector::iterator it_end = confs.end();
	for (; it != it_end; it++)
		if (_is_server_name_match(server_name, it->get_server_name()))
			return (*it);
	return (confs[0]);
}

void	ft::WebServer::_connect_with_client(ft::Socket *socket)
{
	ft::Client	client;
	size_t		size = 10000;
	char		buffer[size];

	client.connect(socket->get_fd());
	while(client.send_request(buffer, size))
	{
		ft::Request	request(buffer);
		std::cout << "Executing the request" << std::endl;
		
		ft::ServerData	server_data;
		server_data = _define_server_block(request.get_server_name(), socket);
		std::cout << server_data << std::endl;
		
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
	std::vector<ft::Socket *>::iterator socket;

	socket = this->_sockets.begin();
	for (; socket != this->_sockets.end(); socket++)
		delete *socket;
	return ;
}
