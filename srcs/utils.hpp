/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:06:54 by phemsi-a          #+#    #+#             */
/*   Updated: 2022/07/03 17:27:54 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <ctime>

bool is_file(std::string path);
bool is_dir(std::string path);
std::string int_to_string(int integer);
std::string current_date_time(void);

#endif
