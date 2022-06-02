
#include "socket.hpp"

ft::Socket::Socket(void)
{
	_create();
	_set_infos();
	_bind();
}

void	ft::Socket::_create()
{
	this->_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_server_fd == ERROR)
		throw (CreateSocketError());
}

void	ft::Socket::_set_infos()
{
	memset((char*)&this->_server_infos, 0, sizeof(this->_server_infos));
	this->_server_infos.sin_family = AF_INET;
	this->_server_infos.sin_port = htons(PORT);
	this->_server_infos.sin_addr.s_addr = htonl(INADDR_ANY);
}

void	ft::Socket::_bind()
{
	if (bind(this->_server_fd, (struct sockaddr *)&this->_server_infos, sizeof(this->_server_infos)) == ERROR)
		throw (BindSocketError());
}

void ft::Socket::start_listening(int backlog)
{
	listen(this->_server_fd, backlog);
}

int ft::Socket::get_server_fd(void)
{
	return (this->_server_fd);
}


ft::Socket::~Socket(void)
{
	close(this->_server_fd);
}
