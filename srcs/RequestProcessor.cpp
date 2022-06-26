/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:34:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/26 13:24:26 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestProcessor.hpp"

ft::RequestProcessor::RequestProcessor(void)
{
	return ;
}

ft::RequestProcessor::RequestProcessor(ft::Socket *socket):
_socket(socket)
{
	return ;
}

ft::RequestProcessor::~RequestProcessor(void)
{
	return ;
}

void ft::RequestProcessor::run(std::string request_string, int client_fd)
{
	this->_request.init(request_string);
	_define_server_name();
	_define_uri();
	_execute_request();

	ft::Response response;
	response.send(client_fd);
}

void ft::RequestProcessor::_define_server_name(void)
{
	this->_server_name = this->_request.get_server_name();
}

void ft::RequestProcessor::_define_uri(void)
{
	this->_uri = this->_request.get_request_field("URI");
	if (*this->_uri.rbegin() != '/')
		this->_uri.push_back('/');
}

void	ft::RequestProcessor::_execute_request(void)
{
	_select_server();
	try
	{
		_select_location();
		std::string redirection = this->_location_data.get_redirection();
		if (redirection != "")
			std::cout << "REDIR\n";
		_check_method();
		
	}
	catch(const std::exception& e)
	{
		//build error responses
		std::cout << e.what() << '\n';
	}
}

void	ft::RequestProcessor::_select_server(void)
{
	server_data_vector confs = this->_socket->get_confs();
	server_data_vector::iterator it = confs.begin();
	server_data_vector::iterator it_end = confs.end();

	for (; it != it_end; it++)
		if (_is_match(it->get_server_name()) != ERROR)
			return (_define_server(*it));
	_define_server(confs[0]);
}

int	ft::RequestProcessor::_is_match(std::vector<std::string> names)
{
	for (size_t i = 0; i < names.size(); i++)
		if (names[i] == this->_server_name)
			return (i);
	return (ERROR);
}

void	ft::RequestProcessor::_define_server(ft::ServerData server)
{
	this->_server_data = server;
}

void	ft::RequestProcessor::_select_location(void)
{
	std::priority_queue<ft::LocationData> locations = _check_locations();
	if (locations.empty())
		throw (NotFound());
	this->_location_data = locations.top();
}

ft::RequestProcessor::location_data_queue	ft::RequestProcessor::_check_locations(void)
{
	location_data_vector all_locations = this->_server_data.get_location();
	std::priority_queue<ft::LocationData> match_locations;
	std::string prefix;

	for (size_t i = 0; i < all_locations.size(); i++)
	{
		prefix = all_locations[i].get_prefix();
		size_t found = this->_uri.find(prefix);
		if (found == 0)
			match_locations.push(all_locations[i]);
	}
	return (match_locations);
}

void	ft::RequestProcessor::_check_method(void)
{
	std::set<std::string> methods = this->_location_data.get_accepted_methods();
	std::string request_method = this->_request.get_request_field("Method");

	std::set<std::string>::iterator found = methods.find(request_method);
	if (found == methods.end())
			throw (MethodNotAllowed());
}
