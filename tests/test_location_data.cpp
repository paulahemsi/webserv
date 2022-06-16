/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_location_data.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:23:00 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/16 17:32:26 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../srcs/LocationData.hpp"

static void debug_location_data(ft::LocationData& location_data)
{
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

void test_location_data(void)
{
	ft::LocationData location_data;
	debug_location_data(location_data);
}
