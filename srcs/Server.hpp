/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:01:52 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 15:17:09 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "socket.hpp"
#include <vector>
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
			std::vector<ft::Socket> _sockets;

		public:
			Server(void);
			Server(size_t size, int *ports);
			~Server(void);
			
			void	start_listening(int backlog);
			void	create_sockets(void);
			
			int		get_socket_fd(void);
	};
}

#endif
