/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:15:49 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/21 18:54:33 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTEN_HPP
#define LISTEN_HPP

#include <iostream>
#include <string>

namespace ft
{
	class Listen
	{
		private:
			std::string	_host;
			int			_port;

		public:
			Listen(void);
			Listen(ft::Listen const &other);
			~Listen(void);

			ft::Listen	&operator=(ft::Listen const &right_hand_side);

			bool		is_set(void) const;
			void		set_host(std::string host);
			void		set_port(int port);
			std::string get_host(void) const;
			int			get_port(void) const;
		};
}

std::ostream &operator<<(std::ostream &outputFile, const ft::Listen &object);

#endif
