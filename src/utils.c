int		isAlpha(char c)
{
  return ((c >= 'a' && c <= 'z') ||
	  (c >= 'A' && c <= 'Z'));
}

int		isEscape(char *s)
{
  if (!(s - 1) || *(s - 1) != '\\')
    return (0);
  return (1);
}
