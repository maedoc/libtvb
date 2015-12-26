/* Apache 2.0 INS-AMU 2015 */

#include "sddekit.h"

static int n_msg = 0;

static int logger(char *fmt, ...) {
	(void) fmt;
	n_msg += 1;
	return 0;
}

TEST(err, basic) {
	int wasq, wasv;
	sk_log_msg_fp oldfp;
	/* record logger state */
	wasq = sk_log_get_quiet();
	wasv = sk_log_get_verbose();
	oldfp = sk_log_get_msg();
	/* */
	sk_log_set_msg((sk_log_msg_fp) &logger);
	sk_log_set_verbose(1);
	EXPECT_EQ(0, n_msg);
	sk_err("trip!");
	EXPECT_EQ(1, n_msg);
	/* restore logger state */
	sk_log_set_msg(oldfp);
	sk_log_set_quiet(wasq);
	sk_log_set_verbose(wasv);
}
