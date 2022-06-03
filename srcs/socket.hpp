#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <unistd.h> //read() write()
#include <string.h> //memset()
#include <iostream> //cpp
#include <sys/socket.h> //socket()
#include <arpa/inet.h> //htons()
#include <netinet/in.h> //sockaddr_in

#define PORT		4444
#define ERROR		-1

namespace ft
{
	class Socket
	{
		private:
			int					_fd;
			struct	sockaddr_in	_infos;

			void	_create(void);
			void	_set_infos(void);
			void	_bind(void);

			class CreateSocketError : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31merror creating socket\e[0m");
					}
			};

			class BindSocketError : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31merror binding socket\e[0m");
					}
			};

		public:
			Socket(void);
			~Socket(void);
			
			void start_listening(int backlog);
			
			int get_socket_fd(void);
	};
}

#endif
