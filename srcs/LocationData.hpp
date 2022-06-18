/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationData.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:30:32 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/17 20:43:38 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONDATA_HPP
#define LOCATIONDATA_HPP

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
			bool						_autoindex;
			int							_body_size;
			
		public:
			LocationData(void);
			~LocationData(void);

			std::set<std::string>		get_accepted_methods(void);
			std::vector<std::string>	get_index(void);
			std::string					get_redirection(void);
			std::string					get_root(void);
			bool						get_autoindex(void);
			int							get_body_size(void);

			void	add_accepted_method(std::string new_method);
			void	add_index(std::string new_index);
			void	set_redirection(std::string redirection_path);
			void	set_root(std::string root_path);
			void	set_autoindex(bool autoindex_value);
			void	set_body_size(int size_limit);
	};
}

#endif
