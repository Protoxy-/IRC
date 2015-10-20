##
## Makefile for LemiPC in /home/hoerte_f/rendu/PSU_2014_lemipc
## 
## Made by Francois Hoertel
## Login   <hoerte_f@epitech.net>
## 
## Started on  Mon Mar  2 09:18:26 2015 Francois Hoertel
## Last update Sun Apr 12 23:41:05 2015 giubil
##

NAMES	= server

NAMEC	= client

SERVER	= server.c			\
	server_connection.c		\
	additonal_channel_functions.c	\
	channel_functions_server.c	\
	create_client.c			\
	parse_commands.c		\

CLIENT	= err_sys.c \
	  get_param.c \
	  parsing.c \
	  client_init.c \
	  client_connexion.c \
	  client_interpret.c \
	  client_core.c \
	  client_file.c \
	  client.c

OBJS	= $(SERVER:.c=.o)

OBJC	= $(CLIENT:.c=.o)

CC	= gcc

RM	= rm -f

all:		$(NAMEC) $(NAMES)

$(NAMES):	 $(OBJS)
	$(CC) -o $(NAMES) $(OBJS)

$(NAMEC):	 $(OBJC)
	$(CC) -o $(NAMEC) $(OBJC)

clean:
	$(RM) $(OBJS) $(OBJC)

fclean:		clean
	$(RM) $(NAMES) $(NAMEC)

re:		fclean all

.PHONY:		all clean re fclean
