/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:58:17 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/19 09:06:35 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

ft::Server::Server(void)
{
	return ;
}

ft::Server::Server(ft::ServerData conf):
_port(conf.get_listen().get_port()),
_conf(conf)
{
	_set_infos();
}

void	ft::Server::create()
{
	_create();
	_bind();
}

void	ft::Server::_create()
{
	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd == ERROR)
		throw (CreateSocketError());
}

void	ft::Server::_set_infos()
{
	memset((char*)&this->_infos, 0, sizeof(this->_infos));
	this->_infos.sin_family = AF_INET;
	this->_infos.sin_port = htons(_port);
	this->_infos.sin_addr.s_addr = htonl(INADDR_ANY);
}

void	ft::Server::_bind()
{
	if (bind(this->_fd, (struct sockaddr *)&this->_infos, sizeof(this->_infos)) == ERROR)
		throw (BindSocketError());
}

void ft::Server::start_listening(int backlog)
{
	listen(this->_fd, backlog);
}

int ft::Server::get_fd(void)
{
	return (this->_fd);
}

ft::Server::~Server(void)
{
	close(this->_fd);
}
