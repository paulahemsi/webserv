/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:01:52 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/26 00:45:03 by phemsi-a         ###   ########.fr       */
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
		typedef std::priority_queue<ft::LocationData> location_data_queue;

		private:
			size_t						_size;
			size_t						_backlog;
			std::vector<ft::Socket *>	_sockets;

			void	_start_listening(void);
			void	_event_loop(void);
			void	_check_event(ft::Poll &poll, size_t index);
			bool	_check_event_mask(short revent);
			void	_connect_with_client(ft::Socket *socket);


			server_data_map		_group_servers_by_port(std::vector<ft::ServerData> server_data);
			void				_init_servers(server_data_map &ports);
			ft::ServerData		_select_server(std::string server_name, server_data_vector confs);
			int					_is_match(std::string name, std::vector<std::string> names);
			ft::LocationData	_select_location(std::string uri, ft::ServerData &server);
			location_data_queue	_check_locations(std::string uri, ft::ServerData &server);
			void	_execute_request(ft::Request& request, server_data_vector confs);
			void	_check_method(std::set<std::string> methods, std::string request_method);

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
			class MethodNotAllowed : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31mMethod Not Allowed\e[0m");
					}
			};
	};
}

#endif
