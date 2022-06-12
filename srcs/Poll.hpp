/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poll.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:49:19 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 20:23:47 by lfrasson         ###   ########.fr       */
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
			short	get_revent(size_t index);
	};
}

#endif
