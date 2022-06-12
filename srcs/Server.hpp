/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:01:52 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 14:19:20 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "socket.hpp"
//#include <unistd.h>
//#include <string.h>
//#include <iostream>
//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <netinet/in.h>
//
//#define PORT		4444
//#define ERROR		-1

namespace ft
{
	class Server
	{
		private:
			ft::Socket _socket;

		public:
			Server(void);
			~Server(void);
			
			void	start_listening(int backlog);
			void	create_sockets(void);
			
			int		get_socket_fd(void);
	};
}

#endif
