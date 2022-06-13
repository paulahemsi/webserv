/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:49:19 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 21:28:39 by phemsi-a         ###   ########.fr       */
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
	};
}

#endif
