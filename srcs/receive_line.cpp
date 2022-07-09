/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_line.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:35:00 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/09 16:17:14 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "receive_line.hpp"
#include <sys/socket.h>
void	receive_line(int fd, std::string &line, std::string delimiter)
{
	char buffer[2] = {0};
	std::string temp_line;

	while (recv(fd, buffer, 1, MSG_DONTWAIT) > 0)
	{
		temp_line += buffer;
        if (temp_line.rfind(delimiter) != std::string::npos)
            break ;
	}
	line = temp_line;
    if (temp_line.rfind(delimiter) != std::string::npos)
		line.resize(line.rfind(delimiter));
}