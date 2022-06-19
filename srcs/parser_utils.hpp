/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 09:18:43 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/06/19 09:36:54 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_HPP
#define PARSER_UTILS_HPP

#include <string>
#include <string.h>

namespace ft
{
	bool	is_not_empty(std::string &line);
	bool	is_number(const std::string &line);
	bool	begins_with(const std::string &line, const char *directive);
	void	trim(std::string &line, const std::string chars_to_trim);
	void	reduce_to_value(std::string &line, const char *directive);
	bool	check_if_only_one_argument(const std::string &line);
}


#endif
