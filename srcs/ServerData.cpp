/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:26:55 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/21 21:39:34 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerData.hpp"
#include <iostream>
ft::ServerData::ServerData(void):
_listen(ft::Listen()),
_server_name(std::vector<std::string>()),
_root(""),
_error_pages(ft::ErrorPages()),
_error_pages_default(ft::ErrorPages()),
_cgi(ft::Cgi()),
_body_size(1000000),
_location(std::vector<ft::LocationData>())
{
	this->_error_pages_default.set_defaults();
	return ;
}

ft::ServerData::ServerData(ft::ServerData const &other)
{
	*this = other;
}

ft::ServerData &ft::ServerData::operator=(ft::ServerData const &right_hand_side)
{
	this->_listen = right_hand_side._listen;
	this->_server_name = right_hand_side._server_name;
	this->_root = right_hand_side._root;
	this->_error_pages = right_hand_side._error_pages;
	this->_error_pages_default = right_hand_side._error_pages_default;
	this->_body_size = right_hand_side._body_size;
	this->_cgi = right_hand_side._cgi;
	this->_location = right_hand_side._location;
	return (*this);
}

ft::ServerData::~ServerData(void)
{
	return ;
}

bool	ft::ServerData::has_listen_set(void) const
{
	return (this->_listen.is_set());
}

bool	ft::ServerData::has_server_name_set(void) const
{
	return (!this->_server_name.empty());
}

bool	ft::ServerData::has_root_set(void) const
{
	return (!this->_root.empty());
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

ft::ErrorPages	ft::ServerData::get_error_pages(void) const
{
	return (this->_error_pages);
}

ft::ErrorPages	ft::ServerData::get_error_pages_default(void) const
{
	return (this->_error_pages_default);
}

std::string	ft::ServerData::get_error_page(std::string code) const
{
	return (this->_error_pages.get_page(code));
}

bool	ft::ServerData::has_error_page(std::string code) const
{
	return (this->_error_pages.has_page(code));
}

ft::Cgi	ft::ServerData::get_cgi(void) const
{
	return (this->_cgi);
}

std::string	ft::ServerData::get_default_error_page(std::string code) const
{
	return (this->_error_pages_default.get_page(code));
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


void ft::ServerData::add_server_name(std::string new_server_name)
{
	this->_server_name.push_back(new_server_name);
}

void ft::ServerData::set_root(std::string root)
{
	this->_root = root;
}

void ft::ServerData::add_error_page(std::string code, std::string page_path)
{
	this->_error_pages.add_page(code, page_path);
}

void ft::ServerData::add_cgi_conf(std::string extension, std::string program_path)
{
	this->_cgi.add_program(extension, program_path);
}

void ft::ServerData::set_body_size(int size_limit)
{
	this->_body_size = size_limit;
}

void ft::ServerData::add_location(ft::LocationData new_location_block)
{
	this->_location.push_back(new_location_block);
}

std::string ft::ServerData::server_name_to_string(void) const
{
	std::string server_name_str;
	for (size_t i = 0; i < this->_server_name.size(); i++)
	{
		server_name_str += this->_server_name[i];
		server_name_str += " ";
	}
	return (server_name_str);
}

std::ostream &operator<<(std::ostream &outputFile, const ft::ServerData &object)
{
	ft::LocationData location_data_str;

	outputFile	<< "Listen: " << std::endl << object.get_listen()
				<< "Server Name: " << object.server_name_to_string() << std::endl
				<< "Root : " << object.get_root() << std::endl
				<< "BodySize : " << object.get_body_size() << std::endl
				<< "Error Pages: " << object.get_error_pages() << std::endl
				<< "Error Pages Defaut: " << object.get_error_pages_default() << std::endl
				<< "Cgi: " << object.get_cgi() << std::endl
				<< "Location: " << std::endl;

	for (size_t i = 0; i < object.get_location().size(); i++)
		outputFile	<< object.get_location()[i];

	return outputFile;
}
