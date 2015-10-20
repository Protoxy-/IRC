/*
** client_connect.c for IRC in /home/hoerte_f/rendu/PSU_2014_myirc/Client
**
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
**
** Started on  Fri Apr 10 21:09:14 2015 Francois Hoertel
** Last update Wed Apr 15 17:12:14 2015 Francois Hoertel
*/

#include "client.h"

int	client_get_content(t_client *clt)
{
  char	*content;

  content = get_param(clt->line, 1);
  if ((clt->last_com == 1 || clt->last_com == 2 || clt->last_com == 3) &&
      content && strlen(content) > 9)
    return (ret_msg("The parameter is to length."));
  if (clt->last_com == 1)
    clt->pass = content;
  if (clt->last_com == 2)
    clt->nick = content;
  if (clt->last_com == 3)
    clt->user = content;
  if (clt->last_com == 5)
    clt->chanel = content;
  return (0);
}

int	client_check_log(t_client *clt)
{
  if (clt->log == 0 && clt->last_com < 4 && clt->last_com != 0)
    return (-2);
  if (clt->log == 0 && clt->last_com > 3)
    return (ret_msg("You have to connect to a server."));
  else if (clt->last_com > 4 && clt->last_com != 4 && clt->last_com != 5 &&
	   clt->chanel[0] == '\0' && clt->last_com != 7 && clt->last_com != 11)
    return (ret_msg("You have to select a channel."));
  if (client_get_content(clt) == -2)
    return (-2);
  return (0);
}

int	server_connect(t_client *clt)
{
  char	*chk;
  char	*ip;
  int	port;

  ip = get_param(clt->line, 1);
  port = ((chk = get_param(clt->line, 2)) == NULL ? 6667 : atoi(chk));
  if (ip == clt->ip && port == clt->port)
    return (-2);
  clt->ip = ip;
  clt->port = port;
  if (chk == NULL)
    sprintf(clt->line, "%s 6667", clt->line);
  if ((port = client_reconnect(clt)) == -2)
    return (ret_msg("402 ERR_NOSUCHSERVER"));
  if (port == -1)
    return (-1);
  if (replace_ret(clt) == -1)
    return (-1);
  clt->log = 1;
  return (0);
}

int	replace_ret(t_client *clt)
{
  char	*def;

  if ((def = malloc(sizeof(char) * 10)) == NULL)
    return (err_msg(": malloc fail"));
  sprintf(def, "%c%c%c%c%c%c%c%c\0\n",
	  ((rand() % 25) + 'a'), ((rand() % 25) + 'a'), ((rand() % 25) + 'a'),
	  ((rand() % 25) + 'a'), ((rand() % 25) + 'a'), ((rand() % 25) + 'a'),
	  ((rand() % 25) + 'a'), ((rand() % 25) + 'a'));
  sprintf(clt->line, "PASS %s\r\n", (clt->pass[0] == 0 ? def : clt->pass));
  if (write(clt->fd, clt->line, strlen(clt->line)) == -1)
    return (err_msg(": Write on server fail."));
  sprintf(clt->line, "NICK %s\r\n", (clt->nick[0] == 0 ? def : clt->nick));
  if (write(clt->fd, clt->line, strlen(clt->line)) == -1)
    return (err_msg(": Write on server fail."));
  sprintf(clt->line, "USER %s", (clt->user[0] == 0 ? def : clt->user));
}

int	client_connect(t_client *clt)
{
  int	chk;

  if (clt->last_com == 0)
    return (server_connect(clt));
  return (0);
}
