/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:58:35 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/19 09:04:44 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <unistd.h> //read() write()
#include <string.h> //memset()
#include <iostream> //cpp
#include <sys/socket.h> //socket()
#include <arpa/inet.h> //htons()
#include <netinet/in.h> //sockaddr_in
#include "ServerData.hpp"

#define PORT		4444
#define ERROR		-1

namespace ft
{
	class Server
	{
		private:
			int					_port;
			int					_fd;
			struct	sockaddr_in	_infos;
			ft::ServerData		_conf;

			void	_create(void);
			void	_set_infos(void);
			void	_bind(void);

			Server(void);

		public:
			Server(ft::ServerData conf);
			~Server(void);
			
			void	start_listening(int backlog);
			void	create(void);
			
			int		get_fd(void);
			
			class CreateSocketError : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31merror creating socket\e[0m");
					}
			};

			class BindSocketError : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31merror binding socket\e[0m");
					}
			};
	};
}

#endif
