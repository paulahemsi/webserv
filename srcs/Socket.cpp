/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:58:17 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/09 18:33:02 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

ft::Socket::Socket(void):
_fd(0)
{
	return ;
}

ft::Socket::Socket(int port, std::vector<ft::ServerData> confs):
_port(port),
_fd(0),
_conf(confs)
{
	_set_infos();
}

void	ft::Socket::create()
{
	_create();
	_bind();
}

void	ft::Socket::_create()
{
	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd == ERROR)
		throw (CreateSocketError());
}

void	ft::Socket::_set_infos()
{
	memset((char*)&this->_infos, 0, sizeof(this->_infos));
	this->_infos.sin_family = AF_INET;
	this->_infos.sin_port = htons(_port);
	this->_infos.sin_addr.s_addr = htonl(INADDR_ANY);
}

void	ft::Socket::_bind()
{
	if (bind(this->_fd, (struct sockaddr *)&this->_infos, sizeof(this->_infos)) == ERROR)
		throw (BindSocketError());
}

void ft::Socket::start_listening(int backlog)
{
	listen(this->_fd, backlog);
}

int ft::Socket::get_fd(void)
{
	return (this->_fd);
}
std::vector<ft::ServerData> ft::Socket::get_confs(void)
{
	return (this->_conf);
}

void ft::Socket::close_fd(void)
{
	if (fd_is_valid(this->_fd))
		close(this->_fd);
}

ft::Socket::~Socket(void)
{
	this->close_fd();
}
