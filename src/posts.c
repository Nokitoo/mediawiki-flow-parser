#include "parser.h"
#include "jansson.h"

void		displayPosts(t_post *post)
{
  while (post)
    {
      printf("%s\n", post->id);
      post = post->next;
    }
}

void		addPost(t_post **posts, const char *id)
{
  t_post	*new;

  if (!(new = malloc(sizeof(*new))))
    return ;
  new->id = strdup(id);
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

t_post		*getTopicPosts(char *topicId)
{
  json_t	*json;
  json_t	*topic;
  json_error_t	error;
  t_post	*posts;
  char		*url;
  char		*content;

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
  posts = initPostsId(topic, topicId);
  json_decref(json);
  free(topicId);
  return (posts);
}

void		destroy_posts(t_post *post)
{
  t_post	*tmp;

  while (post)
    {
      tmp = post->next;
      if (post->id)
	free(post->id);
      free(post);
      post = tmp;
    }
}
