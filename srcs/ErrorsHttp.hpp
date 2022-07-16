/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorsHttp.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 12:43:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/16 13:29:50 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_HTTP_HPP
#define ERRORS_HTTP_HPP

#include <iostream>
#include "http_status_code_defines.hpp"

namespace ft
{
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
	
	class NotFound : public ft::ErrorsHttp
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
	
	class MethodNotAllowed : public ft::ErrorsHttp
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
	
	class Forbidden : public ft::ErrorsHttp
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
	
	class InternalServerError : public ft::ErrorsHttp
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
	
	class PayloadTooLarge : public ft::ErrorsHttp
	{
		public:
			virtual const char* code() const throw()
			{
				return (PAYLOAD_TOO_LARGE_CODE);
			}
			
			virtual const char* reason() const throw()
			{
				return (PAYLOAD_TOO_LARGE_REASON);
			}
	};
	
	class BadRequest : public ft::ErrorsHttp
	{
		public:
			virtual const char* code() const throw()
			{
				return (BAD_REQUEST_CODE);
			}
			
			virtual const char* reason() const throw()
			{
				return (BAD_REQUEST_REASON);
			}
	};
}
 
#endif
