/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:41:42 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 20:53:21 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP 

#include <sys/socket.h> 
#include <netinet/in.h>

namespace ft
{
	typedef struct sockaddr_in socket_address;

	class Client
	{
		private:
			socket_address	_infos;

		public:
			Client(void);
			~Client(void);

			int	connect(int server_fd);	
	};
}

#endif
