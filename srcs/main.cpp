/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:37:20 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/09 16:17:18 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <csignal>
#include "Parser.hpp"
#include "LocationData.hpp"
#include "ServerData.hpp"
#include "WebServer.hpp"

#define ERROR		-1
#define BACKLOG		100

ft::WebServer	web_server;

static int define_configuration_file(int argc, char **argv, std::string& filename)
{
	if (argc > 2)
	{
		std::cout << "\e[0;31mUsage: ./webserv path_to_configuration_file\e[0m" << std::endl;
		return (ERROR);
	}
	if (argc == 1)
		filename = "./conf/webserv.conf";
	else if (argc == 2)
		filename = argv[1];
	return (0);
}

static int parse_configuration_file(ft::Parser &parser,std::string filename)
{
	try
	{
		parser.exec(filename);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
		return(ERROR);
	}
	return (0);
}


static void handle_signal(int signal)
{
	std::cout << "SIGNAL: " << signal << std::endl;
	web_server.close_servers();
	exit(signal);
}

static int run_web_server(ft::Parser &parser)
{
	web_server.init(parser.get_servers(), BACKLOG);

	signal(SIGINT, handle_signal);
	
	try
	{
		web_server.create_sockets();
		web_server.run();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
		return(ERROR);
	}
	return (0);
}

int main(int argc, char **argv)
{
	ft::Parser		parser;
	std::string		file;

	if (define_configuration_file(argc, argv, file) == ERROR)
		return (ERROR);

	if (parse_configuration_file(parser, file) == ERROR)
		return(ERROR);

	if (run_web_server(parser) == ERROR)
		return (ERROR);

	return (0);
}
