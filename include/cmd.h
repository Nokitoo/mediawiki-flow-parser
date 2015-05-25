#ifndef		_CMD_H_
# define	_CMD_H_

#include "parser.h"
#include "display.h"

int		read_cmd(t_topic **topics, t_topic_info **infos);
t_topic		*viewtopiclist(t_topic *topics, char *url);
t_topic_info    *viewtopic(t_topic *topic, t_topic_info *infos, char *url);

#endif /*	_CMD_H_ */
