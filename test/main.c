/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "test.h"

#define TEST_FOUND(name) int name();
#include "test_list.h"
#undef TEST_FOUND

#ifdef _MSC_VER
#include "windows.h"
#endif

int main() {

#ifdef _MSC_VER
	char buf[1024];
	GetCurrentDirectory(1024, buf);
	sd_log_info("cwd is %s\n", buf);
#endif

#define TEST_FOUND(name) \
	name();
#include "test_list.h"
#undef TEST_FOUND

	sd_log_set_verbose(1);
	return sd_test_report();
}
