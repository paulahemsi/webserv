/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:49:19 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 22:35:57 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLL_HPP
#define POLL_HPP

#include "socket.hpp"
#include <vector>
#include <poll.h>

namespace ft
{
	class Poll
	{
		private:
			size_t			_size;
			struct pollfd	*_interest_list;

			Poll(void);

		public:
			Poll(std::vector<ft::Socket> &sockets);
			~Poll(void);
		
			void	exec(void);
			int		get_fd(size_t index);
			short	get_event_return(size_t index);

			class PollError : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31mpoll error\e[0m");
					}
			};
	};
}

#endif
