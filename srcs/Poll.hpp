/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:49:19 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/09 19:00:27 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLL_HPP
#define POLL_HPP

#include "Socket.hpp"
#include <vector>
#include <poll.h>

namespace ft
{
	class Poll
	{
		private:
			size_t						_size;
			std::vector<ft::Socket *>	_sockets;
			struct pollfd				*_interest_list;


		public:
			Poll(void);
			~Poll(void);
		
			void		init(std::vector<ft::Socket *> &sockets);
			void		exec(void);
			ft::Socket	*get_socket(size_t index);
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
