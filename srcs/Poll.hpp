/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:49:19 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/16 12:47:43 by lfrasson         ###   ########.fr       */
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
			size_t					_size;
			std::vector<ft::Socket> &_servers;
			struct pollfd			*_interest_list;

			Poll(void);

		public:
			Poll(std::vector<ft::Socket> &sockets);
			~Poll(void);
		
			void		exec(void);
			ft::Socket	& get_server(size_t index);
			short		get_event_return(size_t index);

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
