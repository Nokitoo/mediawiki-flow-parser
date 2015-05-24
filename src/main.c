#include "display.h"
#include "parser.h"

int		usage(char *bin)
{
  printf("Usage : %s [url]\n", bin);
  return (1);
}

int		main()
{
  t_topic	*topic;
  t_topic	*tmp;
  int		res;

  topic = getTopics("Wikipédia:Forum_des_nouveaux/Flow");
  while (42)
    {
      display_topic(topic);
      res = bot_response();
      if (res == -2)
	break;
      if (res != 0)
	{
	  tmp = request_for_topic(topic, res);
	  if (tmp)
	    printf("Here we're gonna display the entire post you're asking for :)\n");
	}
    }
  destroy_linked_list(&topic);
  return (0);
}
