/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:01:52 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/24 20:44:02 by lfrasson         ###   ########.fr       */
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
			
			void			_init_servers(server_data_map &ports);
			server_data_map	_group_servers_by_port(std::vector<ft::ServerData> server_data);
			ft::ServerData	_define_server_block(std::string server_name, server_data_vector confs);
			bool			_is_server_name_match(std::string request_server_name, std::vector<std::string> server_names);

		public:
			WebServer(void);
			WebServer(std::vector<ft::ServerData> server_data, size_t backlog);
			~WebServer(void);
	
			void	create_sockets(void);
			void	run(void);
	};
}

#endif
