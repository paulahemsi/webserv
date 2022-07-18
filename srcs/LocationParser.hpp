/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationParser.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 09:43:39 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/18 19:15:57 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_PARSER_HPP
#define LOCATION_PARSER_HPP

#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "LocationData.hpp"
#include "parser_utils.hpp"

#define LOCATION_BEGIN "location"
#define LOCATION_END "}"
#define ROOT "root"
#define BODY_SIZE "client_body_size"
#define ACCEPTED_METHODS "accepted_methods"
#define INDEX "index"
#define REDIRECTION "redirection"
#define AUTOINDEX "autoindex"
#define ERROR_PAGE "error_page"
#define CGI "cgi"

namespace ft
{
	class LocationParser
	{
		private:
			ft::LocationData	_location;
			std::string			_line;

			void	_set_location_conf(void);
			void	_set_prefix(void);
			void	_set_root_conf(void);
			void	_set_body_size_conf(void);
			void	_set_index_conf(void);
			void	_set_redirection_conf(void);
			void	_set_autoindex_conf(void);
			void	_set_accepted_methods_conf(void);
			void	_set_error_page_conf(void);
			void	_set_cgi_conf(void);

		public:
			LocationParser(void);
			LocationParser(ft::LocationParser const &other);
			~LocationParser(void);

			ft::LocationParser	&operator=(ft::LocationParser const &right_hand_side);

			void				exec(std::ifstream &file_stream, std::string line);
			ft::LocationData	get_location(void);

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
