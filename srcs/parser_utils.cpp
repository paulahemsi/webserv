/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 09:22:18 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/13 21:39:40 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.hpp"

static bool is_comment(std::string &line)
{
	ft::trim(line, " \t");
	ft::trim(line, " ");
	if (line[0] == '#')
		return (true);
	return (false);
}

bool	ft::is_empty(std::string &line)
{
	ft::trim(line, " \t");
	ft::trim(line, " ");
	return (line == "");
}

bool ft::line_is_valid(std::string &line)
{
	if (is_comment(line))
		return (false);
	if (is_empty(line))
		return (false);
	return (true);
}

bool	ft::is_number(const std::string &line)
{
	return (line.find_first_not_of("0123456789") == std::string::npos);
}

bool	ft::begins_with(const std::string &line, const char *directive)
{
	return (line.find(directive, 0) == 0);
}

void	ft::trim(std::string &line, const std::string chars_to_trim)
{
	line.erase(line.find_last_not_of(chars_to_trim) + 1);
	line.erase(0, line.find_first_not_of(chars_to_trim));
}

void	ft::reduce_to_value(std::string &line, const char *directive)
{
	line.erase(0, strlen(directive));
	ft::trim(line, " \t");
}

bool	ft::more_than_one_argument(const std::string &line)
{
	if (line.find(' ') != std::string::npos)
		return (true);
	if (line.find('\t') != std::string::npos)
		return (true);
	return (false);
}

