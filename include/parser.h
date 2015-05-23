#ifndef PARSER_H_
# define PARSER_H_

typedef struct		s_topic	t_topic;

struct			s_topic
{
  char			*name;
  char			*id;
  t_topic		*next;
};

#endif /* !PARSER_H_ */
