/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:47:26 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/09 19:41:22 by phemsi-a         ###   ########.fr       */
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
#include "ServerData.hpp"
#include "parser_utils.hpp"
#include "ServerParser.hpp"

#define SERVER_BEGIN "server {"

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

		public:
			Parser(void);
			Parser(ft::Parser const &other);
			~Parser(void);
			
			ft::Parser	&operator=(ft::Parser const &right_hand_side);

			void								exec(std::string filename);
			const std::vector<ft::ServerData>	&get_servers(void) const ;

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
	};
}

std::ostream &operator<<(std::ostream &outputFile, const ft::Parser &object);

#endif
