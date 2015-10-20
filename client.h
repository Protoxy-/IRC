/*
** serveur.h for Serveur in /home/hoerte_f/rendu/PSU_2014_myftp
** 
** Made by Francois Hoertel
** Login   <hoerte_f@epitech.net>
** 
** Started on  Mon Mar  9 11:24:30 2015 Francois Hoertel
** Last update Sun Apr 12 22:40:08 2015 Francois Hoertel
*/

#ifndef CLIENT_H_
# define CLIENT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <dirent.h>

typedef struct		s_client
{
  char			**func_name;
  char			*line;
  char			*ret;
  fd_set		readsets;
  int			last_com;
  struct protoent	*pe_data;
  struct protoent	*pe;
  struct sockaddr_in	sin;
  int			fd;
  struct sockaddr_in	sin_data;
  int			fd_data;
  int			port;
  int			log;
  int			ret_att;
  char			*ip;
  char			*chanel;
  char			*pass;
  char			*nick;
  char			*user;
}			t_client;

int			send_info(int, char *);
int			client_init(t_client *, char **);
int			client_reconnect(t_client *);
int			client_check_log(t_client *);
int			init_func_name(t_client *);
void			init_server_name(t_client *);
int			init_data_port(t_client *, int);
int			init_data_connexion(t_client *, int);
int			client_get_data(t_client *);
int			client_interpret(t_client *);
int			client_connect(t_client *);
int			client_loop(t_client *);
int			check_end(t_client *);
int			get_file(t_client *);
int			client_showret(t_client *, int);
int			send_file(t_client *);
int			ret_msg(char *);
int			err_msg(char *);
void			*verr_msg(char *);
int			check_file(char *, int);
char			*get_param(char *, int);
int			check_command(char *, char *);
int			check_msg(char *, char *);

#endif /* CLIENT_H_ */
