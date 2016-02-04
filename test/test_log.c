/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "test.h"

TEST(log, simple)
{
	sd_log_info("formatting %s, answer is %d.", "supported", 42);
	sd_log_info("next line debug shouldn't print:");
	sd_log_set_verbose(0);
	sd_log_debug("Voldemort is %0.2f %% alive.", 32.4); 
	sd_log_set_verbose(1);
	sd_log_info("But now it should:");
	sd_log_debug("quiet means no info:"); 
	sd_log_set_quiet(1);
	sd_log_info("echo?");
	sd_log_debug("echo?");
	sd_log_set_verbose(1);
}

static int n_msg = 0;

static int logger(char *fmt, ...) {
	(void) fmt;
	n_msg += 1;
	return 0;
}

TEST(log, custom_handler) {
	int wasq, wasv;
	sd_log_msg_fp oldfp;
	wasq = sd_log_is_quiet();
	wasv = sd_log_is_verbose();
	oldfp = sd_log_get_msg();
	sd_log_set_msg((sd_log_msg_fp) &logger);
	sd_log_set_quiet(0);
	sd_log_set_verbose(0);
	EXPECT_EQ(0, n_msg);
	sd_log_info("shouldn't see this message in terminal.");
	sd_log_debug("neither this one.");
	EXPECT_EQ(1, n_msg);
	sd_log_set_verbose (1);
	sd_log_info("echo");
	sd_log_debug("echo");
	EXPECT_EQ(3, n_msg);
	sd_log_set_quiet (1);
	sd_log_info("echo");
	sd_log_debug("echo");
	EXPECT_EQ(3, n_msg);
	sd_log_set_msg(oldfp);
	sd_log_set_quiet(wasq);
	sd_log_set_verbose(wasv);
}
