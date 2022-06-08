/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:41:15 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/05 23:48:01 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <unistd.h>
#include <string>
#include <sstream>

#define SP		" "
#define CRLF	"\r\n"

namespace ft
{
	class Response
	{
		private:
			std::string		_http_version;
			unsigned int	_status_code;
			std::string		_reason_phrase;
			std::string		_body;
		
		public:
			Response(void);
			~Response(void);

			std::string toString(void);
			void		send(int client);
	};
}

#endif