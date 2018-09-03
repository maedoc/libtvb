/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

#include <stdarg.h>
#include <stdio.h>

static void fprintf_handler(enum tvb_log_level level, char *message)
{
	FILE *out;
	char *s_level;
	if (level == TVB_LOG_ERROR)
	{
		out = stderr;
		s_level = " ERROR";
	}
	else
	{
		out = stdout;
		s_level = "";
	}
	fprintf(out, "[libtvb%s] %s\n", s_level, message); 
}

static tvb_log_handler handler = &fprintf_handler;

void tvb_log_set_handler(tvb_log_handler new_handler)
{
	handler = new_handler;
}

tvb_log_handler tvb_log_get_handler()
{
	return handler;
}

static bool error_occurred = false;

void tvb_log_handle(enum tvb_log_level level, char *format, ...)
{
	char message[2048];
	va_list args;
	error_occurred = level == TVB_LOG_ERROR;
	va_start(args, format);
	vsnprintf(message, 2048, format, args);
	va_end(args);
	handler(level, message);
}

bool tvb_log_get_err_and_reset()
{
	bool occurred = error_occurred;
	error_occurred = false;
	return occurred;
}
