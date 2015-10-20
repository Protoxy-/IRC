/*
** channel_functions_server.c for irc in /home/giubil
**
** Made by giubil
** Login   <giubil@epitech.net>
**
** Started on  Sun Apr 12 22:51:45 2015 giubil
** Last update Sun Apr 12 22:53:25 2015 giubil
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

int		handle_nick(t_client_info *client, char *cmd,
			    t_client_info *list)
{
  t_client_info	*buff;

  cmd = strndup(cmd, ((cmd[strlen(cmd) - 2] == '\r') ? strlen(cmd) - 2
		      : strlen(cmd) - 1));
  buff = list;
  while (buff)
    {
      if (buff->nick != NULL && strcmp(cmd, buff->nick) == 0)
	return (create_error(client, "433 Error username already exist\r\n"));
      buff = buff->next;
    }
  client->nick = cmd;
  return (0);
}

int	channel_does_not_exist(char *name, t_channel *list)
{
  while (list)
    {
      if (strcmp(list->name, name) == 0)
	return (0);
      list = list->next;
    }
  return (1);
}

void		delete_client_from_channel(t_client_info *client,
					   t_channel **list)
{
  t_channel	*buff;
  t_client_info	*buff_client;
  t_client_info	*_buff_client;

  buff = *list;
  while (buff && strcmp(buff->name, client->channel_name))
    buff = buff->next;
  if (buff->channel_next == client)
    buff->channel_next = buff->channel_next->channel_next;
  else
    {
      buff_client = buff->channel_next;
      while (buff_client && buff_client->channel_next != client)
	buff_client = buff_client->next;
      if (buff_client == NULL)
	return ;
      _buff_client = buff_client->channel_next;
      buff_client->next = buff_client->channel_next->channel_next;
      _buff_client->channel_next = NULL;
    }
}

int		create_channel(char *name, t_client_info *client,
			       t_channel **list)
{
  t_channel	*new_channel;
  t_channel	*buff;

  if (!(new_channel = malloc(sizeof(t_channel))))
    return (-1);
  new_channel->name = name;
  if (client->channel_next)
    delete_client_from_channel(client, list);
  new_channel->channel_next = client;
  if (*list == NULL)
    *list = new_channel;
  else
    {
      buff = *list;
      while (buff->next)
	buff = buff->next;
      buff->next = new_channel;
    }
  return (0);
}

void		add_to_channel(char *name, t_client_info *client,
			       t_channel **list)
{
  t_channel	*buff;
  t_client_info	*buff_client;

  if (client->channel_name)
    delete_client_from_channel(client, list);
  buff = *list;
  while (strcmp(buff->name, name))
    buff = buff->next;
  if (buff->channel_next == NULL)
    buff->channel_next = client;
  else
    {
      buff_client = buff->channel_next;
      while (buff_client->channel_next)
	buff_client = buff_client->channel_next;
      buff_client->channel_next = client;
    }
}
