/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"
#include "test.h"

#define TEST_FOUND(topic, name) int tvb_test__ ## topic ## _ ## name();
#include "test_list.h"
#undef TEST_FOUND

#ifdef _MSC_VER
#include "windows.h"
#endif

static void run_all() {
#define TEST_FOUND(topic, name) \
	tvb_test__ ## topic ## _ ## name();
#include "test_list.h"
#undef TEST_FOUND
}


int main(int argc, char *argv[]) {

#ifdef _MSC_VER
	char buf[1024];
	GetCurrentDirectory(1024, buf);
	tvb_log_info("cwd is %s\n", buf);
#endif

	if (argc > 1) {
		int i;
		for (i=1; i<argc; i++) {
#define TEST_FOUND(topic, name) if (!strcmp(#topic "_" #name, argv[i]))\
			{\
				tvb_log_info("running test %s_%s selected by cli arg.", #topic, #name); \
				tvb_test__ ## topic ## _ ## name(); \
			}
#include "test_list.h"
#undef TEST_FOUND
		}
	}
	else
		run_all();

	return tvb_test_report();
}
