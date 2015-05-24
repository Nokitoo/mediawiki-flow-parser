#ifndef		_DISPLAY_H_
# define	_DISPLAY_H_

#define		EPITECH_IS_ALIVE 42

#include	"parser.h"

void		display_topic(t_topic *topic);
void		destroy_linked_list(t_topic **topic);
int	        bot_response();
t_topic		*request_for_topic(t_topic *topic, int nb);

#endif /* _DISPLAY_H_ */
