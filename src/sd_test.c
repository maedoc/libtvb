/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct { bool pass; char *f, *cond, *fn; int l; } test;

static test *tests;

static uint32_t ntest=0, nfail=0, tests_len=0;

static char *cpstr(const char *str)
{
	uint32_t nc = strlen(str) + 1;
	char *out = sd_malloc(sizeof(char) * nc);
	memcpy(out, str, sizeof(char) * nc);
	return out;
}

static void test_record(bool cond, const char *scond, const char *fname, int lineno, const char *func)
{
	test t = {.pass=cond, .l=lineno};
	t.f = cpstr(fname);
	t.cond = cpstr(scond);
	t.fn = cpstr(func);
	if (ntest == tests_len)
	{
		if (tests_len == 0)
		{
			tests = sd_malloc(sizeof(test));
			tests_len = 1;
		}
		else
		{
			tests = sd_realloc(tests, sizeof(test) * 2 * tests_len);
			tests_len *= 2;
		}
		if (tests == NULL)
		{
			fprintf(stderr, "test alloc failed, abort!\n");
			exit(1);
		}
	}
	tests[ntest] = t;
}

static void free_tests()
{
	uint32_t i;
	for (i=0; i<ntest; i++)
	{
		test t = tests[i];
		sd_free(t.f);
		sd_free(t.cond);
		sd_free(t.fn);
	}
	sd_free(tests);
}

static void dump_junit_xml()
{
	uint32_t i;
	FILE *fd = fopen("junit.xml", "w");
	if (fd == NULL)
	{
		fprintf(stderr, "failed to open junit.xml\n");
		return;
	}
	fprintf(fd, "<testsuite tests=\"%d\">\n", ntest);
	for (i=0; i<ntest; i++)
	{
		test t = tests[i];
		fprintf(fd, "  <testcase classname=\"%s\" name=\"%d\"", t.fn, t.l);
		if (t.pass)
			fprintf(fd, " />\n");
		else
			fprintf(fd, ">\n"
						"    <failure type=\"fail\">%s</failure>\n"
					    "  </testcase>\n", t.cond);
	}
	fprintf(fd, "</testsuite>\n");
}

void sd_test_failed(const char *scond, const char *fname, int lineno)
{
	nfail++;
	fprintf(stderr, "[sd_test] FAILURE %d/%d %s:%d `%s'\n",
			nfail, ntest, fname, lineno, scond);
}

void sd_test_true(bool cond, const char *scond, const char *fname, int lineno, const char *func)
{
	test_record(cond, scond, fname, lineno, func);
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
	dump_junit_xml();
	free_tests();
	return nfail;
}
