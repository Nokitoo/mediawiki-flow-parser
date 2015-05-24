#include "gumbo.h"
#include "parser.h"

void			getTopicName(GumboNode *node, t_topic *topic)
{
  GumboVector		*children;
  GumboAttribute	*class;
  GumboNode		*titleText;
  unsigned int		i;

  i = 0;
  if (node->type != GUMBO_NODE_ELEMENT)
    return ;
  if (node->v.element.tag == GUMBO_TAG_H2 &&
      (class = gumbo_get_attribute(&node->v.element.attributes, "class"))&&
      strstr(class->value, "flow-topic-title"))
    {
      titleText = (GumboNode*)(node->v.element.children.data[0]);
      topic->name = strdup(titleText->v.text.text);
      return ;
    }
  children = &node->v.element.children;
  while (i < children->length)
    {
      getTopicName((GumboNode*)(children->data[i]), topic);
      i++;
    }
}

void			search_topics(GumboNode *node, t_topic **topic)
{
  GumboAttribute	*topicId;
  GumboAttribute	*class;
  GumboVector		*children;
  unsigned int		i;
  t_topic		*tmp;

  i = 0;
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  if (node->v.element.tag == GUMBO_TAG_DIV &&
      (topicId = gumbo_get_attribute(&node->v.element.attributes, "data-flow-id")) &&
      (class = gumbo_get_attribute(&node->v.element.attributes, "class"))&&
      strstr(class->value, "flow-topic"))
    {
      tmp = addTopic(topic, (char*)topicId->value);
      if (tmp)
	getTopicName(node, tmp);
    }

  children = &node->v.element.children;
  while (i < children->length)
    {
      search_topics((GumboNode*)(children->data[i]), topic);
      i++;
    }
}

t_topic		*getTopics(char *html)
{
  GumboOutput	*output;
  t_topic	*topic;

  topic = NULL;
  if (!html)
    return (NULL);
  output = gumbo_parse(html);
  search_topics(output->root, &topic);
  gumbo_destroy_output(&kGumboDefaultOptions, output);
  displayTopics(topic);
  return (topic);
}
