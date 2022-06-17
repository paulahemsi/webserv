/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:47:26 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/17 11:54:35 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <fstream>
#include "Server.hpp"

#include <string>

namespace ft
{
	class Parser
	{
		private:
			std::vector<ft::Server>	_servers;
			std::ifstream			_file_stream;
			
			void					_parse_file(void);

			Parser(void);

		public:
			Parser(const char* filename);
			~Parser(void);
			
			std::vector<ft::Server> get_servers(void);
			
			class OpenFileError : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31merror opening configuration file\e[0m");
					}
			};
	};
}

#endif
