/* copyright 2016 Apache 2 sddekit authors */

#include <stdio.h>

#include "sk_log.h"

sk_log_msg_fp sk_log_msg = (sk_log_msg_fp) printf;
static int sk_log_quiet = 0;
static int sk_log_verbose = 1;

sk_log_msg_fp sk_log_get_msg() {
	return sk_log_msg;
}

void sk_log_set_msg(sk_log_msg_fp fp) {
	sk_log_msg = fp;
}

int sk_log_get_quiet() {
	return sk_log_quiet;
}

void sk_log_set_quiet(int flag) {
	sk_log_quiet = flag;
	if (flag)
		sk_log_verbose = 0;
}

int sk_log_get_verbose() {
	return sk_log_verbose;
}

void sk_log_set_verbose(int flag) {
	sk_log_verbose = flag;
	if (flag)
		sk_log_quiet = 0;
}
