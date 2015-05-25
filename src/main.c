#include "display.h"
#include "parser.h"
#include "cmd.h"

int		usage(char *bin)
{
  printf("Usage : %s [url]\n", bin);
  return (1);
}

int		main()
{
  t_topic	*topics;
  t_topic_info	*infos;
  
  topics = NULL;
  infos = NULL;
  while (1)
    {
      if (read_cmd(&topics, &infos))
	return (1);
    }
  destroy_topics(topics);
  return (0);
}
