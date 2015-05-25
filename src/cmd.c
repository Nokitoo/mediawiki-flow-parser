#include <string.h>
#include <unistd.h>
#include "cmd.h"
#include "parser.h"

int		read_cmd(t_topic **topics, t_topic_info **infos, int isHuman)
{
  int		len;
  char		buffer[64];
  char		*str;
  static char	*url = NULL;
  static int	from = 1;

  bzero(buffer, 64);
  len = read(0, buffer, 64);
  buffer[len - 1] = '\0';
  if (len <= 0 || !strcmp(buffer, "exit"))
    return (1);
  str = strtok(buffer, " ");
  str = strtok(NULL, " ");
  if (str)
    {
      if (!strcmp(buffer, "view-topiclist"))
	{
	  if (!url || strcmp(url, str))
	    {
	      from = 1;
	      if (url)
		free(url);
	      url = strdup(str);
	    }
	  *topics = viewtopiclist(*topics, url, isHuman, &from);
	}
      else if (!strcmp(buffer, "view-topic"))
	*infos = viewtopic(*topics, *infos, str);
    }
  return (0);
}

t_topic		*viewtopiclist(t_topic *topics, char *url, int isHuman, int *from)
{
  char		*lastId;

  lastId = getLastTopicId(topics);
  topics = getTopics(topics, url, lastId);
  display_topic(topics, &from, isHuman);
  return (topics);
}

t_topic_info		*viewtopic(t_topic *topic, t_topic_info *infos, char *url)
{
  int			res;
  t_topic		*tmp;
  
  res = atoi(url);
  if (res <= 0)
    return (NULL);
  tmp = request_for_topic(topic, res);
  if (tmp == NULL)
    return (NULL);
  infos = getTopicInfos(tmp->id);
  displayTopicInfos(infos);
  destroy_topic_info(infos);
  return (infos);
}
