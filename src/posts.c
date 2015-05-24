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

t_post		*getTopicPosts(json_t *topic)
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
     addPost(&posts, key);
   }
  return (posts);
}

void		parseJson(char *html)
{
  json_t	*json;
  json_t	*topic;
  json_error_t	error;
  t_post	*post;

 json = json_loads(html, 0, &error);
 free(html);
  if (!json)
    {
      fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
      return ;
    }
 topic = json_object_get(json_object_get(json_object_get(json_object_get(json, "flow"), "view-topic"), "result"), "topic");
 if(!json_is_object(topic))
   return ;
 post = getTopicPosts(topic);
 displayPosts(post);
}
