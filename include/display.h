#ifndef		_DISPLAY_H_
# define	_DISPLAY_H_

#include	"parser.h"

void		display_topic(t_topic *topic);
int	        bot_response();
t_topic		*request_for_topic(t_topic *topic, int nb);

#endif /* _DISPLAY_H_ */
