/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

void sd_err_default_handler(int err, char *file, int line, char *func, char *reason) 
{
	(void) err;
	sd_log_debug("%s raised error at %s:%d `%s'.", func, file, line, reason);
} 

static sd_err_handler_fp handler = sd_err_default_handler;

sd_err_handler_fp sd_err_get_handler() { return sd_err_handler; }

void sd_err_set_handler(sd_err_handler_fp fp) { 
	if (fp==NULL)
		sd_log_debug("set NULL error handler.");
	handler = fp; 
}

void sd_err_handler(int err, char *file, int line, char *func, char *reason) {
	if (handler!=NULL)
		(*handler)(err, file, line, func, reason);
#ifdef SDDEBUG
	else
		sd_log_debug("%s raised error at %s:%d `%s' (ignored by null handler).", func, file, line, reason);
#endif
}
