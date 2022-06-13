/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:49:23 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 22:33:48 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Poll.hpp"

ft::Poll::Poll(std::vector<ft::Socket> &sockets):
_size(sockets.size()),
_interest_list(new struct pollfd[_size])
{
	for (size_t i = 0; i < this->_size; i++)
	{
		this->_interest_list[i].fd = sockets[i].get_fd();
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

int		ft::Poll::get_fd(size_t index)
{
	return (this->_interest_list[index].fd);
}

short	ft::Poll::get_event_return(size_t index)
{
	return (this->_interest_list[index].revents);
}
