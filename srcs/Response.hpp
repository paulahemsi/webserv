/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 01:41:15 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/05 22:16:41 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

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
		
		public:
			Response(void);
			~Response(void);

			std::string toString(void);
	};
}

#endif