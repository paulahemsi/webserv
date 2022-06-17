/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:37:20 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/16 16:05:28 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "LocationData.hpp"
#include "WebServer.hpp"

#define ERROR		-1
#define BACKLOG		100

int main(void)
{
	ft::LocationData	location_data;
	int				ports[2] = {4444, 4445};
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
