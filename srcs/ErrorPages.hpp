/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPages.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:10:02 by lfrasson          #+#    #+#             */
/*   Updated: 2022/06/29 20:08:16 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_PAGES
#define ERROR_PAGES

#include <iostream>
#include <string>
#include <map>

namespace ft 
{
	class ErrorPages
	{
		private:
			std::map<std::string, std::string>	_pages;
			
		public:
			ErrorPages(void);
			ErrorPages(ft::ErrorPages const &other);
			~ErrorPages(void);

			ft::ErrorPages	&operator=(ft::ErrorPages const &right_hand_side);

			std::map<std::string, std::string> getPages(void) const;
	};
	
}

std::ostream &operator<<(std::ostream &outputFile, const ft::ErrorPages &object);

#endif
