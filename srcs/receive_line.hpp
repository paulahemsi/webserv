/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_line.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:35:08 by lfrasson          #+#    #+#             */
/*   Updated: 2022/07/09 15:50:56 by lfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RECEIVE_LINE_HPP
#define RECEIVE_LINE_HPP

#include <string>

void	receive_line(int fd, std::string &line, std::string delimiter);

#endif