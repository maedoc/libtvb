/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "test.h"

static int n_msg = 0;

static int logger(char *fmt, ...) {
	(void) fmt;
	n_msg += 1;
	return 0;
}

TEST(err, basic) {
	int wasq, wasv;
	sd_log_msg_fp oldfp;
	/* record logger state */
	wasq = sd_log_is_quiet();
	wasv = sd_log_is_verbose();
	oldfp = sd_log_get_msg();
	/* */
	sd_log_set_msg((sd_log_msg_fp) &logger);
	sd_log_set_verbose(1);
	EXPECT_EQ(0, n_msg);
	sd_err("trip!");
	EXPECT_EQ(1, n_msg);
	/* restore logger state */
	sd_log_set_msg(oldfp);
	sd_log_set_quiet(wasq);
	sd_log_set_verbose(wasv);
}
