#include "display.h"
#include "parser.h"
#include "cmd.h"

int			getTagLength(char *s);
char			*formatPostText(char *text);
char			*removeChars(char *s, int n);

int		main(int ac, char **av)
{
  int		man;
  int		arg;
  t_topic	*topics;
  t_topic_info	*infos;

  man = 0;
  while ((arg = getopt(ac, av, "H")) > 0)
    if (arg == 'H')
      man = 1;
  topics = NULL;
  infos = NULL;
  while (1)
    {
      if (man)
	if (write(1, PROMPT, strlen(PROMPT)) < 0)
	  return (1);
      if (read_cmd(&topics, &infos, man))
	return (1);
    }
  destroy_topics(topics);
  return (0);
}
