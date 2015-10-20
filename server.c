/*
** server.c for my_ftp_server in /home/giubil
**
** Made by giubil
** Login   <giubil@epitech.net>
**
** Started on  Sun Mar 22 15:57:10 2015 giubil
** Last update Sun Apr 12 22:59:23 2015 giubil
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/select.h>
#include "server.h"

int	create_error(t_client_info *client, char *error_message)
{
  if (write(client->sockfd, error_message, strlen(error_message)) < 0)
    return (-1);
  return (0);
}

int		private_message(t_client_info *client, t_client_info *list,
			char *cmd)
{
  int		i;
  char		*buff;

  cmd += 4;
  i = -1;
  while (cmd[++i] != ' ');
  buff = strndup(cmd, i);
  cmd += i + 1;
  while (list && strcmp(list->nick, buff))
    list = list->next;
  if (!list)
    return (create_error(client, "Error, username not found"));
  if (write(list->sockfd, cmd, strlen(cmd)) < 0)
    return (-1);
  return (0);
}



int		select_loop(int newsockfd,
			    t_client_info **client_lists,
			    fd_set *readsets, t_channel **channels)
{
  int		ret_accept;
  int		i;

  ret_accept = select(get_bigger_fd(*client_lists, newsockfd),
		      readsets, NULL, NULL, NULL);
  if (ret_accept < 0)
    return (1);
  if (ret_accept > 0)
    {
      i = -1;
      while (++i < get_bigger_fd(*client_lists, newsockfd))
	{
	  if (i == newsockfd && FD_ISSET(newsockfd, readsets))
	    {
	      if (create_new_client(client_lists, newsockfd) < 0)
		return (-1);
	    }
	  else if (FD_ISSET(i, readsets)
		   && check_if_in_clients(i, *client_lists))
	    if (buffer_message(get_client_from_fd(i, *client_lists),
			       *client_lists, channels))
	      return (1);
	}
    }
  return (0);
}

int		 main(int argc, char **argv)
{
  int		newsockfd;
  fd_set	readsets;
  t_client_info	*client_lists;
  t_channel	*channels;

  if (argc < 2
      && (newsockfd = create_socket(6667)) < 0)
      return (1);
  else if (argc == 2 && (newsockfd = create_socket(atoi(argv[1]))) < 0)
    return (1);
  if (print_socket_port(newsockfd) < 0)
    return (1);
  client_lists = NULL;
  channels = NULL;
  while (42)
    {
      FD_ZERO(&readsets);
      FD_SET(newsockfd, &readsets);
      if (client_lists)
	add_client_to_watch_list(client_lists, &readsets);
      if (select_loop(newsockfd, &client_lists, &readsets, &channels))
	return (1);
    }
  return (0);
}
