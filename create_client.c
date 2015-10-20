/*
** create_client.c for irc in /home/giubil
**
** Made by giubil
** Login   <giubil@epitech.net>
**
** Started on  Sun Apr 12 22:49:13 2015 giubil
** Last update Sun Apr 12 22:50:12 2015 giubil
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

int		create_new_client_struct(t_client_info **list, int masterfd)
{
  t_client_info	*new_client;
  t_client_info	*buff;

  if (!(new_client = malloc(sizeof(t_client_info))))
    return (-1);
  if ((new_client->sockfd = accept_new_connection(masterfd)) < 0)
    return (-1);
  new_client->next = NULL;
  new_client->nick = NULL;
  new_client->channel_next = NULL;
  new_client->channel_name = NULL;
  if (*list == NULL)
    *list = new_client;
  else
    {
      buff = *list;
      while (buff->next)
	buff = buff->next;
      buff->next = new_client;
    }
  return (0);
}

t_client_info	*get_last_client(t_client_info *list)
{
  while (list->next)
    list = list->next;
  return (list);
}

int		create_new_client(t_client_info **list, int masterfd)
{
  t_client_info	*client;

  if (create_new_client_struct(list, masterfd))
    return (-1);
  client = get_last_client(*list);
  if (write(client->sockfd, MOTD, strlen(MOTD)) < 0)
    return (-1);
  return (0);
}

int	check_if_in_clients(int fd, t_client_info *client_list)
{
  while (client_list)
    {
      if (fd == client_list->sockfd)
	return (1);
      client_list = client_list->next;
    }
  return (0);
}

t_client_info	*get_client_from_fd(int fd, t_client_info *client_list)
{
  while (client_list)
    {
      if (fd == client_list->sockfd)
	return (client_list);
      client_list = client_list->next;
    }
  return (NULL);
}
