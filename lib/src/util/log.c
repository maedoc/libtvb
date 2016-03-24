/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

#include <stdarg.h>
#include <stdio.h>

static void fprintf_handler(enum sd_log_level level, char *message)
{
	FILE *out;
	char *s_level;
	if (level == SD_LOG_ERROR)
	{
		out = stderr;
		s_level = " ERROR";
	}
	else
	{
		out = stdout;
		s_level = "";
	}
	fprintf(out, "[SDDEKit%s] %s\n", s_level, message); 
}

static sd_log_handler handler = &fprintf_handler;

void sd_log_set_handler(sd_log_handler new_handler)
{
	handler = new_handler;
}

sd_log_handler sd_log_get_handler()
{
	return handler;
}

static bool error_occurred = false;

void sd_log_handle(enum sd_log_level level, char *format, ...)
{
	char message[2048];
	va_list args;
	error_occurred = level == SD_LOG_ERROR;
	va_start(args, format);
	vsnprintf(message, 2048, format, args);
	va_end(args);
	handler(level, message);
}

bool sd_log_get_err_and_reset()
{
	bool occurred = error_occurred;
	error_occurred = false;
	return occurred;
}
