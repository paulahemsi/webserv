/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:33:44 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/26 13:21:48 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_PROCESSOR_HPP
#define REQUEST_PROCESSOR_HPP

#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"
#include "ServerData.hpp"
#include "LocationData.hpp"
#include <queue>
#include <vector>
#include <set>
#include <fstream>

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
			location_data_queue	_check_locations(void);
			void				_check_method(void);

		public:
			RequestProcessor(ft::Socket *socket);
			~RequestProcessor(void);
			
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
