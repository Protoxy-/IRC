/*
** server.h for server.h in /home/giubil
**
** Made by giubil
** Login   <giubil@epitech.net>
**
** Started on  Sun Mar 29 23:04:18 2015 giubil
** Last update Sun Apr 12 23:15:23 2015 giubil
*/

#ifndef SERVER_H_
# define SERVER_H_

#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

typedef struct		s_client_info
{
  char			*nick;
  char			*channel_name;
  char			command_buffer[8192];
  int			sockfd;
  int			error_code;
  char			*message_to_send;
  struct s_client_info	*next;
  struct s_client_info	*channel_next;
}			t_client_info;

typedef struct		s_channel
{
  char			*name;
  struct s_channel	*next;
  t_client_info		*channel_next;
}			t_channel;

int		create_socket(int);
int		login_command(int, int *);
int		get_bigger_fd(t_client_info *, int);
int		create_new_client(t_client_info **, int);
int		check_if_in_clients(int, t_client_info *);
int		buffer_message(t_client_info *, t_client_info *, t_channel **);
int		print_socket_port(int);
void		add_client_to_watch_list(t_client_info *, fd_set *);
t_client_info	*get_client_from_fd(int, t_client_info *);
int		create_error(t_client_info *, char *);
int		channel_does_not_exist(char *, t_channel *);
int		create_channel(char *, t_client_info *, t_channel **);
void		add_to_channel(char *, t_client_info *, t_channel **);
void		delete_client_from_channel(t_client_info *, t_channel **);
int		accept_new_connection(int);
int		handle_nick(t_client_info *, char *, t_client_info *);
int		join_channel(t_client_info *, char *, t_channel **);
int		part_channel(t_client_info *, t_channel **);
int		list_channels(t_channel *, char *, t_client_info *);
int		list_users(t_client_info *, t_channel *);
int		private_message(t_client_info *, t_client_info *, char *);
int		send_messages(t_client_info *, t_channel *, char *);

# define MOTD	"Welcome to my irc server\r\n"

#endif /* SERVER_H_ */
