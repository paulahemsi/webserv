/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationData.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:30:32 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/23 10:09:00 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONDATA_HPP
#define LOCATIONDATA_HPP

#include "Cgi.hpp"
#include "ErrorPages.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <set>

namespace ft 
{
	class LocationData
	{
		private:
			std::set<std::string>		_accepted_methods;
			std::vector<std::string>	_index;
			std::string					_redirection;
			std::string					_root;
			std::string					_prefix;
			ft::Cgi						_cgi;
			ft::ErrorPages				_error_pages;
			bool						_autoindex;
			int							_body_size;
			
		public:
			LocationData(void);
			LocationData(ft::LocationData const &other);
			~LocationData(void);

			ft::LocationData	&operator=(ft::LocationData const &right_hand_side);
		
			std::set<std::string>		get_accepted_methods(void) const ;
			std::vector<std::string>	get_index(void) const ;
			std::string					get_redirection(void) const ;
			std::string					get_root(void) const ;
			std::string					get_prefix(void) const ;
			bool						get_autoindex(void) const ;
			int							get_body_size(void) const ;
			ft::ErrorPages				get_error_pages(void) const;
			std::string					get_error_page(std::string code) const;
			ft::Cgi						get_cgi(void) const;
			std::string					accepted_methods_to_string(void) const ;
			std::string					index_to_string(void) const ;

			void	add_accepted_method(std::string new_method);
			void	add_index(std::string new_index);
			void	set_redirection(std::string redirection_path);
			void	set_root(std::string root_path);
			void	set_prefix(std::string prefix);
			void	set_autoindex(bool autoindex_value);
			void	set_body_size(int size_limit);
			void	add_error_page(std::string code, std::string page_path);
			void	add_cgi_conf(std::string extension, std::string program_path);
			bool	has_error_page(std::string code) const;
			bool	has_redirection_set(void) const;
			bool	has_root_set(void) const;
			bool	operator>(ft::LocationData const &right_hand_side) const;
			bool	operator>=(ft::LocationData const &right_hand_side) const;
			bool	operator<(ft::LocationData const &right_hand_side) const;
			bool	operator<=(ft::LocationData const &right_hand_side) const;
			bool	operator==(ft::LocationData const &right_hand_side) const;
			bool	operator!=(ft::LocationData const &right_hand_side) const;
	};
	
}

std::ostream &operator<<(std::ostream &outputFile, const ft::LocationData &object);

#endif
