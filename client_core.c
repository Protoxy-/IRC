/*
** client_core.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
**
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
**
** Started on  Thu Mar 19 13:36:15 2015 Francois Hoertel
** Last update Wed Apr 15 17:14:29 2015 Francois Hoertel
*/

#include "client.h"

int	replace_command(t_client *clt, int pos)
{
  char	*new;
  int	i;
  int	j;

  if ((new = malloc(sizeof(char) * (4096))) == NULL)
    return (err_msg(": Malloc fail"));
  new = strcpy(new, clt->func_name[pos]);
  j = strlen(new);
  i = 0;
  while (clt->line[i] && clt->line[i] != '\n' && clt->line[i] != ' ')
    i++;
  while (clt->line[i] && clt->line[i] != '\n' && clt->line[i] == ' ')
    i++;
  new[j++] = ' ';
  while (clt->line[i] && clt->line[i] != '\n')
    {
      new[j] = clt->line[i];
      i++;
      j++;
    }
  new[j] = '\0';
  clt->line = strcpy(clt->line, new);
  return (0);
}

int     get_command(t_client *clt)
{
  char	*func;
  int	i;

  bzero(clt->line, 4096);
  read(0, clt->line, 4096);
  func = get_param(clt->line, 0);
  i = 0;
  while (i < 12 && check_command(func, clt->func_name[i]) == -1 &&
	 check_command(func, clt->func_name[i]) == -1)
    i++;
  clt->last_com = i;
  if (((i == 0 || i == 1 || i == 5 || i == 6 || i == 10) &&
       check_number(clt->line) < 2) || (i == 8 || i == 9) &&
      check_number(clt->line) < 3)
    return (ret_msg("You need to put more argument in parameter"));
  if (client_check_log(clt) == -2)
    return (-2);
  return (0);
}

int	send_command(t_client *clt)
{
  int	chk;

  if (strlen(clt->line) == 1)
    return (-2);
  if (clt->last_com != 12)
    replace_command(clt, clt->last_com);
  else
    clt->line[strlen(clt->line) - 2] = '\0';
  if ((chk = client_connect(clt)) != 0)
    return (chk);
  clt->ret_att = 1;
  sprintf(clt->line, "%s\r\n", clt->line);
  if (write(clt->fd, clt->line, strlen(clt->line)) == -1)
    return (err_msg("Write on the server fail"));
  return (0);
}

int	client_readwrite(t_client *clt)
{
  int	chk;

  if (FD_ISSET(0, &clt->readsets))
    {
      if ((chk = get_command(clt)) == -2)
	return (-2);
      if (send_command(clt) == -1 || chk == -1)
	return (-1);
    }
  if (FD_ISSET(clt->fd, &clt->readsets))
    {
      if ((chk = client_interpret(clt)) < 0)
	return (chk);
    }
  return (0);
}

int	client_loop(t_client *clt)
{
  int	chk;

  while (42)
    {
      FD_ZERO(&clt->readsets);
      if (clt->log != 0)
	FD_SET(clt->fd, &clt->readsets);
      FD_SET(0, &clt->readsets);
      chk = select((clt->log == 0 ? 1 : clt->fd + 1), &clt->readsets,
		   NULL, NULL, NULL);
      if (chk == -1)
	return (-1);
      if ((chk = client_readwrite(clt)) == -1)
	return (-1);
    }
  return (0);
}
