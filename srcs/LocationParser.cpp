/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationParser.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 09:45:40 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/23 10:10:47 by phemsi-a         ###   ########.fr       */
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
		if (ft::line_is_valid(this->_line))
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
	else if (ft::begins_with(this->_line, ERROR_PAGE))
		_set_error_page_conf();
	else if (ft::begins_with(this->_line, CGI))
		_set_cgi_conf();
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

void ft::LocationParser::_set_error_page_conf()
{
	ft::reduce_to_value(this->_line, ERROR_PAGE);
	if (!ft::more_than_one_argument(this->_line))
		throw (LocationConfigurationError());

	size_t				pos = this->_line.find_last_of(' ');
	std::string 		page_path = this->_line.substr(pos + 1);
	std::string			codes= this->_line.substr(0, pos);
	ft::trim(codes, " \t");

	std::stringstream 	ss_codes(codes);
	std::string 		code;
	while (ss_codes.good())
	{
		std::getline(ss_codes, code, ' ');
		this->_location.add_error_page(code, page_path);
	}
}

void ft::LocationParser::_set_cgi_conf()
{
	ft::reduce_to_value(this->_line, CGI);
	if (!ft::more_than_one_argument(this->_line))
		throw (LocationConfigurationError());

	std::stringstream cgi_line(this->_line);
	std::string extension;
	std::string path;

	for (size_t i = 1; cgi_line.good(); i++)
	{
		switch (i)
		{
		case 1:
			std::getline(cgi_line, extension, ' ');
			break;
		case 2:
			std::getline(cgi_line, path, ' ');
			break;
		case 3:
			throw (LocationConfigurationError());
		}
	}
	this->_location.add_cgi_conf(extension, path);
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
	if (this->_location.has_root_set())
		throw (LocationConfigurationError());
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
	if (this->_location.has_redirection_set())
		throw (LocationConfigurationError());
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
