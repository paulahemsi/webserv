/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:37:20 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/18 23:42:29 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <csignal>
#include "Parser.hpp"
#include "LocationData.hpp"
#include "ServerData.hpp"
#include "WebServer.hpp"

#define BACKLOG		100

ft::WebServer	web_server;
ft::Parser		parser;
std::string		file;

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
	exit(signal);
}

static int run_web_server(ft::Parser &parser)
{
	web_server.init(parser.get_servers(), BACKLOG);

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
	signal(SIGINT, handle_signal);

	if (define_configuration_file(argc, argv, file) == ERROR)
		return (ERROR);

	if (parse_configuration_file(parser, file) == ERROR)
		return(ERROR);

	if (run_web_server(parser) == ERROR)
		return (ERROR);

	return (0);
}
