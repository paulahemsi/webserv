/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:57:35 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/10 10:43:23 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

// #include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "receive_line.hpp"

namespace ft
{
	typedef std::pair<std::string, std::string> request_pair;

	class Request
	{
		private:
			
			std::map<std::string, std::string>	_request;
			std::string							_body;
			int									_client_fd;

			void	_parse_request_line(void);
			void	_parse_header(void);
			void	_parse_body(void);
			void	_read_message_body(void);
			int		_get_body_message_length(void);
			void	_receive_chunked_body(void);
			bool	_has(std::string key);
			bool	_has_mandatory_fields(void);
			bool	_has_no_body(void);

		public:
			Request(void);
			Request(const Request& other);
			~Request(void);

			Request& operator= (const Request& other);

			void								init(int client_fd);
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
