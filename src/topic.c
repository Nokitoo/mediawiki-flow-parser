#include <stdlib.h>
#include "parser.h"

t_topic		*getTopicFromId(t_topic *topic, const char *id)
{
  while (topic)
    {
      if (!strcmp(topic->id, id))
	return (topic);
      topic = topic->next;
    }
  return (NULL);
}

t_topic		*getTopicFromPostId(t_topic *topic, const char *id)
{
  while (topic)
    {
      if (!strcmp(topic->postId, id))
	return (topic);
      topic = topic->next;
    }
  return (NULL);
}

t_topic		*addTopic(t_topic **topic, const char *id)
{
  t_topic	*newElement;
  t_topic	*tmp;

  tmp = *topic;
  newElement = malloc(sizeof(*newElement));
  if (newElement == NULL || id == NULL)
    return (NULL);
  newElement->name = NULL;
  newElement->next = NULL;
  newElement->id = strdup(id);
  newElement->postId = NULL;
  if (newElement->id == NULL)
    {
      free(newElement);
      return (NULL);
    }
  if (!tmp)
    {
      *topic = newElement;
      (*topic)->next = NULL;
    }
  else
    {
      while (tmp && tmp->next)
	tmp = tmp->next;
      tmp->next = newElement;
      newElement->prev = tmp;
    }
  return (newElement);
}

void            destroy_linked_list(t_topic **topic)
{
  t_topic       *tmp;

  while (*topic)
    {
      tmp = (*topic)->next;
      if ((*topic)->name)
	free((*topic)->name);
      if ((*topic)->postId)
	free((*topic)->postId);
      if ((*topic)->id)
	free((*topic)->id);
      free(*topic);
      (*topic) = tmp;
    }
}
