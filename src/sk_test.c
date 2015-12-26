/* Apache 2.0 INS-AMU 2015 */

#include <stdio.h>

#include "sk_test.h"
#include "sk_log.h"

static int ntest=0, nfail=0;

void sk_test_failed(char *scond, char *fname, int lineno)
{
	nfail++;
	fprintf(stderr, "[sk_test] FAILURE %d/%d %s:%d `%s'\n",
			nfail, ntest, fname, lineno, scond);
}

void sk_test_true(int cond, char *scond, char *fname, int lineno)
{
	ntest++;
	if (!cond)
		sk_test_failed(scond, fname, lineno);
}

int sk_test_report()
{
	if (nfail > 0) {
		sk_log_info( "[sk_test] %d/%d tests failed", nfail, ntest );
	} else {
		sk_log_info( "[sk_test] all %d tests passed", ntest );
	}
	return nfail;
}
