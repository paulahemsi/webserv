/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:57:35 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/18 20:31:18 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <cstring>
#include <stdlib.h>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "receive_line.hpp"
#include "utils.hpp"
#include "ErrorsHttp.hpp"

namespace ft
{
	typedef std::pair<std::string, std::string> request_pair;

	class Request
	{
		private:
			
			std::map<std::string, std::string>	_request;
			std::string							_body;
			int									_client_fd;

			void		_parse_request_line(void);
			void		_parse_header(void);
			void		_parse_body(void);
			void		_read_message_body(void);
			void		_receive_chunked_body(void);
			size_t		_get_chunk_size(void);
			size_t		_convert_chunk_size(std::string chunk_size);
			bool		_has(std::string key);
			bool		_has_mandatory_fields(void);
			bool		_has_no_body(void);
			void		_parse_filename(std::string header);
			void		_clean_header(std::string &temp_line);
			void		_clean_footer(std::string &temp_line);
			std::string	_extract_entity_body(std::string message_body);

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
			int									get_content_length(void);
			void								check_request(void);
			bool								is_multipart_form_data(void);
	};
}

std::ostream &operator<<(std::ostream &outputFile, const ft::Request &object);

#endif 
