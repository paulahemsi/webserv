/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiMediator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:27:03 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/15 18:14:13 by phemsi-a         ###   ########.fr       */
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
#include "RequestProcessor.hpp"

namespace ft
{
	class CgiMediator
	{
		private:

			ft::Request			_request;
			ft::ServerData		_server_data;
			ft::LocationData	_location_data;
			std::string			_file_path;
			ft::Cgi				_cgi;
			char**				_env;
			char**				_cmd;

			void	_execute_cgi(std::string path);
			char **	_build_cmd(std::string file_path);
			ft::Cgi	_get_cgi_configs(void);
			char **	_build_env(void);

		public:

			CgiMediator(void);
			~CgiMediator(void);
			
			CgiMediator(ft::CgiMediator const &other);

			ft::CgiMediator	&operator=(ft::CgiMediator const &right_hand_side);

			void	build(ft::RequestProcessor, std::string path);
			void	exec(void);
	};
}


#endif
