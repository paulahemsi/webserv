/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:37:20 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/12 18:28:29 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"

#define ERROR		-1
#define BACKLOG		100

typedef struct sockaddr_in socket_address;

static int get_client_connection(int server_socket)
{
	socket_address	client_infos;
	unsigned int	client_infos_size;

	client_infos_size = sizeof(client_infos);
	return (accept(server_socket,
					(struct sockaddr *)&client_infos,
					&client_infos_size));
}


static void deal_with_requests(int client_socket)
{
	char		buffer[10000];
	int			reading;

	while((reading = read(client_socket, buffer, 10000)))
	{
		ft::Request	request(buffer);
		request.debugging_request();
		std::cout << "Executing the request" << std::endl;

		ft::Response response;
		response.show();
		response.send(client_socket);
	}
}

int main(void)
{
	int			ports[2] = {4444, 4445};
	ft::Server	server(2, ports, BACKLOG);

	try
	{
		server.create_sockets();
		server.start_listening();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
		return(ERROR);
	}

	while(1)
	{
		std::cout << "waiting........." << std::endl;
	//	server.event_poll();
		int client_socket = get_client_connection(server.get_socket_fd());
		deal_with_requests(client_socket);
		close(client_socket);
	}
	return (0);
}
