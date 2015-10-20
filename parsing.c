/*
** parsing.c for FTP in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Thu Mar 19 14:10:37 2015 Francois Hoertel
** Last update Sun Apr 12 21:32:49 2015 Francois Hoertel
*/

#include "client.h"

int	check_command(char *entry, char *func)
{
  int	i;
  int	j;
  int	k;

  if (strlen(entry) > strlen(func) + 1)
    return (-1);
  k = 0;
  if (entry[0] == '/')
    k++;
  j = 0;
  i = 0;
  while (entry[i] && func[i])
    {
      if (entry[i + k] == func[i])
        j++;
      if (entry[i + k] >= 'a' && entry[i] <= 'z' &&
	  entry[i + k] - 32 == func[i])
	j++;
      i++;
    }
  if (j != i)
    return (-1);
  return (0);
}

int	check_msg(char *entry, char *func)
{
  int	i;
  int	j;

  j = 0;
  i = 0;
  while (entry[i] && func[i])
    {
      if (entry[i] == func[i])
        j++;
      if (entry[i] >= 'a' && entry[i] <= 'z' && entry[i] - 32 == func[i])
	j++;
      i++;
    }
  if (j != i)
    return (-1);
  return (0);
}

int	check_errmsg(char *entry)
{
  if (strlen(entry) < 7)
    return (-1);
  if (entry[4] != 'E')
    return (-1);
  if (entry[5] != 'R')
    return (-1);
  if (entry[6] != 'R')
    return (-1);
  return (0);
}

int	check_number(char *str)
{
  int	i;
  int	j;

  i = -1;
  j = 0;
  while (str[++i])
    {
      while (str[i] == ' ' && str[i])
	i++;
      while (str[i] != ' ' && str[i])
	i++;
      j++;
    }
  return (j);
}
