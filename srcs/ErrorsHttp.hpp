/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorsHttp.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 12:43:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/16 12:44:51 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_HTTP_HPP
#define ERRORS_HTTP_HPP

#include <iostream>

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
}
 
#endif
