/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:33:44 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/02 18:40:47 by phemsi-a         ###   ########.fr       */
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
#include <queue>
#include <vector>
#include <set>
#include <fstream>
#include <streambuf>
#include <dirent.h>

#define AUTOINDEX_HTML_HEAD "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\"content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Autoindex</title></head>"
#define CLOSE_BODY "</body></html>"
#define CLOSE_H1 "</h1>"
#define OPEN_BODY_TITLE "<body><h1>Index of "
#define OPEN_ANCHOR_TAG "<p><a href=\""
#define MIDDLE_ANCHOR_TAG "\">"
#define CLOSE_ANCHOR_TAG "</a></p>"
#define SLASH "/"
#define NOT_FOUND_PATH "./www/error/404.html"
#define NOT_ALLOWED_PATH "./www/error/405.html"
#define NOT_FOUND_REASON "Not found"
#define NOT_ALLOWED_REASON "Method not allowed"
#define NOT_FOUND_CODE 404
#define NOT_ALLOWED_CODE 405

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
			ft::ServerData		_server_data;
			ft::LocationData	_location_data;

			RequestProcessor(void);

			void				_define_uri(void);
			void				_define_server_name(void);
			void				_execute_request(void);
			void				_select_server(void);
			void				_define_server(ft::ServerData server);
			int					_is_match(std::vector<std::string> names);
			void				_select_location(void);
			bool				_is_redirection(void);
			location_data_queue	_check_locations(void);
			void				_check_method(void);
			void				_set_error(unsigned int code, std::string reason, std::string path);
			void				_set_body(void);
			void				_get_file(std::string path, std::string file_path);
			void				_set_body_type(std::string path);
			bool				_is_file(std::string path, std::string& file_path);
			bool				_find_index(std::string path, std::string& file_path);
			void				_build_autoindex(std::string path);
			void				_set_autoindex_h1(std::string &body);
			void				_set_autoindex_body(std::string &body, const char *path);
			void				_add_autoindex_link(std::string &body, struct dirent *entry);

		public:
			RequestProcessor(ft::Socket *socket);
			~RequestProcessor(void);
			RequestProcessor(ft::RequestProcessor const &other);

			ft::RequestProcessor	&operator=(ft::RequestProcessor const &right_hand_side);

			void	run(std::string request_string,  int client_fd);
			
			class NotFound : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31mLocation not found\e[0m");
					}
			};
			class MethodNotAllowed : public std::exception
			{
				public:
					virtual const char* what() const throw()
					{
						return ("\e[0;31mMethod Not Allowed\e[0m");
					}
			};
	};
}

#endif
