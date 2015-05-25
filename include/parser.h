#ifndef PARSER_H_
# define PARSER_H_
# define TOPICS_LIMIT "50"

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_topic		t_topic;
typedef struct		s_topic_info	t_topic_info;
typedef struct		s_post		t_post;
typedef struct		s_date		t_date;

struct			s_date
{
  char			*timestamp;
  char			*localTime;
};

struct			s_post
{
  char			*id;
  char			*author;
  char			*text;
  t_post		*next;
};

struct			s_topic_info
{
  char			*name;
  int			replies;
  t_post		*posts;
  t_date		date;
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
t_topic			*getTopics(t_topic *topics, char *html, char *lastId);
void			parseJson(char *html);
int			get(char *url);
char			*append(char *s1, char *s2);
char			*request(const char *url);
t_topic_info		*getTopicInfos(char *topicId);
void			displayTopicInfos(t_topic_info *infos);
void			destroy_topic_info(t_topic_info *infos);
char			*lowerCase(char *s);
int			isAlpha(char c);
int			isEscape(char *s);
char			*formatPostText(char *text);
char			*getLastTopicId(t_topic *topic);
const char		*timestampToLocalTime(const char *timestamp);

#endif /* !PARSER_H_ */
