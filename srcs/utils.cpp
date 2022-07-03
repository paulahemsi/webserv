/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:06:24 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/03 17:27:54 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

bool is_file(std::string path)
{
	struct stat s;
	if ((stat(path.c_str(), &s) == 0) && (s.st_mode & S_IFREG))
		return (true);
	return (false);
}

bool is_dir(std::string path)
{
	struct stat s;
	if ((stat(path.c_str(), &s) == 0) && (s.st_mode & S_IFDIR))
		return (true);
	return (false);
}

std::string int_to_string(int integer)
{
	std::stringstream str_stream;

	str_stream << integer;
	return (str_stream.str());
}

std::string current_date_time(void)
{
	time_t	now;
	tm		*gmt_time;
	char	buff[29];

	now = time(NULL);
	gmt_time = gmtime(&now);
	strftime(buff, 29, "%a, %d %b %Y %T GMT", gmt_time);
	return (buff);
}