/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:58:35 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/23 15:46:11 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
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
