#ifndef		_DISPLAY_H_
# define	_DISPLAY_H_

# define	PROMPT	"flow-parser>"

#include	"parser.h"

void		display_topic(t_topic *topic, int **from, int isHuman);
void		destroy_topics(t_topic *topic);
int	        bot_response(int *res);
t_topic		*request_for_topic(t_topic *topic, int nb);

#endif /* _DISPLAY_H_ */
