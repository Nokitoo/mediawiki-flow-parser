#include "parser.h"
#include "sockets.h"

int		get(char *domain, char *host)
{
  char		*request;

  request = malloc(sizeof(char) * (strlen(domain) + strlen(host) + 36));
  sprintf(request, "GET %s HTTP/1.0\r\nHOST:%s \r\n\r\n", domain, host);
  free(request);
  return (0);
}

int             init(char *adress, char *port)
{
  int		sockfd;
  t_sockaddr_in cin;
  t_hostent     *host;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("socket");
      return (1);
    }
  if (!(host = gethostbyname(adress)))
    {
      perror("gethostbyname");
      close(sockfd);
      return (1);
    }
  memset(&cin, 0, sizeof(cin));
  cin.sin_family = AF_INET;
  memcpy(&cin.sin_addr, host->h_addr_list[0], host->h_length);
  cin.sin_port = htons(atoi(port));
  if (connect(sockfd, (struct sockaddr *)&cin, sizeof(cin)) < 0)
    {
      perror("connect");
      close(sockfd);
      return (1);
    }
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
  if (init(av[1], "80"))
    return (1);
  if (get("www.google.fr", "www.google.fr"))
    return (1);
  return (0);
}
