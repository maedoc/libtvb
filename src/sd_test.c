/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

static int ntest=0, nfail=0;

void sd_test_failed(char *scond, char *fname, int lineno)
{
	nfail++;
	fprintf(stderr, "[sd_test] FAILURE %d/%d %s:%d `%s'\n",
			nfail, ntest, fname, lineno, scond);
}

void sd_test_true(bool cond, char *scond, char *fname, int lineno)
{
	ntest++;
	if (!cond)
		sd_test_failed(scond, fname, lineno);
}

int sd_test_report()
{
	if (nfail > 0) {
		sd_log_info( "[sd_test] %d/%d tests failed", nfail, ntest );
	} else {
		sd_log_info( "[sd_test] all %d tests passed", ntest );
	}
	return nfail;
}
