/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:25:56 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/16 19:11:02 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERDATA_HPP
#define SERVERDATA_HPP

#include "LocationData.hpp"
#include "Listen.hpp"
#include <vector>

namespace ft
{
	class ServerData
	{
		private:
			ft::Listen						_listen;
			std::vector<std::string>		_server_name;
			std::string						_root;
			std::string						_error_pages;
			int								_body_size;
			std::vector<ft::LocationData>	_location;

		public:
			ServerData();
			~ServerData();

			ft::Listen					get_listen(void);
			std::vector<std::string>		get_server_name(void);
			std::string					get_root(void);
			std::string					get_error_pages(void);
			int							get_body_size(void);
			std::vector<ft::LocationData>	get_location(void);

			void	set_listen(ft::Listen listen);
			void	set_server_name(std::string new_server_name);
			void	set_root(std::string root);
			void	set_error_pages(std::string error_pages);
			void	set_body_size(int size_limit);
			void	set_location(ft::LocationData new_location_block);
	};
}

#endif
