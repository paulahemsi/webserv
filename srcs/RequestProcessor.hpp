/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:33:44 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/18 21:02:35 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_PROCESSOR_HPP
#define REQUEST_PROCESSOR_HPP

#include "parser_utils.hpp"

#include "CgiMediator.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"
#include "ServerData.hpp"
#include "LocationData.hpp"
#include "utils.hpp"
#include "html_defines.hpp"
#include "http_status_code_defines.hpp"
#include "ErrorsHttp.hpp"
#include <sys/wait.h>
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
			ft::Request				_request;
			ft::Response			_response;
			ft::Socket				*_socket;
			std::string				_uri;
			std::string				_server_name;
			std::string				_method;
			ft::ServerData			_server_data;
			ft::LocationData		_location_data;
			std::set<std::string>	_known_methods;
			int						_client;

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
			void				_define_prefix(std::string& prefix, ft::LocationData location);
			bool				_is_uri_in_location(ft::LocationData location);
			void				_check_method(void);
			void				_set_error(std::string code, std::string reason);
			void				_set_body(void);
			std::string			_define_path(void);
			void				_get_file(std::string path);
			bool				_is_file(std::string path, std::string& file_path);
			void				_check_slash(std::string &path);
			bool				_find_index(std::string& path);
			void				_build_autoindex(std::string path);
			void				_set_autoindex_h1(std::string &body);
			void				_set_autoindex_body(std::string &body, const char *path);
			void				_add_autoindex_link(std::string &body, struct dirent *entry);
			std::string			_get_error_page_path(std::string code);
			void				_execute_get(std::string path);
			void				_execute_post(void);
			void				_check_payload(void);
			void				_upload_file(void);
			std::string			_build_filepath(void);
			std::string			_build_file_location(void);
			bool				_is_cgi(std::string& path);
			bool				_has_cgi_configured(void);
			ft::Cgi				_get_cgi_configs(void);
			void				_execute_cgi(std::string file_path);

		public:
			RequestProcessor(ft::Socket *socket);
			~RequestProcessor(void);
			RequestProcessor(ft::RequestProcessor const &other);

			ft::RequestProcessor	&operator=(ft::RequestProcessor const &right_hand_side);

			void				run(int client_fd);
			ft::Request			get_request(void);
			ft::ServerData		get_server_data(void);
			ft::LocationData	get_location_data(void);
	};
}

#endif

