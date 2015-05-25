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
      if (bot_response(&res))
	return (1);
      if (res == -2)
	break;
      if (res != 0)
	{
	  tmp = request_for_topic(topic, res);
	  if (tmp){}
	}
    }
  destroy_linked_list(&topic);
  return (0);
}
