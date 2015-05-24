#ifndef PARSER_H_
# define PARSER_H_

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_topic	t_topic;

struct			s_topic
{
  char			*name;
  char			*id;
  char			*text;
  int			nb;
  t_topic		*next;
};

t_topic			*addTopic(t_topic **topic, char *id);
void			destroy_linked_list(t_topic **topic);
t_topic			*getTopics(char *html);
void			displayTopics(t_topic *topic);

#endif /* !PARSER_H_ */
