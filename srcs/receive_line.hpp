/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_line.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:35:08 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/18 23:42:56 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RECEIVE_LINE_HPP
#define RECEIVE_LINE_HPP

#include <string>
#include <sys/socket.h>
#include "utils.hpp"

void	receive_line(int fd, std::string &line, std::string delimiter);

#endif