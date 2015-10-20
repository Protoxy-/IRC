/*
** client_interpret.c for IRC in /home/hoerte_f/rendu/PSU_2014_myirc/Client
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Sat Apr 11 17:15:38 2015 Francois Hoertel
** Last update Wed Apr 15 16:48:11 2015 Francois Hoertel
*/

#include "client.h"

int	client_check_info(t_client *clt)
{
  if (clt->last_com == 5)
    clt->chanel = get_param(clt->line, 0);
  return (0);
}

int	client_showret(t_client *clt, int pos)
{
  int	chk;
  int	i;

  bzero(clt->ret, (i = strlen(clt->ret)));
  write(1, clt->ret, 4096);
  if (pos == 4096)
    {
      bzero(clt->ret, 4096);
      while ((chk = read(clt->fd, clt->ret, 4096)) < 0)
	{
	  write(1, clt->ret, strlen(clt->ret));
	  bzero(clt->ret, 4096);
	}
      if (chk == 1)
	return (err_msg(": fail to read on server"));
      return (0);
    }
}

int     client_interpret(t_client *clt)
{
  int	chk;

  bzero(clt->ret, 4096);
  chk = read(clt->fd, clt->ret, 4096);
  write(1, clt->ret, strlen(clt->ret));
  if (clt->ret_att == 1)
    {
      if (clt->last_com == 0 && check_errmsg(clt->ret) == 0)
	{
	  clt->log = 0;
	  return (ret_msg(clt->ret));
	}
      else if (check_errmsg(clt->ret) == 0)
	return (ret_msg(clt->ret));
    }
  if (client_showret(clt, chk) == -1)
    return (-1);
  return (0);
}
