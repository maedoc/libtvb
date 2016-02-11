/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

#include <stdarg.h>

#define SIZE 2048

static bool sd_log_quiet = false;
static bool sd_log_verbose = true;

static sd_log_handler handler = (sd_log_handler)sd_log_handler_printf;
sd_log_msg_fp sd_log_msg_ptr = (sd_log_msg_fp)sd_log_msg;

void sd_log_handler_printf(const char *msg)
{
	printf("%s", msg);
}


/* Generate a single string and pass it to the appropriate handler */
void sd_log_msg(const char *format, ...)
{
	char msg[SIZE];

	va_list args;
	va_start(args, format);
	vsnprintf(msg, SIZE, format, args);
	va_end(args);

	/* Function call to the default handler */
	handler(msg);
}

void sd_log_set_handler(sd_log_handler h)
{
	if((handler = h) == NULL)
		sd_err("NULL handler provided");
}

sd_log_handler sd_log_get_handler()
{
	return handler;
}

sd_log_msg_fp sd_log_get_msg()
{
	return sd_log_msg_ptr;
}

void sd_log_set_msg(sd_log_msg_fp fp)
{
	sd_log_msg_ptr = fp;
}

bool sd_log_is_quiet()
{
	return sd_log_quiet;
}

void sd_log_set_quiet(bool flag)
{
	sd_log_quiet = flag;
	if (flag)
		sd_log_verbose = 0;
}

bool sd_log_is_verbose()
{
	return sd_log_verbose;
}

void sd_log_set_verbose(bool flag)
{
	sd_log_verbose = flag;
	if (flag)
		sd_log_quiet = 0;
}
