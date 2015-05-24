#include <unistd.h>
#include <stdio.h>
#include "parser.h"

void		display_topic(t_topic *topic)
{
  long		i;
  t_topic	*tmp;

  i = 0;
  tmp = topic;
  printf("List of topics: \n");
  while (tmp)
    {
      printf("%ld - %s\n", i++, tmp->name);
      tmp = tmp->next;
    }
  return ;
}
