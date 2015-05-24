#include "display.h"
#include "parser.h"

int		usage(char *bin)
{
  printf("Usage : %s [url]\n", bin);
  return (1);
}

int		main()
{
  displayTopics(getTopics("Wikipédia:Forum_des_nouveaux/Flow"));
  return (0);
}
