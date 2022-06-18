/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:15:49 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/17 20:31:49 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTEN_HPP
#define LISTEN_HPP

#include <string>

namespace ft
{
	class Listen
	{
		private:
			std::string	_host;
			std::string	_port;

		public:
			Listen(void);
			Listen(ft::Listen const &other);
			~Listen(void);

			ft::Listen	&operator=(ft::Listen const &right_hand_side);

			void set_host(std::string host);
			void set_port(std::string port);

			std::string get_host(void);
			std::string get_port(void);
		};
}

#endif
