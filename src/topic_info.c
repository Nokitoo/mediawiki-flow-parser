#include "parser.h"
#include "jansson.h"

void		displayTopicInfos(t_topic_info *infos)
{
  t_post	*post;

  post = infos->posts;
  printf("[%s]\n", infos->name);
  printf("[%d]\n\n", infos->replies);
  printf("[%s] [%s]\n\n", infos->date.timestamp, infos->date.localTime);
  while (post)
    {
      printf("[%s]\n", post->author);
      printf("[%s]\n\n", post->text);
      post = post->next;
    }
}

int	getPostNb(t_post *posts)
{
  int	count;

  count = 0;
  while (posts)
    {
      posts = posts->next;
      count++;
    }
  return (count);
}

t_post		*getPostFromId(t_post *posts, const char *id)
{
  char		tmp[strlen(id)];

  strcpy(tmp, id);
  lowerCase(tmp);
  while (posts)
    {
      if (!strcmp(tmp, posts->id))
	return (posts);
      posts = posts->next;
    }
  return (NULL);
}

void		addPost(t_post **posts, const char *id)
{
  t_post	*new;

  if (!(new = malloc(sizeof(*new))))
    return ;
  new->id = strdup(id);
  new->author = NULL;
  new->text = NULL;
  new->next = (*posts);
  (*posts) = new;
}

t_post		*initPostsId(json_t *topic, char *topicId)
{
  t_post	*posts;
  json_t	*postJson;
  void		*iter;
  const char	*key;

  posts = NULL;
  postJson = json_object_get(topic, "posts");
  if (!json_is_object(postJson))
    return (NULL);
  iter = json_object_iter(postJson);
  while (iter)
    {
      key = json_object_iter_key(iter);
      iter = json_object_iter_next(postJson, iter);
      if (strcmp(key, topicId))
	addPost(&posts, key);
    }
  return (posts);
}

t_topic_info		*initTopicInfos(json_t *topic)
{
  t_topic_info		*infos;

  (void)topic;
  if (!(infos = malloc(sizeof(*infos))))
    return (NULL);
  infos->posts = NULL;
  infos->date.timestamp = NULL;
  infos->date.localTime = NULL;
  infos->replies = 0;
  return (infos);
}

char			*removeChars(char *s, int n)
{
  char			*tmp;

  if (n <= 0 || !s)
    return (s);
  tmp = s;
  while (s + n && *(s + n))
    {
      *s = *(s + n);
      s++;
    }
  while (s && *s)
    {
      *s = '\0';
      s++;
    }
  return (tmp);
}

int			getTagLength(char *s)
{
  int			length;
  int			attribute;

  length = 1;
  attribute = 0;
  if (!s || *s != '<' || !*(s + 1))
    return (0);
  s++;
  if (*s == '/')
    {
      s++;
      length++;
      while (s && *s && *s != '>')
	{
	  if (!isAlpha(*s))
	    return (0);
	  s++;
	  length++;
	}
    }
  else
    {
      while (s && *s && (*s != '>' || attribute))
	{
	  if ((*s == '"' || (*s == '\'')) && !attribute)
	    attribute = 1;
	  else if ((*s == '"' || *s == '\'') && attribute && !isEscape(s))
	    attribute = 0;
	  s++;
	  length++;
	}
    }
  return (length);
}

char			*formatPostText(char *text)
{
  char			*tmp;
  int			length;

  tmp = text;
  while (text && *text)
    {
      length = getTagLength(text);
      if (length)
	text = removeChars(text, length + 1);
      text++;
    }
  return (tmp);
}

void			setRevisionInfos(t_post *post, json_t *revision)
{
  json_t		*data;
  const char		*value;

  data = json_object_get(json_object_get(revision, "author"), "name");
  if (json_is_string(data))
    {
      value = json_string_value(data);
      post->author = value ? strdup(value) : NULL;
    }
  data = json_object_get(json_object_get(revision, "content"), "content");
  if (json_is_string(data))
    {
      value = json_string_value(data);
      post->text = value ? formatPostText(strdup(value)) : NULL;
    }
}
t_post			*getPostsInfos(json_t *topic, char *topicId)
{
  t_post		*posts;
  json_t		*revisions;
  void			*iter;
  const char		*key;
  json_t		*value;
  t_post		*tmp;

  if (!(posts = initPostsId(topic, topicId)))
    return (NULL);
  revisions = json_object_get(topic, "revisions");
  if (!json_is_object(revisions))
    {
      printf("Can't find revisions field\n");
      return (NULL);
    }
  iter = json_object_iter(revisions);
  while (iter)
    {
      key = json_object_iter_key(iter);
      value = json_object_iter_value(iter);
      iter = json_object_iter_next(revisions, iter);
      if (key && value && (tmp = getPostFromId(posts, key)))
	setRevisionInfos(tmp, value);
    }
  return (posts);
}

const char	*getTopicRevisionId(json_t *topic, char *topicId)
{
  json_t	*postJson;
  void		*iter;
  const char	*key;
  json_t	*value;

  postJson = json_object_get(topic, "posts");
  if (!json_is_object(postJson))
      return (NULL);
  iter = json_object_iter(postJson);
  while (iter)
    {
      key = json_object_iter_key(iter);
      if (!strcmp(key, topicId))
	{
	  value = json_object_iter_value(iter);
	  if (json_is_array(value))
	    {
	      value = json_array_get(value, 0);
	      if (json_is_string(value))
		return (json_string_value(value));
	    }
	}
      iter = json_object_iter_next(postJson, iter);
    }
  return (NULL);
}

void		setTopicDate(json_t *revision, t_topic_info *infos)
{
  json_t	*content;
  const char	*timestamp;
  const char	*localTime;

  content = json_object_get(revision, "timestamp");
  if (json_is_string(content))
    {
      timestamp = json_string_value(content);
      localTime = timestampToLocalTime(timestamp);
      infos->date.timestamp = timestamp ? strdup(timestamp) : NULL;
      infos->date.localTime =  localTime ? strdup(localTime) : NULL;
    }
}

void		setTopicName(json_t *revision, t_topic_info *infos)
{
  json_t	*content;
  const char	*name;

  content = json_object_get(json_object_get(revision, "content"), "content");
  if (json_is_string(content))
    {
      name = json_string_value(content);
      infos->name = name ? strdup(name) : NULL;
    }
}

void			setTopicInfos(t_topic_info *infos, json_t *topic, char *topicId)
{
  json_t		*revisions;
  void			*iter;
  const char		*key;
  json_t		*value;
  const char		*revisionId;

  infos->replies = getPostNb(infos->posts);
  if (!(revisionId = getTopicRevisionId(topic, topicId)))
    return ;
  revisions = json_object_get(topic, "revisions");
  if (!json_is_object(revisions))
    {
      printf("Can't find revisions field\n");
      return ;
    }
  iter = json_object_iter(revisions);
  while (iter)
    {
      key = json_object_iter_key(iter);
      value = json_object_iter_value(iter);
      iter = json_object_iter_next(revisions, iter);
      if (key && value && !strcmp(key, revisionId))
	{
	  setTopicName(value, infos);
	  setTopicDate(value, infos);
	}
    }
  return ;
}

t_topic_info		*getTopicInfos(char *topicId)
{
  json_t		*json;
  json_t		*topic;
  json_error_t		error;
  char			*url;
  char			*content;
  t_topic_info		*infos;

  topicId = lowerCase(strdup(topicId));
  url = append(append(NULL, "https://fr.wikipedia.org/w/api.php?action=flow&submodule=view-topic&format=json&page=Topic:"), topicId);
  content = request(url);
  if (!content)
    {
      fprintf(stderr, "Failed to requests url %s\n", url);
      free(url);
      return (NULL);
    }
  free(url);
  json = json_loads(content, 0, &error);
  free(content);
  if (!json)
    {
      free(topicId);
      fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
      return (NULL);
    }
  topic = json_object_get(json_object_get(json_object_get(json_object_get(json, "flow"), "view-topic"), "result"), "topic");
  if (!json_is_object(topic))
    {
      json_decref(json);
      free(topicId);
      printf("Failed to get topic field\n");
      return (NULL);
    }
  if (!(infos = initTopicInfos(topic)) ||
      !(infos->posts = getPostsInfos(topic, topicId)))
    {
      json_decref(json);
      free(topicId);
    }
  setTopicInfos(infos, topic, topicId);
  json_decref(json);
  free(topicId);
  return (infos);
}

void		destroy_topic_info(t_topic_info *infos)
{
  t_post	*post;
  t_post	*tmp;

  post = infos->posts;
  while (post)
    {
      tmp = post->next;
      if (post->id)
	free(post->id);
      if (post->author)
	free(post->author);
      if (post->text)
	free(post->text);
      free(post);
      post = tmp;
    }
}
