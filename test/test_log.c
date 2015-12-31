/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

TEST(log, simple)
{
	sk_log_info("formatting %s, answer is %d.", "supported", 42);
	sk_log_info("next line debug shouldn't print:");
	sk_log_debug("Voldemort is %0.2f %% alive.", 32.4); 
	sk_log_set_verbose(1);
	sk_log_info("But now it should:");
	sk_log_debug("quiet means no info:"); 
	sk_log_set_quiet(1);
	sk_log_info("echo?");
	sk_log_debug("echo?");
}

static int n_msg = 0;

static int logger(char *fmt, ...) {
	(void) fmt;
	n_msg += 1;
	return 0;
}

TEST(log, custom_handler) {
	int wasq, wasv;
	sk_log_msg_fp oldfp;
	wasq = sk_log_get_quiet();
	wasv = sk_log_get_verbose();
	oldfp = sk_log_get_msg();
	sk_log_set_msg((sk_log_msg_fp) &logger);
	sk_log_set_quiet(0);
	sk_log_set_verbose(0);
	EXPECT_EQ(0, n_msg);
	sk_log_info("shouldn't see this message in terminal.");
	sk_log_debug("neither this one.");
	EXPECT_EQ(1, n_msg);
	sk_log_set_verbose (1);
	sk_log_info("echo");
	sk_log_debug("echo");
	EXPECT_EQ(3, n_msg);
	sk_log_set_quiet (1);
	sk_log_info("echo");
	sk_log_debug("echo");
	EXPECT_EQ(3, n_msg);
	sk_log_set_msg(oldfp);
	sk_log_set_quiet(wasq);
	sk_log_set_verbose(wasv);
}
