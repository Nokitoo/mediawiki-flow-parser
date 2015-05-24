#ifndef PARSER_H_
# define PARSER_H_

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_topic	t_topic;
typedef struct		s_post	t_post;

struct			s_post
{
  char			*id;
  t_post		*next;
};

struct			s_topic
{
  char			*name;
  char			*id;
  char			*postId;
  int			nb;
  t_topic		*next;
  t_topic		*prev;
};

t_topic			*addTopic(t_topic **topic, const char *id);
t_topic			*getTopicFromId(t_topic *topic, const char *id);
t_topic			*getTopicFromPostId(t_topic *topic, const char *id);
void			destroy_topics(t_topic *topic);
t_topic			*getTopics(char *html);
void			parseJson(char *html);
int			get(char *url);
char			*append(char *s1, char *s2);
char			*request(const char *url);
t_post			*getTopicPosts(char *topicName);
void			displayPosts(t_post *post);
void			destroy_posts(t_post *post);
char			*lowerCase(char *s);

#endif /* !PARSER_H_ */
