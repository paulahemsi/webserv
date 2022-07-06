/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phemsi-a <phemsi-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:06:54 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/05 23:02:56 by phemsi-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstring>

bool is_file(std::string path);
bool is_dir(std::string path);
std::string int_to_string(int integer);
std::string current_date_time(void);
std::string last_modification_time(std::string path);

#endif
