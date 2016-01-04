/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

sd_log_msg_fp sd_log_msg = (sd_log_msg_fp) printf;

static bool sd_log_quiet = false;
static bool sd_log_verbose = true;

sd_log_msg_fp sd_log_get_msg()
{
	return sd_log_msg;
}

void sd_log_set_msg(sd_log_msg_fp fp)
{
	sd_log_msg = fp;
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
