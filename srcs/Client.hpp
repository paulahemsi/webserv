/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:41:42 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/18 23:40:14 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP 

#include <sys/socket.h> 
#include <netinet/in.h>
#include <unistd.h>
#include <exception>
#include "utils.hpp"

namespace ft
{
	typedef struct sockaddr_in socket_address;

	class Client
	{
		private:
			socket_address	_infos;
			int				_fd;

		public:
			Client(void);
			~Client(void);

			void	connect(int server_fd);
			int		get_fd(void);
	
		class AcceptConnectionError : public std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return ("Error to accept new connection");
				}
		};
	};
}

#endif
