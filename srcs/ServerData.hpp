/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:25:56 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/21 20:03:07 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERDATA_HPP
#define SERVERDATA_HPP

#include "LocationData.hpp"
#include "Listen.hpp"
#include "ErrorPages.hpp"
#include "Cgi.hpp"
#include <vector>

namespace ft
{
	class ServerData
	{
		private:
			ft::Listen						_listen;
			std::vector<std::string>		_server_name;
			std::string						_root;
			ft::ErrorPages					_error_pages;
			ft::ErrorPages					_error_pages_default;
			ft::Cgi							_cgi;
			int								_body_size;
			std::vector<ft::LocationData>	_location;

		public:
			ServerData();
			ServerData(ft::ServerData const &other);
			~ServerData();

			ft::ServerData	&operator=(ft::ServerData const &right_hand_side);

			ft::Listen						get_listen(void) const;
			std::vector<std::string>		get_server_name(void) const;
			std::string						get_root(void) const;
			std::string						get_error_page(std::string code) const;
			std::string						get_default_error_page(std::string code) const;
			ft::ErrorPages					get_error_pages(void) const;
			ft::ErrorPages					get_error_pages_default(void) const;
			ft::Cgi							get_cgi(void) const;
			int								get_body_size(void) const;
			std::vector<ft::LocationData>	get_location(void) const;
			bool							has_listen_set(void) const;
			bool							has_server_name_set(void) const;
			bool							has_root_set(void) const;

			std::string	server_name_to_string(void) const; 

			void		set_listen(ft::Listen listen);
			void		add_server_name(std::string new_server_name);
			void		set_root(std::string root);
			void		set_body_size(int size_limit);
			void		add_location(ft::LocationData new_location_block);
			void		add_error_page(std::string code, std::string page_path);
			void		add_cgi_conf(std::string extension, std::string program_path);
			bool		has_error_page(std::string code) const;
	};
}

std::ostream &operator<<(std::ostream &outputFile, const ft::ServerData &object);

#endif
