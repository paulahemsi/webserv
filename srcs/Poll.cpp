/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:49:23 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/16 12:47:49 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Poll.hpp"

ft::Poll::Poll(std::vector<ft::Socket> &servers):
_size(servers.size()),
_servers(servers),
_interest_list(new struct pollfd[_size])
{
	for (size_t i = 0; i < this->_size; i++)
	{
		this->_interest_list[i].fd = servers[i].get_fd();
		this->_interest_list[i].events = POLLIN | POLLPRI | POLLOUT | POLLWRBAND;
	}
}

ft::Poll::~Poll(void)
{
	delete this->_interest_list;
}

void	ft::Poll::exec(void)
{
	int ret = poll(this->_interest_list, this->_size, 0);
	if (ret == -1)
		throw (PollError());

}

ft::Socket	& ft::Poll::get_server(size_t index)
{
	return (this->_servers[index]);
}

short	ft::Poll::get_event_return(size_t index)
{
	return (this->_interest_list[index].revents);
}
