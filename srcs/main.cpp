
#include <unistd.h> //read() write()
#include <string.h> //memset()
#include <iostream> //cpp
#include <sys/socket.h> //socket()
#include <arpa/inet.h> //htons()
#include <netinet/in.h> //sockaddr_in

#include "socket.hpp"

#define DOMAIN		AF_INET //IP
#define TCP			SOCK_STREAM //TCP
#define PROTOCOL	0
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
	char	buffer[100];
	int		reading;

	while((reading = read(client_socket, buffer, 100)))
	{
		std::cout << "Request:" << buffer << std::endl;
		std::cout << "Executing the request" << std::endl;
		write(client_socket, "response", 9);
	}

}

int main(void)
{
	ft::Socket server_socket;

	server_socket.start_listening(BACKLOG);

	while(1)
	{
		std::cout << "waiting........." << std::endl;
		int client_socket = get_client_connection(server_socket.get_socket_fd());
		deal_with_requests(client_socket);
		close(client_socket);
	}
	return (0);
}
