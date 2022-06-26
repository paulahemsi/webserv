/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestProcessor.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:33:44 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/26 12:00:44 by phemsi-a         ###   ########.fr       */
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
		typedef std::priority_queue<ft::LocationData> location_data_queue;

		private:
			ft::Request		_request;
			ft::Response	_response;
			ft::Socket		*_socket;

			RequestProcessor(void);

			void			_execute_request(void);
			ft::ServerData	_select_server(std::string server_name, server_data_vector confs);
			int				_is_match(std::string name, std::vector<std::string> names);
			
			ft::LocationData	_select_location(std::string uri, ft::ServerData &server);
			location_data_queue	_check_locations(std::string uri, ft::ServerData &server);
			void	_check_method(std::set<std::string> methods, std::string request_method);
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
