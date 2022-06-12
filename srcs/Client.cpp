/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:41:32 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 20:54:33 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

ft::Client::Client(void)
{
	return ;
}

ft::Client::~Client(void)
{
	return ;
}

int	ft::Client::connect(int server_fd)
{
	unsigned int	infos_size;
	
	infos_size = sizeof(this->_infos);
	return (accept(server_fd, (struct sockaddr *)&this->_infos, &infos_size));
}