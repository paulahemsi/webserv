/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:47:26 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/18 18:33:44 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <string>
#include <string.h>
#include <stdlib.h>
#include "ServerData.hpp"
#include "LocationData.hpp"

#define SERVER_BEGIN "server {"
#define SERVER_END "};"
#define LOCATION_BEGIN "location"
#define LOCATION_END "}"
#define LISTEN "listen"
#define SERVER_NAME "server_name"
#define ROOT "root"
#define ERROR_PAGE "error_page"
#define BODY_SIZE "client_body_size"
#define ACCEPTED_METHODS "accepted_methods"
#define INDEX "index"
#define REDIRECTION "redirection"
#define AUTOINDEX "autoindex"

namespace ft
{
	class Parser
	{
		private:
			std::vector<ft::ServerData>	_servers;
			std::ifstream				_file_stream;
			std::string					_line;

			void	_parse_file(void);
			void	_parse_server_block(void);
			void	_parse_location_block(ft::ServerData &server);

			void	_set_server_conf(ft::ServerData &server);
			void	_set_location_conf(ft::LocationData &location);
			void	_set_listen_conf(ft::ServerData &server);
			void	_set_server_name_conf(ft::ServerData &server);
			void	_set_error_page_conf(ft::ServerData &server);
			void	_set_root_conf(ft::ServerData &server);
			void	_set_body_size_conf(ft::ServerData &server);

			void	_set_prefix(ft::LocationData &location);
			void	_set_root_conf(ft::LocationData &location);
			void	_set_body_size_conf(ft::LocationData &location);
			void	_set_index_conf(ft::LocationData &location);
			void	_set_redirection_conf(ft::LocationData &location);
			void	_set_autoindex_conf(ft::LocationData &location);
			void	_set_accepted_methods_conf(ft::LocationData &location);

			bool		_line_is_not_empty(void);
			bool		_line_is_number(void);
			bool		_line_begins_with(const char *directive);
			void		_trim_line(const std::string chars_to_trim);
			void		_reduce_line_to_value(const char *directive);
			void		_check_if_only_one_argument(void);

			Parser(void);

		public:
			Parser(const char* filename);
			~Parser(void);
			
			std::vector<ft::ServerData> get_servers(void);
			
			class OpenFileError : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31merror opening configuration file\e[0m");
					}
			};

			class ServerConfigurationError : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31merror setting server block\e[0m");
					}
			};

			class LocationConfigurationError : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31merror setting location block\e[0m");
					}
			};
	};
}

#endif
