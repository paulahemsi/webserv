/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:37:20 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/19 09:13:12 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Parser.hpp"
#include "LocationData.hpp"
#include "ServerData.hpp"
#include "WebServer.hpp"

#define ERROR		-1
#define BACKLOG		100

static bool wrong_arguments(int argc)
{
	if (argc != 2)
	{
		std::cout << "\e[0;31mUsage: ./webserv path_to_configuration_file\e[0m" << std::endl;
		return (true);
	}
	return (false);
}

static int parse_configuration_file(ft::Parser &parser, char *filename)
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

int run_web_server(ft::Parser &parser)
{
	ft::WebServer	web_server(parser.get_servers(), BACKLOG);
	
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

int main(int argc, char **argv)
{
	ft::Parser		parser;

	if (wrong_arguments(argc))
		return (ERROR);

	if (parse_configuration_file(parser, argv[1]) == ERROR)
		return(ERROR);

	if (run_web_server(parser) == ERROR)
		return (ERROR);

	return (0);
}
