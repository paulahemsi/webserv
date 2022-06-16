/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationData.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:31:20 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/16 16:20:33 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	#include "LocationData.hpp"

	ft::LocationData::LocationData(void):
	_accepted_methods(std::vector<std::string>()),
	_index(std::vector<std::string>()),
	_redirection(""),
	_root(""),
	_autoindex(false),
	_body_size(10000)
	{
		_accepted_methods.push_back(static_cast<std::string>("GET"));
	}
	
	ft::LocationData::~LocationData(void)
	{
	}
	
	void ft::LocationData::set_accepted_methods(std::string new_method)
	{
		this->_accepted_methods.push_back(new_method);
	}
	
	void ft::LocationData::set_index(std::string new_index)
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
	
	void ft::LocationData::set_autoindex(bool autoindex_value)
	{
		this->_autoindex = autoindex_value;
	}
	
	void ft::LocationData::set_body_size(int size_limit)
	{
		this->_body_size = size_limit;
	}
	
	std::vector<std::string> ft::LocationData::get_accepted_methods(void)
	{
		return (this->_accepted_methods);
	}
	
	std::vector<std::string> ft::LocationData::get_index(void)
	{
		return (this->_index);
	}
	
	std::string ft::LocationData::get_redirection(void)
	{
		return (this->_redirection);
	}
	
	std::string ft::LocationData::get_root(void)
	{
		return (this->_root);
	}
	
	bool ft::LocationData::get_autoindex(void)
	{
		return (this->_autoindex);
	}
	
	int ft::LocationData::get_body_size(void)
	{
		return (this->_body_size);
	}
	