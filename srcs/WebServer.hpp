/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:01:52 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/24 22:57:40 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "ServerData.hpp"
#include "Socket.hpp"
#include "Poll.hpp"
#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include <queue>
#include <vector>
#include <map>

namespace ft
{
	class WebServer
	{
		typedef std::map<int, std::vector<ft::ServerData> > server_data_map;
		typedef std::vector<ft::ServerData> server_data_vector;

		private:
			size_t						_size;
			size_t						_backlog;
			std::vector<ft::Socket *>	_sockets;

			void	_start_listening(void);
			void	_event_loop(void);
			void	_check_event(ft::Poll &poll, size_t index);
			bool	_check_event_mask(short revent);
			void	_connect_with_client(ft::Socket *socket);

			ft::LocationData	_select_location(std::string uri, ft::ServerData &server);

			server_data_map	_group_servers_by_port(std::vector<ft::ServerData> server_data);
			void			_init_servers(server_data_map &ports);
			ft::ServerData	_select_server(std::string server_name, server_data_vector confs);
			int				_is_match(std::string name, std::vector<std::string> names);

		public:
			WebServer(void);
			WebServer(std::vector<ft::ServerData> server_data, size_t backlog);
			~WebServer(void);
	
			void	create_sockets(void);
			void	run(void);
			
			class NotFound : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31mLocation not found\e[0m");
					}
			};
	};
}

#endif
