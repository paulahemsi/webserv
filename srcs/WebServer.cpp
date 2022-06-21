/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:04:45 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/20 20:55:00 by phemsi-a         ###   ########.fr       */
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
	std::map<int, std::vector<ft::ServerData> > ports;

	for (size_t i = 0; i < server_data.size(); i++)
	{
		int port = server_data[i].get_listen().get_port();
		ports[port].push_back(server_data[i]);
	}
	
	std::map<int, std::vector<ft::ServerData> >::iterator it_begin = ports.begin();
	std::map<int, std::vector<ft::ServerData> >::iterator it_end = ports.end();
	
	for (; it_begin != it_end; it_begin++)
	{
		ft::Server new_server(it_begin->first, it_begin->second);
		_servers.push_back(new_server);
	}
	return ;
}

void	ft::WebServer::create_servers(void)
{
	std::vector<ft::Server>::iterator server;

	server = this->_servers.begin();
	for (; server != this->_servers.end(); server++)
		server->create();
}

void	ft::WebServer::run(void)
{
	this->_start_listening();
	this->_event_loop();
}

void ft::WebServer::_event_loop(void)
{
	Poll	poll(this->_servers);

	std::cout << "waiting........." << std::endl;
	while (true)
	{
		poll.exec();
		for (size_t i = 0; i < this->_size; i++)
			this->_check_event(poll, i);
	}
}

void	ft::WebServer::_connect_with_client(ft::Server &server)
{
	ft::Client	client;
	size_t		size = 10000;
	char		buffer[size];

	client.connect(server.get_fd());
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
		this->_connect_with_client(poll.get_server(index));
}

void ft::WebServer::_start_listening(void)
{
	std::vector<ft::Server>::iterator server;

	server = this->_servers.begin();
	for (; server != this->_servers.end(); server++)
		server->start_listening(this->_backlog);
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
