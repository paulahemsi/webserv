/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:57:35 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/26 11:39:41 by phemsi-a         ###   ########.fr       */
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
			
			std::map<std::string, std::string> _request;
			
			void _parse_request_line(std::string request_line);
			void _parse_header(std::stringstream &header);
			void _parse_body(std::string request_string);

		public:
			Request(void);
			Request(const Request& other);
			~Request(void);

			Request& operator= (const Request& other);

			void		init(std::string request_string);
			std::string get_request_field(std::string key);
			std::string get_server_name(void);
			//DEBUGGING FUNCTION
			void debugging_request(void);
	};
}

#endif 
