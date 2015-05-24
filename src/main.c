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
  int		res;
  t_topic	*tmp;
  
  topic = NULL;
  if (ac < 2)
    return (usage(av[0]));
  while (EPITECH_IS_ALIVE)
    {
      res = bot_response();
      if (res != -1)
	{
	  tmp = request_for_topic(topic, res);
	  if (tmp)
	    printf("%s\n", tmp->id);
	}
      if (res == -2)
	break; // At school we are not allowed to use break keyword ! So I have fun with it !
    }
  free(tmp);
  destroy_linked_list(&topic);
  return (0);
}
