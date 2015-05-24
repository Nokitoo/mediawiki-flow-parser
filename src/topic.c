#include <stdlib.h>
#include "parser.h"

void		displayTopics(t_topic *topic)
{
  while (topic)
    {
      printf("%s %s\n", topic->id, topic->name);
      topic = topic->next;
    }
}

t_topic		*addTopic(t_topic **topic, char *id)
{
  t_topic	*newElement;

  newElement = malloc(sizeof(*newElement));
  if (newElement == NULL || id == NULL)
    return (NULL);
  newElement->name = NULL;
  newElement->text = NULL;
  newElement->id = strdup(id);
  if (newElement->id == NULL)
    {
      free(newElement);
      return (NULL);
    }
  newElement->next = *topic;
  *topic = newElement;
  return (newElement);
}

void            destroy_linked_list(t_topic **topic)
{
  t_topic       *tmp;

  while (*topic)
    {
      tmp = (*topic)->next;
      free((*topic)->id);
      free(*topic);
      (*topic) = tmp;
    }
}
