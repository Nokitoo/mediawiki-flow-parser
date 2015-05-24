#ifndef PARSER_H_
# define PARSER_H_

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_topic	t_topic;

struct			s_topic
{
  char			*name;
  char			*id;
  char			*text;
  t_topic		*next;
};

int			addTopic(t_topic **topic, char *name, char *text, char *id);
void			destroy_linked_list(t_topic **topic);

#endif /* !PARSER_H_ */
