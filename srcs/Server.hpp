/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:01:52 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 21:04:27 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "socket.hpp"
#include "Poll.hpp"
#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include <vector>

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
			bool	_check_event(short revent);

		public:
			Server(void);
			Server(size_t size, int *ports, size_t backlog);
			~Server(void);
	
			void	create_sockets(void);
			void	run(void);
	};
}

#endif
