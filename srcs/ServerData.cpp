/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:26:55 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/18 20:58:25 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerData.hpp"
#include <iostream>
ft::ServerData::ServerData(void):
_listen(ft::Listen()),
_server_name(std::vector<std::string>()),
_root(""),
_error_pages(""),
_body_size(10000),
_location(std::vector<ft::LocationData>())
{
	this->_listen.set_host("localhost");
	this->_listen.set_port("80");
	return ;
}

ft::ServerData::~ServerData(void)
{
	return ;
}

ft::Listen	ft::ServerData::get_listen(void) const
{
	return (this->_listen);
}

std::vector<std::string>	ft::ServerData::get_server_name(void) const
{
	return (this->_server_name);
}

std::string	ft::ServerData::get_root(void) const
{
	return (this->_root);
}

std::string	ft::ServerData::get_error_pages(void) const
{
	return (this->_error_pages);
}

int	ft::ServerData::get_body_size(void) const
{
	return (this->_body_size);
}

std::vector<ft::LocationData>	ft::ServerData::get_location(void) const
{
	return (this->_location);
}

void ft::ServerData::set_listen(ft::Listen listen)
{
	this->_listen = listen;
}


void ft::ServerData::set_server_name(std::string new_server_name)
{
	this->_server_name.push_back(new_server_name);
}

void ft::ServerData::set_root(std::string root)
{
	this->_root = root;
}

void ft::ServerData::set_error_pages(std::string error_pages)
{
	this->_error_pages = error_pages;
}

void ft::ServerData::set_body_size(int size_limit)
{
	this->_body_size = size_limit;
}

void ft::ServerData::set_location(ft::LocationData new_location_block)
{
	this->_location.push_back(new_location_block);
}

std::string ft::ServerData::server_name_to_string(void) const
{
	std::string server_name_str;
	for (size_t i = 0; i < this->_server_name.size(); i++)
	{
		server_name_str += this->_server_name[i];
		server_name_str += "\n";
	}
	return (server_name_str);
}

std::ostream &operator<<(std::ostream &outputFile, const ft::ServerData &object)
{
	ft::LocationData location_data_str;
	
	for (size_t i = 0; i < object.get_location().size(); i++)
		outputFile	<< object.get_location()[i];

	outputFile	<< "Listen: " << object.get_listen() << std::endl
				<< "Server Name: " << object.server_name_to_string() << std::endl
				<< "Root : " << object.get_root() << std::endl
				<< "BodySize : " << object.get_body_size() << std::endl
				<< "Error Page: " << object.get_error_pages() << std::endl;

	return outputFile;
}
