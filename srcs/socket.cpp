
#include "socket.hpp"

ft::Socket::Socket(void): _port(PORT)
{
	_set_infos();
}

ft::Socket::Socket(int port): _port(port)
{
	_set_infos();
}

void	ft::Socket::create()
{
	_create();
	_bind();
}

void	ft::Socket::_create()
{
	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd == ERROR)
		throw (CreateSocketError());
}

void	ft::Socket::_set_infos()
{
	memset((char*)&this->_infos, 0, sizeof(this->_infos));
	this->_infos.sin_family = AF_INET;
	this->_infos.sin_port = htons(_port);
	this->_infos.sin_addr.s_addr = htonl(INADDR_ANY);
}

void	ft::Socket::_bind()
{
	if (bind(this->_fd, (struct sockaddr *)&this->_infos, sizeof(this->_infos)) == ERROR)
		throw (BindSocketError());
}

void ft::Socket::start_listening(int backlog)
{
	listen(this->_fd, backlog);
}

int ft::Socket::get_fd(void)
{
	return (this->_fd);
}


ft::Socket::~Socket(void)
{
	close(this->_fd);
}
