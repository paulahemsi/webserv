NAME		:=	webserv

CC			:=	c++
CFLAGS		:= -Wall -Wextra -Werror
CFLAGS		+= -g
CFLAGS		+= -std=c++98

RM			:=	rm -rf

SRCS_DIR	:=	./srcs/
SRCS		:=	main.cpp \
				socket.cpp \
				Request.cpp

OBJS_DIR	:=	./objs/
OBJS		:=	$(addprefix $(OBJS_DIR), $(notdir $(SRCS:.cpp=.o)))

HEADER		=	socket.hpp \
				Request.hpp

INCLUDES	=

VPATH		:=	$(SRCS_DIR)

all:	$(NAME)

$(OBJS_DIR)%.o:	%.cpp
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ -o $@

$(OBJS): | $(OBJS_DIR)

$(OBJS_DIR):
			mkdir $(OBJS_DIR)

clean:
			$(RM) $(OBJS_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

PHONY:		all clean fclean re
