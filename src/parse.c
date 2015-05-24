#include "parser.h"
#include "jansson.h"

t_topic			*initRoots(json_t *topicList)
{
  t_topic		*topics;
  json_t		*roots;
  json_t		*data;
  unsigned int		nb;
  unsigned int		i;

  i = 0;
  roots = json_object_get(topicList, "roots");
  if (!json_is_array(roots))
    {
      printf("roots field is not an array\n");
      return (NULL);
    }
  topics = NULL;
  nb = json_array_size(roots);
  while (i < nb)
    {
     data = json_array_get(roots, i);
     if (!json_is_string(data) ||
	      !addTopic(&topics, json_string_value(data)))
       {
	 printf("roots field value is not a string\n");
	 return (NULL);
       }
     i++;
    }
  return (topics);
}

int			initPostIds(json_t *topicList, t_topic *topics)
{
  json_t		*posts;
  void			*iter;
  const char		*key;
  json_t		*value;
  t_topic		*tmp;

  posts = json_object_get(topicList, "posts");
  if (!json_is_object(posts))
    {
      printf("Can't find posts field\n");
      return (1);
    }
  iter = json_object_iter(posts);
  while (iter)
    {
      key = json_object_iter_key(iter);
      value = json_object_iter_value(iter);
      iter = json_object_iter_next(posts, iter);
      if (key && value && (tmp = getTopicFromId(topics, key)))
	{
	  if (json_is_array(value))
	    {
	      key = json_string_value(json_array_get(value, 0));
	      tmp->postId = key ? strdup(key) : NULL;
	    }
	}
      (void)key;
    }
  return (0);
}

int			getTopicsName(json_t *topicList, t_topic *topics)
{
  json_t		*revisions;
  void			*iter;
  const char		*key;
  json_t		*value;
  t_topic		*tmp;
  json_t		*data;

  revisions = json_object_get(topicList, "revisions");
  if (!json_is_object(revisions))
    {
      printf("Can't find revisions field\n");
      return (1);
    }
  iter = json_object_iter(revisions);
  while (iter)
    {
      key = json_object_iter_key(iter);
      value = json_object_iter_value(iter);
      iter = json_object_iter_next(revisions, iter);
      if (key && value && (tmp = getTopicFromPostId(topics, key)))
	{
	  data = json_object_get(json_object_get(json_object_get(value, "properties"), "topic-of-post"), "plaintext");
	  if (json_is_string(data))
	    tmp->name = strdup(json_string_value(data));
	}
    }
  (void)topics;
  return (0);
}

t_topic			*getFromJson(json_t *topicList)
{
  t_topic		*topics;

  if (!(topics = initRoots(topicList)) ||
      initPostIds(topicList, topics) ||
      getTopicsName(topicList, topics))
    return (NULL);
  return (topics);
}

t_topic		*getTopics(char *page)
{
  t_topic	*topics;
  json_t	*json;
  json_t	*topicList;
  json_error_t	error;
  char		*url;
  char		*content;

  url = append(append(NULL, "https://fr.wikipedia.org/w/api.php?action=flow&submodule=view-topiclist&format=json&page="), page);
  json = NULL;
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
  if(!json)
    {
      fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
      return (NULL);
    }
  topicList = json_object_get(json_object_get(json_object_get(json_object_get(json, "flow"), "view-topiclist"), "result"), "topiclist");
  if (!json_is_object(topicList))
    return (NULL);
  topics = getFromJson(topicList);
  return (topics);
}
