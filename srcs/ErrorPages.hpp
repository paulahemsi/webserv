/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPages.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:10:02 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/18 21:22:36 by lfrasson         ###   ########.fr       */
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

			void		_add_default_page(std::string code);
			std::string	_get_default_path(std::string code);
			
		public:
			ErrorPages(void);
			ErrorPages(ft::ErrorPages const &other);
			~ErrorPages(void);

			ft::ErrorPages	&operator=(ft::ErrorPages const &right_hand_side);

			std::map<std::string, std::string>	get_pages(void) const;
			std::string     					get_page(std::string code) const;	
			void								add_page(std::string code, std::string path);
			bool								has_page(std::string code) const;
			void								set_defaults(void);
	};
	
}

std::ostream &operator<<(std::ostream &outputFile, const ft::ErrorPages &object);

#endif
