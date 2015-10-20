/*
** additonal_channel_functions.c for irc in /home/giubil
**
** Made by giubil
** Login   <giubil@epitech.net>
**
** Started on  Sun Apr 12 22:55:20 2015 giubil
** Last update Sun Apr 12 22:56:20 2015 giubil
*/

#include <string.h>
#include "server.h"

int	join_channel(t_client_info *client, char *cmd, t_channel **channels)
{
  cmd = strndup(cmd, ((cmd[strlen(cmd) - 1] == '\r') ? strlen(cmd) - 2
		      : strlen(cmd) - 1));
  if (cmd[0] != '#')
    return (create_error(client, "403 Error no such channel\r\n"));
  if (channel_does_not_exist(cmd, *channels))
    {
      if (create_channel(cmd, client, channels) < 0)
	return (-1);
    }
  else
    add_to_channel(cmd, client, channels);
  client->channel_name = cmd;
  return (0);
}

int		send_messages(t_client_info *client, t_channel *channels,
			      char *message)
{
  t_client_info	*buff;

  if (client->channel_name == NULL)
    return (create_error(client, "Error you need to be in a channel"));
  while (strcmp(channels->name, client->channel_name))
    channels = channels->next;
  buff = channels->channel_next;
  while (buff)
    {
      if (write(buff->sockfd, message, strlen(message)) < 0)
	return (-1);
      buff = buff->channel_next;
    }
  return (0);
}

int	part_channel(t_client_info *client, t_channel** channels)
{
  if (client->channel_name != NULL)
    delete_client_from_channel(client, channels);
  client->channel_name = NULL;
  client->channel_next = NULL;
  return (0);
}

int	list_channels(t_channel *list, char *cmd, t_client_info *client)
{
  cmd = strndup(cmd + 5, ((cmd[strlen(cmd) - 1] == '\r') ? strlen(cmd) - 2
		      : strlen(cmd) - 1));
  if (strcmp("", cmd) != 0)
    {
      while (list)
	{
	  if (strstr(cmd, list->name) != NULL
	      && list->channel_next != NULL)
	    if (write(client->sockfd, list->name, strlen(list->name)) < 0
		|| write(client->sockfd, " ", 1) < 0)
	      return (-1);
	  list = list->next;
	}
    }
  else
    while (list)
      {
	if (list->channel_next != NULL)
	  if (write(client->sockfd, list->name, strlen(list->name)) < 0
	      || write(client->sockfd, " ", 1) < 0)
	    return (-1);
	list = list->next;
      }
  write(client->sockfd, "\r\n", 2);
  return (0);
}

int		list_users(t_client_info *client, t_channel *list)
{
  t_client_info	*buff;

  if (client->channel_name == NULL)
    return (create_error(client, "Error you need to be in a channel"));
  while (strcmp(list->name, client->channel_name))
    list = list->next;
  buff = list->channel_next;
  while (buff)
    {
      if (write(client->sockfd, buff->nick, strlen(buff->nick)) < 0
	  || write(client->sockfd, " ", 1) < 0)
	return (-1);
      buff = buff->channel_next;
    }
  write(client->sockfd, "\r\n", 2);
  return (0);
}
