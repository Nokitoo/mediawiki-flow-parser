#include "parser.h"
#include "sockets.h"

int		send_with_check(int sockfd, char *message)
{
  if (send(sockfd, message, strlen(message), 0) < 0)
    {
      perror("send");
      return (1);
    }
  return (0);
}

int		recv_with_check(int sockfd, char *message)
{
  if (recv(sockfd, message, strlen(message), 0) < 0)
    {
      perror("recv");
      return (1);
    }
  return (0);
}

int             init_socket(int *sockfd, char *adress, char *port)
{
  t_sockaddr_in cin;
  t_hostent     *host;

  if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("socket");
      return (1);
    }
  if (!(host = gethostbyname(adress)))
    {
      perror("gethostbyname");
      close(*sockfd);
      return (1);
    }
  memset(&cin, 0, sizeof(cin));
  cin.sin_family = AF_INET;
  memcpy(&cin.sin_addr, host->h_addr_list[0], host->h_length);
  cin.sin_port = htons(atoi(port));
  if (connect(*sockfd, (struct sockaddr *)&cin, sizeof(cin)) < 0)
    {
      perror("connect");
      close(*sockfd);
      return (1);
    }
  return (0);
}

int		get(char *domain, char *host)
{
  int		sockfd;
  char		*request;

  if (init_socket(&sockfd,domain, "80"))
    return (1);
  if (!(request = calloc(strlen(domain) + strlen(host) + 36, sizeof(char))))
    return (1);
  sprintf(request, "GET %s HTTP/1.0\r\nHOST:%s \r\n\r\n", domain, host);
  close(sockfd);
  free(request);
  return (0);
}

int		usage(char *bin)
{
  printf("Usage : %s [url]\n", bin);
  return (1);
}

int		main(int ac, char **av)
{
  if (ac < 2)
    return (usage(av[0]));
  if (get("http://www.google.fr", "http://www.google.fr"))
    return (1);
  return (0);
}
