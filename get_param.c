/*
** get_param.c for IRC in /home/hoerte_f/rendu/PSU_2014_myirc/client_src
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Sun Apr 12 20:21:21 2015 Francois Hoertel
** Last update Sun Apr 12 22:52:16 2015 Francois Hoertel
*/

#include "client.h"

char	*get_param(char *buff, int pos)
{
  char	*param;
  int	i;
  int	j;
  int	k;

  if ((param = malloc(sizeof(char) * 4096)) == NULL)
    return (verr_msg(": Malloc fail"));
  k = 0;
  j = 0;
  i = -1;
  while (buff[++i] && buff[(i == 0 ? 0 : i - 1)] && j < pos + 1)
    {
      while (buff[i] && (buff[i] == ' ' || buff[i] == ':'))
	i++;
      while (buff[i] && (buff[i] != ' ' && buff[i] != ':'))
	{
	  if (j == pos)
	    param[k++] = buff[i];
	  i++;
	}
      if (j == pos)
	param[k] = '\0';
      j++;
    }
  return ((k == 0 ? NULL : param));
}
