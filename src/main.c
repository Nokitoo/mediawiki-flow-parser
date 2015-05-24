#include "display.h"
#include "parser.h"

int		usage(char *bin)
{
  printf("Usage : %s [url]\n", bin);
  return (1);
}

int		main(int ac, char **av)
{
  t_topic	*topic;

  topic = NULL;
  (void)topic;
  if (ac < 2)
    return (usage(av[0]));
  destroy_linked_list(&topic);
  return (0);
}
