/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:58:17 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/22 21:40:26 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

ft::Socket::Socket(void):
_fd(-1)
{
	return ;
}

ft::Socket::Socket(int port, std::vector<ft::ServerData> confs):
_port(port),
_fd(-1),
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

ft::Socket::~Socket(void)
{
	close(this->_fd);
}
