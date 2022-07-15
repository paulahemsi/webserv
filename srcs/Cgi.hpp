/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:42:55 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/15 18:01:36 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include <string>
#include <map>

namespace ft 
{
	class Cgi
	{
		private:
			std::map<std::string, std::string>	_program;


		public:
			Cgi(void);
			Cgi(ft::Cgi const &other);
			~Cgi(void);

			ft::Cgi	&operator=(ft::Cgi const &right_hand_side);

			std::map<std::string, std::string>	get_program_map(void) const;
			std::string							get_program(std::string extension) const;
			void								add_program(std::string extension, std::string path);
			bool								has_extension(std::string extension);
			size_t								size(void);
	};
	
}

std::ostream &operator<<(std::ostream &outputFile, const ft::Cgi &object);

#endif
