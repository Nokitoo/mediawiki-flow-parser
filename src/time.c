#include <stdlib.h>
#include <time.h>

const char	*timestampToLocalTime(const char *timestamp)
{
  time_t	time;
  char		*buffer;
  struct tm	*loctime;

  if (!timestamp || !(buffer = calloc(256, sizeof(char))))
    return (NULL);
  time = atoi(timestamp);
  loctime = localtime(&time);
  strftime(buffer, 256, "%D %R", loctime);
  return (buffer);
}
