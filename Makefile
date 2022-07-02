NAME		:=	webserv

CC			:=	c++
CFLAGS		:= -Wall -Wextra -Werror
CFLAGS		+= -g
CFLAGS		+= -std=c++98
#CFLAGS		+= -fstandalone-debug

RM			:=	rm -rf

SRCS_DIR	:=	./srcs/
SRCS		:=	main.cpp \
				utils.cpp \
				Parser.cpp \
				parser_utils.cpp \
				LocationParser.cpp \
				ServerParser.cpp \
				LocationData.cpp \
				Listen.cpp \
				ServerData.cpp \
				WebServer.cpp \
				Socket.cpp \
				Poll.cpp \
				Client.cpp \
				Request.cpp \
				Response.cpp \
				RequestProcessor.cpp \

OBJS_DIR	:=	./objs/
OBJS		:=	$(addprefix $(OBJS_DIR), $(notdir $(SRCS:.cpp=.o)))

HEADER		=	utils.hpp \
				Parser.hpp \
				parser_utils.hpp \
				LocationParser.hpp \
				ServerParser.hpp \
				LocationData.hpp \
				Listen.hpp \
				ServerData.hpp \
				WebServer.hpp \
				Socket.hpp \
				Poll.hpp \
				Client.hpp \
				Request.hpp \
				Response.hpp \
				RequestProcessor.hpp \

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
