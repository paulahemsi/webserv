/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:41:32 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/08 18:01:14 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <unistd.h>

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
	return ;
}

int ft::Client::get_fd(void)
{
	return (this->_fd);
}
