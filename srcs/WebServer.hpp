/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:01:52 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 22:21:50 by phemsi-a         ###   ########.fr       */
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
	class WebServer
	{
		private:
			size_t					_size;
			size_t					_backlog;
			std::vector<ft::Socket> _servers;

			void	_start_listening(void);
			void	_event_loop(void);
			void	_check_event(ft::Poll &poll, size_t index);
			bool	_check_event_mask(short revent);
			void	_connect_with_client(int server_fd);

		public:
			WebServer(void);
			WebServer(size_t size, int *ports, size_t backlog);
			~WebServer(void);
	
			void	create_servers(void);
			void	run(void);
	};
}

#endif
