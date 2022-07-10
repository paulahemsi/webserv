/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:01:52 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/09 20:06:38 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "ServerData.hpp"
#include "Socket.hpp"
#include "Poll.hpp"
#include "Client.hpp"
#include "RequestProcessor.hpp"
#include <vector>
#include <map>

#define	WEBSERV	"\n\n\n \e[0;38;5;82m\
	██     ██ ███████ ██████  \e[0;38;5;22m███████ ███████ ██████  ██    ██ \n \e[0;38;5;82m\
	██     ██ ██      ██   ██ \e[0;38;5;22m██      ██      ██   ██ ██    ██ \n \e[0;38;5;82m\
	██  █  ██ █████   ██████  \e[0;38;5;22m███████ █████   ██████  ██    ██ \n \e[0;38;5;82m\
	██ ███ ██ ██      ██   ██  \e[0;38;5;22m    ██ ██      ██   ██  ██  ██  \n \e[0;38;5;82m\
 	 ███ ███  ███████ ██████  \e[0;38;5;22m███████ ███████ ██   ██   ████   \n\n\033[0m"

namespace ft
{
	class WebServer
	{
		typedef std::map<int, std::vector<ft::ServerData> > server_data_map;

		private:
			size_t						_size;
			size_t						_backlog;
			ft::Poll					_poll;
			std::vector<ft::Socket *>	_sockets;
			server_data_map				_ports;
			

			void	_start_listening(void);
			void	_event_loop(void);
			void	_check_event(ft::Poll &poll, size_t index);
			bool	_check_event_mask(short revent);
			void	_connect_with_client(ft::Socket *socket);


			void		_group_servers_by_port(const std::vector<ft::ServerData>& server_data);
			void				_init_servers(server_data_map &ports);

		public:
			WebServer(void);
			~WebServer(void);
	
			void	init(const std::vector<ft::ServerData> &server_data, size_t backlog);
			void	create_sockets(void);
			void	run(void);
	};
}

#endif
