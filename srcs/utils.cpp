/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:06:24 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/01 22:06:45 by phemsi-a         ###   ########.fr       */
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
