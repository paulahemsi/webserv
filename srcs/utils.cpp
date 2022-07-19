/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:06:24 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/18 23:42:19 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

bool fd_is_valid(int fd)
{
	return (fcntl(fd, F_GETFD) != ERROR || errno != EBADF);
}

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
	#ifdef DARWIN
		return (http_date(&s.st_mtimespec .tv_sec));
	#else
		return (http_date(&s.st_mtim.tv_sec));
	#endif
}

bool	is_executable(char* path)
{
	struct stat	buffer;

	if (stat(path, &buffer) != 0)
		return (false);
	if ((buffer.st_mode & S_IFMT) == S_IFDIR)
		return (false);
	if ((buffer.st_mode & S_IXUSR))
		return (true);
	return (false);
}

std::string	extract_extension(std::string path)
{
	size_t pos;
	size_t size;

	pos = path.rfind(".");
	if (pos == std::string::npos)
		return ("");
	size = path.size();
	return (path.substr(pos, size));
}

std::string to_upper(std::string s)
{
	for (size_t i = 0; i < s.length(); i++)
		s.at(i) = std::toupper(s[i]);
	return (s);
}
