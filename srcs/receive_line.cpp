/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_line.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:35:00 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/18 23:41:41 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "receive_line.hpp"

static bool has_delimiter(std::string line, std::string delimiter)
{
	return (line.rfind(delimiter) != std::string::npos);
}

void	receive_line(int fd, std::string &line, std::string delimiter)
{
	char		buffer[2] = {0};
	ssize_t		num_of_bytes;	
	std::string temp_line;

	while (true)
	{
		num_of_bytes = recv(fd, buffer, 1, 0);
		if (num_of_bytes == ERROR)
			throw (std::exception());
		if (num_of_bytes == 0)
			break ;
		temp_line += buffer;
        if (has_delimiter(temp_line, delimiter))
            break ;
	}
	line = temp_line;
    if (has_delimiter(temp_line, delimiter))
		line.resize(line.rfind(delimiter));
}