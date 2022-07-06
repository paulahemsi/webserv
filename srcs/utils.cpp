/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:06:24 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/06 23:52:52 by coder            ###   ########.fr       */
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

static std::string http_date(std::time_t *time)
{
	std::tm		*gmt_time;
	char		buff[64];

	memset(buff, 0, 64);
	gmt_time = gmtime(time);
	strftime(buff, 64, "%a, %d %b %Y %T GMT", gmt_time);
	return (buff);
}

std::string current_date_time(void)
{
	time_t	now;

	now = std::time(NULL);
	return (http_date(&now));
}

std::string last_modification_time(std::string path)
{
	struct stat s;
	
	if (stat(path.c_str(), &s) != 0)
	{
		//lança ServerError?
	}
	return (http_date(&s.st_mtim.tv_sec));
}
