/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listen.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:15:49 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/16 19:18:44 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTEN_HPP
#define LISTEN_HPP

#include <utility>
#include <string>

namespace ft
{
	class Listen
	{
		private:
			std::pair<std::string, std::string> _listen;

		public:
			Listen(void);
			Listen(std::pair<std::string, std::string> const other);
			~Listen(void);

			ft::Listen	&operator=(ft::Listen const &right_hand_side);

			void set_host(std::string host);
			void set_port(std::string port);

			std::string get_host(void);
			std::string get_port(void);
	};
}

#endif
