/*
** server_connection.c for server_co in /home/giubil
**
** Made by giubil
** Login   <giubil@epitech.net>
**
** Started on  Thu Apr  9 12:53:38 2015 giubil
** Last update Sun Apr 12 22:49:59 2015 giubil
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/select.h>
#include "server.h"

int	create_socket(int port)
{
  int sockfd;
  struct sockaddr_in serv_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    {
      printf("ERROR opening socket");
      return (-1);
    }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);
  if (bind(sockfd, (struct sockaddr *) &serv_addr,
	   sizeof(serv_addr)) < 0)
    {
      printf("ERROR on binding");
      return (-1);
    }
  listen(sockfd,5);
  return (sockfd);
}

int			accept_new_connection(int masterfd)
{
  int			newsockfd;
  socklen_t		clilen;
  struct sockaddr_in	cli_addr;

  if (getsockname(masterfd, (struct sockaddr *)&cli_addr, &(clilen)) < 0
      || (newsockfd = accept(masterfd, (struct sockaddr *)&cli_addr,
			     &(clilen))) < 0)
    return (-1);
  return (newsockfd);
}

void	add_client_to_watch_list(t_client_info *client_list, fd_set *readsets)
{
  while (client_list)
    {
      FD_SET(client_list->sockfd, readsets);
      client_list = client_list->next;
    }
}

int	get_bigger_fd(t_client_info *client_lists, int masterfd)
{
  int	buff_fd;

  if (!client_lists)
    return (masterfd + 1);
  buff_fd = client_lists->sockfd;
  client_lists = client_lists->next;
  while (client_lists)
    {
      if (client_lists->sockfd > buff_fd)
	buff_fd = client_lists->sockfd;
      client_lists = client_lists->next;
    }
  return (buff_fd + 1);
}

int			print_socket_port(int masterfd)
{
  struct sockaddr_in	sin;
  socklen_t		len;

  len = sizeof(sin);
  if (getsockname(masterfd, (struct sockaddr *)&sin, &len) < 0)
    return (-1);
  printf("Port to connect to is : %d\n", ntohs(sin.sin_port));
  return (0);
}
