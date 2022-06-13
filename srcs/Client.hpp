/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:41:42 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 21:22:48 by phemsi-a         ###   ########.fr       */
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
			int				_fd;

		public:
			Client(void);
			~Client(void);

			void	connect(int server_fd);
			int		send_request(char *buffer, size_t size);
			int		get_fd(void);
	};
}

#endif
