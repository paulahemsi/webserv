/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:41:15 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/28 21:41:07 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>
#include <map>

#define SP		" "
#define CRLF	"\r\n"

namespace ft
{
	typedef std::pair<std::string, std::string> header_pair;
	typedef std::map<std::string, std::string> header_map;

	class Response
	{
		private:
			std::string		_http_version;
			unsigned int	_status_code;
			std::string		_reason_phrase;
			header_map		_header;
			std::string		_body;

			std::string _header_to_string(void);
			std::string _to_string(void);
			std::string	_int_to_string(int integer);
		
		public:
			Response(void);
			~Response(void);

			void	send(int client);
			void	show(void);
			void	set_header_field(std::string key, std::string value);
			void	set_status_code(unsigned int status_code);
			void	set_reason_phrase(std::string reason);
			void	set_content_length(unsigned int length);
			void	set_content_type(std::string type);
			void	set_body(std::string body);
	};
}

#endif
