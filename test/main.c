/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "test.h"

#define TEST_FOUND(topic, name) int sd_test__ ## topic ## _ ## name();
#include "test_list.h"
#undef TEST_FOUND

#ifdef _MSC_VER
#include "windows.h"
#endif

static void run_all() {
#define TEST_FOUND(topic, name) \
	sd_test__ ## topic ## _ ## name();
#include "test_list.h"
#undef TEST_FOUND
}


int main(int argc, char *argv[]) {

#ifdef _MSC_VER
	char buf[1024];
	GetCurrentDirectory(1024, buf);
	sd_log_info("cwd is %s\n", buf);
#endif

	if (argc > 1) {
		int i;
		for (i=1; i<argc; i++) {
#define TEST_FOUND(topic, name) if (!strcmp(#topic "_" #name, argv[i]))\
			{\
				sd_log_info("running test %s_%s selected by cli arg.", #topic, #name); \
				sd_test__ ## topic ## _ ## name(); \
			}
#include "test_list.h"
#undef TEST_FOUND
		}
	}
	else
		run_all();

	sd_log_set_verbose(1);
	return sd_test_report();
}
