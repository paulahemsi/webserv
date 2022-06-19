/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationParser.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 09:45:40 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/19 13:05:46 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationParser.hpp"

ft::LocationParser::LocationParser(void)
{
	return ;
}

ft::LocationParser::LocationParser(ft::LocationParser const &other)
{
	*this = other;
}

ft::LocationParser &ft::LocationParser::operator=(ft::LocationParser const &right_hand_side)
{
	this->_location = right_hand_side._location;
	this->_line = right_hand_side._line;
	return (*this);
}

ft::LocationParser::~LocationParser(void)
{
	return ;
}

void ft::LocationParser::exec(std::ifstream &file_stream, std::string line)
{
	this->_line = line;
	_set_prefix();
	while (file_stream.good())
	{
		std::getline(file_stream, this->_line);
		if (ft::is_not_empty(this->_line))
		{
			if (this->_line == LOCATION_END)
				return ;
			_set_location_conf();
		}
	}
}

ft::LocationData ft::LocationParser::get_location(void)
{
	return (this->_location);
}

void ft::LocationParser::_set_location_conf(void)
{
	if (ft::begins_with(this->_line, ACCEPTED_METHODS))
		_set_accepted_methods_conf();
	else if (ft::begins_with(this->_line, INDEX))
		_set_index_conf();
	else if (ft::begins_with(this->_line, REDIRECTION))
		_set_redirection_conf();
	else if (ft::begins_with(this->_line, ROOT))
		_set_root_conf();
	else if (ft::begins_with(this->_line, AUTOINDEX))
		_set_autoindex_conf();
	else if (ft::begins_with(this->_line, BODY_SIZE))
		_set_body_size_conf();
	else
		throw (LocationConfigurationError());
}

void ft::LocationParser::_set_prefix(void)
{
	ft::reduce_to_value(this->_line, LOCATION_BEGIN);
	std::stringstream location_line(this->_line);
	std::string splited;

	std::getline(location_line, splited, ' ');
	this->_location.set_prefix(splited);
	std::getline(location_line, splited, ' ');
	splited.erase(splited.find_last_not_of(" \t") + 1);
	if (splited != "{")
		throw (LocationConfigurationError());
}

void ft::LocationParser::_set_body_size_conf(void)
{
	ft::reduce_to_value(this->_line, BODY_SIZE);
	if (ft::more_than_one_argument(this->_line))
		throw (LocationConfigurationError());
	if (ft::is_number(this->_line))
		this->_location.set_body_size(atoi(this->_line.c_str()));
	else
		throw (LocationConfigurationError());
}

void ft::LocationParser::_set_root_conf(void)
{
	ft::reduce_to_value(this->_line, ROOT);
	if (ft::more_than_one_argument(this->_line))
		throw (LocationConfigurationError());
	this->_location.set_root(this->_line);
}

void ft::LocationParser::_set_index_conf(void)
{
	ft::reduce_to_value(this->_line, INDEX);

	std::stringstream index_line(this->_line);
	std::string index_value;
	while (index_line.good())
	{
		std::getline(index_line, index_value, ' ');
		this->_location.add_index(index_value);
	}
}

void ft::LocationParser::_set_redirection_conf(void)
{
	ft::reduce_to_value(this->_line, REDIRECTION);
	if (ft::more_than_one_argument(this->_line))
		throw (LocationConfigurationError());
	this->_location.set_redirection(this->_line);
}

void ft::LocationParser::_set_autoindex_conf(void)
{
	ft::reduce_to_value(this->_line, AUTOINDEX);
	if (this->_line == "on")
		this->_location.set_autoindex(true);
	else if (this->_line == "off")
		this->_location.set_autoindex(false);
	else
		throw (LocationConfigurationError());
}

void ft::LocationParser::_set_accepted_methods_conf(void)
{
	ft::reduce_to_value(this->_line, ACCEPTED_METHODS);
	
	std::stringstream accepted_methods_line(this->_line);
	std::string accepted_methods_value;
	while (accepted_methods_line.good())
	{
		std::getline(accepted_methods_line, accepted_methods_value, ' ');
		this->_location.add_accepted_method(accepted_methods_value);
	}
}
