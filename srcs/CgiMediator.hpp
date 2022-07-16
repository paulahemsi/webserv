/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiMediator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:27:03 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/16 14:54:15 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_MEDIATOR_HPP
#define CGI_MEDIATOR_HPP

#include <iostream>
#include <map>
#include <sys/wait.h>
#include <cstdio>
#include "Cgi.hpp"
#include "Response.hpp"
#include "ServerData.hpp"
#include "LocationData.hpp"
#include "Request.hpp"
#include "utils.hpp"
#include "parser_utils.hpp"
#include "http_status_code_defines.hpp"
#include "ErrorsHttp.hpp"

namespace ft
{
	typedef std::map<std::string, std::string> header_map;

	class CgiMediator
	{
		private:

			header_map	_header;
			ft::Cgi		_cgi;
			std::string	_file_path;
			char**		_env;
			char**		_cmd;

			void	_execute_cgi(std::string path);
			char **	_build_cmd(std::string file_path);
			ft::Cgi	_select_cgi(ft::ServerData server_data, ft::LocationData location_data);
			char **	_build_env(void);
			void	_save_env_variable(std::string key, std::string value, char** env_var);
			void	_run_script(int temp_fd);
			void	_get_script_output(std::FILE *temp_file, ft::Response& response);
			int		_get_file_size(std::FILE *temp_file);

		public:

			CgiMediator(void);
			~CgiMediator(void);
			
			CgiMediator(ft::CgiMediator const &other);

			ft::CgiMediator	&operator=(ft::CgiMediator const &right_hand_side);

			void	build(ft::ServerData server_data, ft::LocationData location_data, ft::Request request, std::string path);
			void	exec(ft::Response& response);
	};
}


#endif
