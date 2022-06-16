/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:37:20 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/16 20:29:01 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "LocationData.hpp"
#include "ServerData.hpp"
#include "WebServer.hpp"

#define ERROR		-1
#define BACKLOG		100

static void debug_location_data(ft::LocationData& location_data)
{
	std::cout << "TEST LOCATION DATA" << std::endl;

	std::cout << "Accepted methods: " << std::endl;
	
	std::vector<std::string> accepted_methods = location_data.get_accepted_methods();
	std::vector<std::string>::iterator it = accepted_methods.begin();
	for (; it != accepted_methods.end(); it++)
		std::cout << *it << std::endl;
	
	std::cout << "Index: " << std::endl;
	
	std::vector<std::string> index = location_data.get_index();
	std::vector<std::string>::iterator it_index = index.begin();
	for (; it_index != index.end(); it_index++)
		std::cout << *it_index << std::endl;
	
	std::cout << "Redirection: " << location_data.get_redirection() << std::endl;
	std::cout << "Root: " << location_data.get_root() << std::endl;
	std::cout << "Autoindex: " << location_data.get_autoindex() << std::endl;
	std::cout << "body_size: " << location_data.get_body_size() << std::endl;
}

static void debug_server_data(ft::ServerData& server_data)
{
	std::cout << "TEST SERVER DATA" << std::endl;

	std::cout << "Listen: " << server_data.get_listen().get_host() << ":" << server_data.get_listen().get_port() << std::endl;
	
	std::vector<std::string>::iterator it = server_data.get_server_name().begin();
	for (; it != server_data.get_server_name().end(); ++it)
	{
		std::cout << "server_name" << std::endl;
		std::cout << *it << std::endl;
	}
	
	std::cout << "Root: " << server_data.get_root() << std::endl;
	std::cout << "error_pages: " << server_data.get_error_pages() << std::endl;
	std::cout << "body_size: " << server_data.get_body_size() << std::endl;
	
	std::cout << "Location: " << std::endl;
	std::vector<ft::LocationData>::iterator it_location = server_data.get_location().begin();
	for (; it_location != server_data.get_location().end(); it_location++)
	{
		std::cout << "vou testar a location\n";
		debug_location_data(*it_location);
	}
}


#include "Listen.hpp"
static void test_listen(void)
{
	std::cout << "TEST LISTEN" << std::endl;

	ft::Listen listen;
	
	listen.set_host("host");
	listen.set_port("port");
	
	std::cout << listen.get_host() << listen.get_port() << std::endl;
	std::cout << "END TEST LISTEN" << std::endl;
	
}

int main(void)
{
	test_listen();

	ft::LocationData location_data;
	ft::ServerData server_data;
	debug_location_data(location_data);
	debug_server_data(server_data);
	
	int				ports[2] = {4444, 4445};



	/*
	try
	{
		ft::Parser parser(config file)
	}
	catch(){}
	
	ft::WebServer	web_server(parser.get_server_list());
	*/
	ft::WebServer	web_server(2, ports, BACKLOG);

	try
	{
		web_server.create_servers();
		web_server.run();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
		return(ERROR);
	}
	return (0);
}
