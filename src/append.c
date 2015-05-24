#include <stdlib.h>
#include <string.h>

char			*append(char *s1, char *s2)
{
  char			*tmp;

  if (!s1)
    {
      if ((s1 = malloc(sizeof(char) * (strlen(s2) + 1))) == NULL)
	return (NULL);
      tmp = s1;
    }
  else
    {
      if (!s2 || (s1 = realloc(s1,
			sizeof(char) * (strlen(s1) + strlen(s2) + 1))) == NULL)
	return (NULL);
      tmp = s1;
      while (s1 && *s1)
	s1++;
    }
  while (s2 && *s2)
    {
      *s1 = *s2;
      s1++;
      s2++;
    }
  *s1 = '\0';
  return (tmp);
}
