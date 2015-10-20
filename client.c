/*
** client.c for Client in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Mon Mar  9 11:28:21 2015 Francois Hoertel
** Last update Sun Apr 12 21:34:45 2015 Francois Hoertel
*/

#include "client.h"

int		send_info(int fd, char *str)
{
  if (write(fd, str, strlen(str)) == -1)
    return (err_msg(": for write on server"));
  return (0);
}

int		main(int ac, char **av)
{
  t_client	*clt;

  if (ac != 3 && ac != 1)
    {
      err_msg("Usage : ./client <ip server> <port nb>\n");
      return (-1);
    }
  srand(time(NULL));
  if ((clt = malloc(sizeof(t_client))) == NULL)
    return (err_msg(": malloc fail"));
  if (client_init(clt, (ac == 1 ? NULL : av)) == -1)
    return (-1);
  if (client_loop(clt) == -1)
    return (-1);
  close(clt->fd);
  return (0);
}
