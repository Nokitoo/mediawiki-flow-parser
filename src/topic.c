#include <stdlib.h>
#include "parser.h"

int		addTopic(t_topic **topic, char *name, char *text, char *id)
{
  t_topic	*newElement;

  newElement = NULL;
  if (name == NULL || text == NULL || id == NULL)
    return (1);
  newElement = malloc(sizeof(*newElement));
  if (newElement == NULL)
    return (1);
  newElement->name = name;
  newElement->text = text;
  newElement->id = id;
  newElement->next = *topic;
  *topic = newElement;
  return (0);
}

void            destroy_linked_list(t_topic **topic)
{
  t_topic       *tmp;

  while (*topic)
    {
      tmp = (*topic)->next;
      free(*topic);
      (*topic) = tmp;
    }
  return (0);
}
