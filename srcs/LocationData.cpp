/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationData.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:31:20 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/23 10:08:48 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationData.hpp"

ft::LocationData::LocationData(void):
_accepted_methods(std::set<std::string>()),
_index(std::vector<std::string>()),
_redirection(""),
_root(""),
_prefix(""),
_cgi(ft::Cgi()),
_error_pages(ft::ErrorPages()),
_autoindex(false),
_body_size(0)
{
	this->_accepted_methods.insert("GET");
	return ;
}

ft::LocationData::LocationData(ft::LocationData const &other)
{
	*this = other;
}

ft::LocationData &ft::LocationData::operator=(ft::LocationData const &right_hand_side)
{
	this->_accepted_methods = right_hand_side._accepted_methods;
	this->_index = right_hand_side._index;
	this->_redirection = right_hand_side._redirection;
	this->_root = right_hand_side._root;
	this->_prefix = right_hand_side._prefix;
	this->_autoindex = right_hand_side._autoindex;
	this->_body_size = right_hand_side._body_size;
	this->_cgi = right_hand_side._cgi;
	this->_error_pages = right_hand_side._error_pages;
	return (*this);
}

ft::LocationData::~LocationData(void)
{
}

void ft::LocationData::add_accepted_method(std::string new_method)
{
	this->_accepted_methods.insert(new_method);
}

void ft::LocationData::add_index(std::string new_index)
{
	this->_index.push_back(new_index);
}

void ft::LocationData::set_redirection(std::string redirection_path)
{
	this->_redirection = redirection_path;
}

void ft::LocationData::set_root(std::string root_path)
{
	this->_root = root_path;
}

void ft::LocationData::set_prefix(std::string prefix)
{
	this->_prefix = prefix;
}

void ft::LocationData::set_autoindex(bool autoindex_value)
{
	this->_autoindex = autoindex_value;
}

void ft::LocationData::set_body_size(int size_limit)
{
	this->_body_size = size_limit;
}

void ft::LocationData::add_error_page(std::string code, std::string page_path)
{
	this->_error_pages.add_page(code, page_path);
}

void ft::LocationData::add_cgi_conf(std::string extension, std::string program_path)
{
	this->_cgi.add_program(extension, program_path);
}

ft::ErrorPages	ft::LocationData::get_error_pages(void) const
{
	return (this->_error_pages);
}

std::string	ft::LocationData::get_error_page(std::string code) const
{
	return (this->_error_pages.get_page(code));
}

bool ft::LocationData::has_error_page(std::string code) const
{
	return (this->_error_pages.has_page(code));
}

bool ft::LocationData::has_redirection_set(void) const
{
	return (!this->_redirection.empty());
}

bool ft::LocationData::has_root_set(void) const
{
	return (!this->_root.empty());
}

ft::Cgi	ft::LocationData::get_cgi(void) const
{
	return (this->_cgi);
}

std::set<std::string> ft::LocationData::get_accepted_methods(void) const
{
	return (this->_accepted_methods);
}

std::vector<std::string> ft::LocationData::get_index(void) const
{
	return (this->_index);
}

std::string ft::LocationData::get_redirection(void) const
{
	return (this->_redirection);
}

std::string ft::LocationData::get_root(void) const
{
	return (this->_root);
}

std::string ft::LocationData::get_prefix(void) const
{
	return (this->_prefix);
}

bool ft::LocationData::get_autoindex(void) const
{
	return (this->_autoindex);
}

int ft::LocationData::get_body_size(void) const
{
	return (this->_body_size);
}

std::string ft::LocationData::accepted_methods_to_string(void) const
{
	std::string accepted_methods_str;
	std::set<std::string>::iterator it_begin = this->_accepted_methods.begin();
	std::set<std::string>::iterator it_end = this->_accepted_methods.end();
	while (it_begin != it_end)
	{
		accepted_methods_str += *it_begin;
		accepted_methods_str += " ";
		it_begin++;
	}
	return (accepted_methods_str);
}

std::string ft::LocationData::index_to_string(void) const
{
	std::string index_str;
	for (size_t i = 0; i < this->_index.size(); i++)
	{
		index_str += this->_index[i];
		index_str += " ";
	}
	return (index_str);
}

bool	ft::LocationData::operator>(ft::LocationData const &right_hand_side) const
{
	return (this->_prefix > right_hand_side._prefix);
}

bool	ft::LocationData::operator>=(ft::LocationData const &right_hand_side) const
{
	return (this->_prefix >= right_hand_side._prefix);
}

bool	ft::LocationData::operator<(ft::LocationData const &right_hand_side) const
{
	return (this->_prefix < right_hand_side._prefix);
}

bool	ft::LocationData::operator<=(ft::LocationData const &right_hand_side) const
{
	return (this->_prefix <= right_hand_side._prefix);
}

bool	ft::LocationData::operator==(ft::LocationData const &right_hand_side) const
{
	return (this->_prefix == right_hand_side._prefix);
}

bool	ft::LocationData::operator!=(ft::LocationData const &right_hand_side) const
{
	return (this->_prefix != right_hand_side._prefix);
}

std::ostream &operator<<(std::ostream &outputFile, const ft::LocationData &object)
{
	outputFile	<< "Prefix : " << object.get_prefix() << std::endl
				<< "Root : " << object.get_root() << std::endl
				<< "Redirection : " << object.get_redirection() << std::endl
				<< "Autoindex : " << object.get_autoindex() << std::endl
				<< "BodySize : " << object.get_body_size() << std::endl
				<< "Accepted Methods: " << std::endl
					<< object.accepted_methods_to_string() << std::endl
				<< "Index: " << object.index_to_string() << std::endl
				<< "Error Pages: " << object.get_error_pages() << std::endl
				<< "Cgi: " << object.get_cgi() << std::endl;
	
	return outputFile;
}
