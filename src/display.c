#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "parser.h"

void		display_topic(t_topic *topic)
{
  long		i;
  t_topic	*tmp;

  i = 1;
  tmp = topic;
  printf("List of topics: \n");
  while (tmp)
    {
      printf("%ld - %s\n", i++, tmp->id);
      tmp = tmp->next;
    }
  return ;
}

int		bot_response()
{
  char		buffer[32];
  int		res;

  bzero(buffer, 32);
  res = read(0, buffer, 32);
  if (res == -1)
    return (-1);
  buffer[res] = '\0';
  res = atoi(buffer);
  if (res == 0)
    return (-1);
  return (res);
}

t_topic		*request_for_topic(t_topic *topic, int nb)
{
t_topic		*tmp;
  int		i;

  tmp = topic;
  for (i = 1; i < nb && tmp; i++)
    tmp = tmp->next;
  if (tmp)
    return (NULL);
  return (tmp);
}
