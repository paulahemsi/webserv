/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:06:54 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/14 20:24:56 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <sstream>
#include <ctime>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>

bool fd_is_valid(int fd);
bool is_file(std::string path);
bool is_dir(std::string path);
std::string int_to_string(int integer);
std::string current_date_time(void);
std::string last_modification_time(std::string path);
std::string	extract_extension(std::string path);
bool	is_executable(std::string path);

#endif
