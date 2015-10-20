/*
** client_init.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
**
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
**
** Started on  Thu Mar 19 13:14:01 2015 Francois Hoertel
** Last update Sun Apr 12 23:24:04 2015 giubil
*/

#include "client.h"

int	init_func_name(t_client *clt)
{
  if ((clt->line = malloc(sizeof(char) * 4096)) == NULL)
    return (err_msg(": Malloc fail"));
  if ((clt->ret = malloc(sizeof(char) * 4096)) == NULL)
    return (err_msg(": Malloc fail"));
  if ((clt->func_name = malloc(sizeof(char*) * 20)) == NULL)
    return (err_msg(": Malloc fail"));
  clt->func_name[0] = "SERVER";
  clt->func_name[1] = "PASS";
  clt->func_name[2] = "NICK";
  clt->func_name[3] = "USER";
  clt->func_name[4] = "LIST";
  clt->func_name[5] = "JOIN";
  clt->func_name[6] = "PART";
  clt->func_name[7] = "USERS";
  clt->func_name[8] = "MSG";
  clt->func_name[9] = "SEND_FILE";
  clt->func_name[10] = "ACCEPT_FILE";
  clt->func_name[11] = "QUIT";
  clt->func_name[12] = "NOOP";
  clt->log = 0;
  clt->fd = 2;
  return (0);
}

int	client_reconnect(t_client *clt)
{
  close(clt->fd);
  if ((clt->fd = socket(AF_INET, SOCK_STREAM, clt->pe->p_proto)) == -1)
    return (err_msg("Err: socket"));
  clt->sin.sin_family = AF_INET;
  clt->sin.sin_port = htons(clt->port);
  clt->sin.sin_addr.s_addr = inet_addr(clt->ip);
  if (connect(clt->fd, (const struct sockaddr *)&clt->sin, sizeof(clt->sin))
      == -1)
    return (-2);
  return (0);
}

int	client_init(t_client *clt, char **av)
{
  if (init_func_name(clt) == -1)
    return (-1);
  clt->ret_att = 0;
  if (!(clt->pe = getprotobyname("TCP")))
    return (err_msg("Err: getprotobyname"));
  if (av != NULL)
    {
      clt->ip = av[1];
      clt->port = atoi(av[2]);
      clt->log = 1;
      clt->ret_att = 1;
      if (client_reconnect(clt) < 0)
	return (-1);
    }
  if ((clt->chanel = malloc(sizeof(char) * 4096)) == NULL)
    return (err_msg(": malloc fail"));
  clt->chanel = "";
  clt->pass = "";
  clt->nick = "";
  clt->user = "";
  return (0);
}
