# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfrasson <lfrasson@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 11:18:40 by lfrasson          #+#    #+#              #
#    Updated: 2022/06/11 11:19:45 by lfrasson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

IMAGE		:=	nginx
CONTAINER	:=	nginx

build:
	docker build -t $(IMAGE) .

run:
	docker run -d --rm -p 4444:4444 --name $(CONTAINER) $(IMAGE)

exec:
	docker exec -it $(CONTAINER) /bin/bash

stop:
	docker stop $(CONTAINER)

.PHONY:	build run exec stop
