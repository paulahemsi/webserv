
#include <string.h> //memset()
#include <iostream> //cpp
#include <sys/socket.h> //socket()
#include <arpa/inet.h> //htons()
#include <netinet/in.h> //sockaddr_in

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
	ft::Server	server;

	try
	{
		server.create_sockets();
		server.start_listening(BACKLOG);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
		return(ERROR);
	}

	while(1)
	{
		std::cout << "waiting........." << std::endl;
		int client_socket = get_client_connection(server.get_socket_fd());
		deal_with_requests(client_socket);
		close(client_socket);
	}
	return (0);
}
