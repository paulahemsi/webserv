/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:34:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/26 12:20:05 by phemsi-a         ###   ########.fr       */
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
	this->_server_name = this->_request.get_server_name();
	_define_uri();
	_execute_request();
	ft::Response response;
	response.send(client_fd);
}

void ft::RequestProcessor::_define_uri(void)
{
	this->_uri = this->_request.get_request_field("URI");
	if (*this->_uri.rbegin() != '/')
		this->_uri.push_back('/');
}

void	ft::RequestProcessor::_execute_request(void)
{
	ft::ServerData		server_data;
	ft::LocationData	location_data;
	std::cout << "Executing the request" << std::endl;
	server_data = _select_server();
	try
	{
		location_data = _select_location(server_data);
		std::string redirection = location_data.get_redirection();
		if (redirection != "")
			std::cout << "--------Build Response with REDIRECTION--------" << std::endl;
		_check_method(location_data.get_accepted_methods(), this->_request.get_request_field("Method"));
		std::ifstream file_stream;
		//ver se tem root ou não para abrir arquivo
		//index ou não
		//file_stream.open();
	}
	catch(const std::exception& e)
	{
		//build error responses
		std::cout << e.what() << '\n';
	}
}

ft::ServerData	ft::RequestProcessor::_select_server(void)
{
	server_data_vector confs = this->_socket->get_confs();
	server_data_vector::iterator it = confs.begin();
	server_data_vector::iterator it_end = confs.end();

	for (; it != it_end; it++)
		if (_is_match(it->get_server_name()) != ERROR)
			return (*it);
	return (confs[0]);
}

int	ft::RequestProcessor::_is_match(std::vector<std::string> names)
{
	for (size_t i = 0; i < names.size(); i++)
		if (names[i] == this->_server_name)
			return (i);
	return (ERROR);
}

ft::LocationData	ft::RequestProcessor::_select_location(ft::ServerData &server)
{
	std::priority_queue<ft::LocationData> locations = _check_locations(server);
	if (locations.empty())
		throw (NotFound());
	return (locations.top());
}

ft::RequestProcessor::location_data_queue	ft::RequestProcessor::_check_locations(ft::ServerData &server)
{
	std::priority_queue<ft::LocationData> locations;
	for (size_t i = 0; i < server.get_location().size(); i++)
	{
		size_t found = this->_uri.find(server.get_location()[i].get_prefix());
		if (found == 0)
			locations.push(server.get_location()[i]);
	}
	return (locations);
}

void	ft::RequestProcessor::_check_method(std::set<std::string> methods, std::string request_method)
{
	std::set<std::string>::iterator found = methods.find(request_method);
	if ( found == methods.end())
			throw (MethodNotAllowed());
}
