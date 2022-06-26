/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:34:30 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/26 11:59:07 by phemsi-a         ###   ########.fr       */
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
	_execute_request();
	ft::Response response;
	response.send(client_fd);
}

void	ft::RequestProcessor::_execute_request(void)
{
	ft::ServerData		server_data;
	ft::LocationData	location_data;
	std::cout << "Executing the request" << std::endl;
	server_data = _select_server(this->_request.get_server_name(), this->_socket->get_confs());
	try
	{
		location_data = this->_select_location(this->_request.get_request_field("URI"), server_data);
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

int	ft::RequestProcessor::_is_match(std::string name, std::vector<std::string> names)
{
	for (size_t i = 0; i < names.size(); i++)
		if (names[i] == name)
			return (i);
	return (ERROR);
}

ft::ServerData	ft::RequestProcessor::_select_server(std::string server_name, server_data_vector confs)
{
	server_data_vector::iterator it = confs.begin();
	server_data_vector::iterator it_end = confs.end();

	for (; it != it_end; it++)
		if (_is_match(server_name, it->get_server_name()) != ERROR)
			return (*it);
	return (confs[0]);
}

void	ft::RequestProcessor::_check_method(std::set<std::string> methods, std::string request_method)
{
	std::set<std::string>::iterator found = methods.find(request_method);
	if ( found == methods.end())
			throw (MethodNotAllowed());
}

ft::RequestProcessor::location_data_queue	ft::RequestProcessor::_check_locations(std::string uri, ft::ServerData &server)
{
	std::priority_queue<ft::LocationData> locations;
	for (size_t i = 0; i < server.get_location().size(); i++)
	{
		size_t found = uri.find(server.get_location()[i].get_prefix());
		if (found == 0)
			locations.push(server.get_location()[i]);
	}
	return (locations);
}

ft::LocationData	ft::RequestProcessor::_select_location(std::string uri, ft::ServerData &server)
{
	if (*uri.rbegin() != '/')
		uri.push_back('/');
	std::priority_queue<ft::LocationData> locations = _check_locations(uri, server);
	if (locations.empty())
		throw (NotFound());
	return (locations.top());
}
