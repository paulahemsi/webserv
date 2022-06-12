/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:01:52 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 18:30:18 by lfrasson         ###   ########.fr       */
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

		public:
			Server(void);
			Server(size_t size, int *ports, size_t backlog);
			~Server(void);
			
			void	create_sockets(void);
			void	start_listening(void);
			void	event_poll(void);
			int		get_socket_fd(void);
	};
}

#endif
