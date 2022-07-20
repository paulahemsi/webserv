/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:58:35 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/18 23:40:33 by lfrasson         ###   ########.fr       */
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
#include "utils.hpp"

namespace ft
{
	class Socket
	{
		private:
			int							_port;
			int							_fd;
			struct	sockaddr_in			_infos;
			std::vector<ft::ServerData>	_conf;

			void						_create(void);
			void						_set_infos(void);
			void						_bind(void);

		public:
			Socket(void);
			Socket(int port, std::vector<ft::ServerData> confs);
			~Socket(void);
			
			void	start_listening(int backlog);
			void	create(void);
			void	close_fd(void);
			int		get_fd(void);

			std::vector<ft::ServerData>	get_confs(void);
			
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
