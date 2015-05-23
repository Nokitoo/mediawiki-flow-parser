#ifndef PARSER_H_
# define PARSER_H_

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_topic	t_topic;
typedef struct		s_topic_content t_topic_content;

struct			s_topic
{
  char			*name;
  char			*id;
  t_topic		*next;
};

struct			s_topic_content
{
  char			*text;
  t_topic_content	*next;
};

#endif /* !PARSER_H_ */
