#include <stdlib.h>
#include <string.h>

int	isAlpha(char c)
{
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	isEscape(char *s)
{
  if (!(s - 1) || *(s - 1) != '\\')
    return (0);
  return (1);
}

char	*append(char *s1, char *s2)
{
  char	*tmp;

  if (!s1)
    {
      if ((s1 = malloc(sizeof(char) * (strlen(s2) + 1))) == NULL)
	return (NULL);
      tmp = s1;
    }
  else
    {
      if (!s2 || (s1 = realloc(s1, sizeof(char) * (strlen(s1) + strlen(s2) + 1))) == NULL)
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

char	*replace(char *search, char *replace, char *str)
{
  char	*p;
  char	*old;
  char	*new;
  int	c;
  int	len;

  c = 0;
  len = strlen(search);
  p = strstr(str, search);
  while (p)
    {
      ++c;
      p = strstr(p + len, search);
    }
  c = (strlen(replace) - len) * c + strlen(str);
  if (!(new = calloc(c, sizeof(char))))
    return (NULL);
  old = str;
  p = strstr(str, search);
  while (p)
    {
      strncpy(new + strlen(new), old, p - old);
      strcpy(new + strlen(new), replace);
      old = p + len;
      p = strstr(p + len, search);
   }
  strcpy(new + strlen(new), old);
  return (new);
}
