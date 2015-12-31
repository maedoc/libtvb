/* copyright 2016 Apache 2 sddekit authors */

#include <stdio.h>

#include "sk_err.h"
#include "sk_log.h"

void sk_err_default_handler(int errno, char *file, int line, char *reason) {
	sk_log_debug("errno=%d %s:%s `%s'.", errno, file, line, reason);
} 

static sk_err_handler_fp handler = sk_err_default_handler;

sk_err_handler_fp sk_err_get_handler() { return sk_err_handler; }

void sk_err_set_handler(sk_err_handler_fp fp) { 
	if (fp==NULL)
		sk_log_debug("set NULL error handler.");
	handler = fp; 
}

void sk_err_handler(int errno, char *file, int line, char *reason) {
	if (handler!=NULL)
		(*handler)(errno, file, line, reason);
#ifdef SKDEBUG
	else
		sk_log_debug("errno=%d %s:%s `%s' ignored by null handler.", errno, file, line, reason);
#endif
}
