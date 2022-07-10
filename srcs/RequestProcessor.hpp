/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:33:44 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/10 14:43:00 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_PROCESSOR_HPP
#define REQUEST_PROCESSOR_HPP

#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"
#include "ServerData.hpp"
#include "LocationData.hpp"
#include "utils.hpp"
#include "html_defines.hpp"
#include "http_methods_defines.hpp"
#include <queue>
#include <vector>
#include <set>
#include <fstream>
#include <streambuf>
#include <dirent.h>

namespace ft
{
	class RequestProcessor
	{
		typedef std::vector<ft::ServerData> server_data_vector;
		typedef std::vector<ft::LocationData> location_data_vector;
		typedef std::priority_queue<ft::LocationData> location_data_queue;

		private:
			ft::Request			_request;
			ft::Response		_response;
			ft::Socket			*_socket;
			std::string			_uri;
			std::string			_server_name;
			std::string			_method;
			ft::ServerData		_server_data;
			ft::LocationData	_location_data;

			RequestProcessor(void);

			void				_define_uri(void);
			void				_define_server_name(void);
			void				_execute_request(void);
			void				_execute_delete(std::string path);
			void				_select_server(void);
			void				_define_server(const ft::ServerData& server);
			int					_is_match(std::vector<std::string> names);
			void				_select_location(void);
			bool				_is_redirection(void);
			location_data_queue	_check_locations(void);
			void				_check_method(void);
			void				_set_error(std::string code, std::string reason);
			void				_set_body(void);
			void				_get_file(std::string path, std::string file_path);
			bool				_is_file(std::string path, std::string& file_path);
			bool				_find_index(std::string path, std::string& file_path);
			void				_build_autoindex(std::string path);
			void				_set_autoindex_h1(std::string &body);
			void				_set_autoindex_body(std::string &body, const char *path);
			void				_add_autoindex_link(std::string &body, struct dirent *entry);
			std::string			_get_error_page_path(std::string code);
			void				_execute_get(std::string path);
			void				_execute_post(void);
			std::string			_build_filepath(void);

		public:
			RequestProcessor(ft::Socket *socket);
			~RequestProcessor(void);
			RequestProcessor(ft::RequestProcessor const &other);

			ft::RequestProcessor	&operator=(ft::RequestProcessor const &right_hand_side);

			void	run(int client_fd);

			class ErrorsHttp : public std::exception
			{
				public:
					virtual const char* code() const throw()
					{
						return ("");
					}
					
					virtual const char* reason() const throw()
					{
						return ("");
					}
			};

			class NotFound : public ft::RequestProcessor::ErrorsHttp
			{
				public:
					virtual const char* code() const throw()
					{
						return (NOT_FOUND_CODE);
					}
					
					virtual const char* reason() const throw()
					{
						return (NOT_FOUND_REASON);
					}
			};
			
			class MethodNotAllowed : public ft::RequestProcessor::ErrorsHttp
			{
				public:
					virtual const char* code() const throw()
					{
						return (NOT_ALLOWED_CODE);
					}
					
					virtual const char* reason() const throw()
					{
						return (NOT_ALLOWED_REASON);
					}
			};
			
			class Forbidden : public ft::RequestProcessor::ErrorsHttp
			{
				public:
					virtual const char* code() const throw()
					{
						return (FORBIDDEN_CODE);
					}
					
					virtual const char* reason() const throw()
					{
						return (FORBIDDEN_REASON);
					}
			};
			
			class InternalServerError : public ft::RequestProcessor::ErrorsHttp
			{
				public:
					virtual const char* code() const throw()
					{
						return (SERVER_ERROR_CODE);
					}
					
					virtual const char* reason() const throw()
					{
						return (SERVER_ERROR_REASON);
					}
			};
	};
}

#endif

