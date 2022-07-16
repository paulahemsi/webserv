NAME		:=	webserv

CC			:=	c++
CFLAGS		:= -Wall -Wextra -Werror
CFLAGS		+= -g
CFLAGS		+= -std=c++98
#CFLAGS		+= -fstandalone-debug

UNAME		:=	$(shell uname)

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
				ErrorPages.cpp \
				Cgi.cpp \
				CgiMediator.cpp \
				receive_line.cpp \

OBJS_DIR	:=	./objs/
OBJS		:=	$(addprefix $(OBJS_DIR), $(notdir $(SRCS:.cpp=.o)))

HEADER		=	utils.hpp \
				html_defines.hpp \
				http_status_code_defines.hpp \
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
				ErrorPages.hpp \
				Cgi.hpp \
				CgiMediator.hpp \
				receive_line.hpp \

INCLUDES	=

VPATH		:=	$(SRCS_DIR)

ifeq ($(UNAME),Darwin)
	OP_SYSTEM := -D DARWIN 
endif

all:	$(NAME)

$(OBJS_DIR)%.o:	%.cpp $(HEADER)
			$(CC) $(CFLAGS) $(OP_SYSTEM) -c $< -o $@

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
