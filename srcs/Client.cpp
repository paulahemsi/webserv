/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:41:32 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/18 23:40:21 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

ft::Client::Client(void)
{
	return ;
}

ft::Client::~Client(void)
{
	close(this->_fd);
	return ;
}

void ft::Client::connect(int server_fd)
{
	unsigned int	infos_size;
	
	infos_size = sizeof(this->_infos);
	this->_fd = accept(server_fd, (struct sockaddr *)&this->_infos, &infos_size);
	if (this->_fd == ERROR)
		throw (AcceptConnectionError()); 
	return ;
}

int ft::Client::get_fd(void)
{
	return (this->_fd);
}
