/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:49:31 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/19 12:40:45 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_PARSER_HPP
#define SERVER_PARSER_HPP

#include "ServerData.hpp"
#include "parser_utils.hpp"
#include "LocationParser.hpp"
#include <sstream>
#include <fstream>
#include <string>

#define SERVER_BEGIN "server {"
#define SERVER_END "};"
#define LOCATION_BEGIN "location"
#define LOCATION_END "}"
#define LISTEN "listen"
#define SERVER_NAME "server_name"
#define ROOT "root"
#define ERROR_PAGE "error_page"
#define BODY_SIZE "client_body_size"
#define INDEX "index"

namespace ft
{
	class ServerParser
	{
		private:
			ft::ServerData	_server;
			std::string		_line;

			void	_parse_location_block(std::ifstream &file_stream);
			void	_set_server_conf(void);
			void	_set_listen_conf(void);
			void	_set_server_name_conf(void);
			void	_set_error_page_conf(void);
			void	_set_root_conf(void);
			void	_set_body_size_conf(void);

		public:
			ServerParser(void);
			~ServerParser(void);

			void				exec(std::ifstream &file_stream, std::string line);
			ft::ServerData		get_server(void);

			class ServerConfigurationError : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31merror setting server block\e[0m");
					}
			};
	};
}

#endif
