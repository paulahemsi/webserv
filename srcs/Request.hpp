/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:57:35 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/07 21:04:29 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <map>

namespace ft
{
	typedef std::pair<std::string, std::string> request_pair;

	class Request
	{
		private:
			
			std::map<std::string, std::string>	_request;
			std::string							_body_line;
			
			void	_parse_request_line(std::string request_line);
			void	_parse_header(std::stringstream &header);
			void	_parse_body(std::string request_string, int client_fd);
			bool	_has(std::string key);
			bool	_has_mandatory_fields(void);

		public:
			Request(void);
			Request(const Request& other);
			~Request(void);

			Request& operator= (const Request& other);

			void								init(std::string request_string, int client_fd);
			std::string							get_request_field(std::string key);
			std::string							get_server_name(void);
			std::map<std::string, std::string>	get_request(void) const;
			std::string							get_method(void);
			void								check_request(void);
			
			class BadRequest : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31mBad Request\e[0m");
					}
			};
	};
}

std::ostream &operator<<(std::ostream &outputFile, const ft::Request &object);

#endif 
