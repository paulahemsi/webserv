/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiMediator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:27:03 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/15 21:33:10 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_MEDIATOR_HPP
#define CGI_MEDIATOR_HPP

#include <iostream>
#include <map>
#include <sys/wait.h>
#include "Cgi.hpp"
#include "ServerData.hpp"
#include "LocationData.hpp"
#include "Request.hpp"
#include "utils.hpp"
#include "parser_utils.hpp"
#include "http_methods_defines.hpp"

namespace ft
{
	class CgiMediator
	{
		private:

			ft::Request			_request;
			ft::ServerData		_server_data;
			ft::LocationData	_location_data;
			std::string			_file_path;
			char**				_env;
			char**				_cmd;

			void	_execute_cgi(std::string path);
			char **	_build_cmd(std::string file_path);
			ft::Cgi	_get_cgi_configs(void);
			char **	_build_env(void);
			void	_free_cmd(void);
			void	_free_env(void);
			void	_free(char **char_matrix);

		public:

			CgiMediator(void);
			~CgiMediator(void);
			
			CgiMediator(ft::CgiMediator const &other);

			ft::CgiMediator	&operator=(ft::CgiMediator const &right_hand_side);

			void	build(ft::ServerData server_data, ft::LocationData location_data, ft::Request request, std::string path);
			void	exec(void);
			
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
			class InternalServerError : public ft::CgiMediator::ErrorsHttp
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
