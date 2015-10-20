/*
** parse_commands.c for irc in /home/giubil
**
** Made by giubil
** Login   <giubil@epitech.net>
**
** Started on  Sun Apr 12 22:57:56 2015 giubil
** Last update Sun Apr 12 22:58:39 2015 giubil
*/

#include <string.h>
#include <unistd.h>
#include "server.h"

int	handle_client_connection(t_client_info *client, t_client_info *list,
				 char *cmd, t_channel **channels)
{
  char	*buff;

  buff = strdup(cmd);
  bzero(cmd, 4096);
  if (strncmp(buff, "PASS ", 5) == 0)
    return (0);
  else if (strncmp(buff, "NICK ", 5) == 0)
    return (handle_nick(client, buff + 5, list));
  else if (strncmp(buff, "USER ", 5) == 0)
    return (0);
  else if (strncmp(buff, "JOIN ", 5) == 0)
    return (join_channel(client, buff + 5, channels));
  else if (strncmp(buff, "PART ", 5) == 0)
    return (part_channel(client, channels));
  else if (strncmp(buff, "LIST", 4) == 0)
    return (list_channels(*channels, cmd, client));
  else if (strncmp(buff, "USERS", 5) == 0)
    return (list_users(client, *channels));
  else if (strncmp(buff, "MSG", 3) == 0)
    return (private_message(client, list, buff));
  else
    return (send_messages(client, *channels, buff));
  return (0);
}

int		buffer_message(t_client_info *client, t_client_info *list,
			       t_channel **channels)
{
  char		buff[512];

  bzero(buff, 512);
  if (read(client->sockfd, buff, 512) < 0)
    return (-1);
  if (strlen(client->command_buffer) + strlen(buff) > 8192)
    return (-1);
  strcpy(client->command_buffer + strlen(client->command_buffer),
	 buff);
  if (client->command_buffer[strlen(client->command_buffer) - 1] == '\n')
    return (handle_client_connection(client, list, client->command_buffer,
				     channels));
  return (0);
}
