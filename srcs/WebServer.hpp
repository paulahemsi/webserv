/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:01:52 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/01 18:32:46 by phemsi-a         ###   ########.fr       */
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

# define BLACK "\033[0;30m"
# define BOLD_BLACK "\033[1;30m"
# define RED "\033[0;31m"
# define BOLD_RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define BOLD_GREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define BOLD_YELLOW "\033[1;33m"
# define BLUE "\033[0;34m"
# define BOLD_BLUE "\033[1;34m"
# define PURPLE "\033[0;35m"
# define BOLD_PURPLE "\033[1;35m"
# define CYAN "\033[0;36m"
# define BOLD_CYAN "\033[1;36m"
# define WHITE "\033[0;37m"
# define BOLD_WHITE "\033[1;37m"
# define RESET_COLOR "\033[0m"
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
			std::vector<ft::Socket *>	_sockets;

			void	_start_listening(void);
			void	_event_loop(void);
			void	_check_event(ft::Poll &poll, size_t index);
			bool	_check_event_mask(short revent);
			void	_connect_with_client(ft::Socket *socket);


			server_data_map		_group_servers_by_port(std::vector<ft::ServerData> server_data);
			void				_init_servers(server_data_map &ports);

		public:
			WebServer(void);
			WebServer(std::vector<ft::ServerData> server_data, size_t backlog);
			~WebServer(void);
	
			void	create_sockets(void);
			void	run(void);
	};
}

#endif
