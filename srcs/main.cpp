
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

int main(void)
{
	struct sockaddr_in client_infos;
	unsigned int client_infos_size = sizeof(client_infos);

	ft::Socket socket;

	socket.start_listening(BACKLOG);

	while(1)
	{
		std::cout << "waiting........." << std::endl;
		int client_socket_fd = accept(socket.get_socket_fd(), (struct sockaddr *)&client_infos, &client_infos_size);
		char buffer[100];
		int reading;
		while((reading = read(client_socket_fd, buffer, 100)))
		{
			std::cout << "Request:" << buffer << std::endl;
			std::cout << "Executing the request" << std::endl;
			write(client_socket_fd, "response", 9);
		}
		close(client_socket_fd);
	}

	return (0);
}
