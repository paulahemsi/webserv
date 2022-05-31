
#include <unistd.h> //read() write()
#include <string.h> //memset()
#include <iostream> //cpp
#include <sys/socket.h> //socket()
#include <arpa/inet.h> //htons()
#include <netinet/in.h> //sockaddr_in
// struct sockaddr_in 
// { 
//     __uint8_t         sin_len; 
//     sa_family_t       sin_family; 
//     in_port_t         sin_port; 
//     struct in_addr    sin_addr; 
//     char              sin_zero[8]; 
// };

#define DOMAIN		AF_INET //IP
#define TYPE		SOCK_STREAM //TCP
#define PROTOCOL	0
#define ERROR		-1
//defines the maximum number of pending connections that can be queued up before connections are refused.
#define BACKLOG		100
#define PORT		888

int main(void)
{
	struct sockaddr_in server_infos;
	struct sockaddr_in client_infos;
	unsigned int client_infos_size = sizeof(client_infos);

	int server_socket_fd = socket(DOMAIN, TYPE, PROTOCOL);
	if (server_socket_fd == ERROR)
	{
		std::cout << "error creating server socket" << std::endl;
		return (-1);
	}
	server_infos.sin_family = DOMAIN;
	server_infos.sin_port = htons(PORT);
	memset((char*)&server_infos, 0, sizeof(server_infos));
	if (bind(server_socket_fd, (struct sockaddr *)&server_infos, sizeof(server_infos)) == ERROR)
	{
		std::cout << "error binding server socket" << std::endl;
		return (-1);
	}
	listen(server_socket_fd, BACKLOG);

	while(1)
	{
		std::cout << "waiting........." << std::endl;
		int client_socket_fd = accept(server_socket_fd, (struct sockaddr *)&client_infos, &client_infos_size);
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
	close(server_socket_fd);

	return (0);
}