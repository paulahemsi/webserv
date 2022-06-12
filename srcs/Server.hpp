/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:01:52 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 19:12:09 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "socket.hpp"
#include <vector>
#include <poll.h>

namespace ft
{
	class Server
	{
		private:
			size_t					_size;
			size_t					_backlog;
			std::vector<ft::Socket> _sockets;

			void	_start_listening(void);
			void	_event_loop(void);
			void	_event_poll(void);

		public:
			Server(void);
			Server(size_t size, int *ports, size_t backlog);
			~Server(void);
	
			void	create_sockets(void);
			void	run(void);
			int		get_socket_fd(void);
	};
}

#endif
