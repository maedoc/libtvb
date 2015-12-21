/* Apache 2.0 INS-AMU 2015 */

#include "sddekit.h"

#define TEST_FOUND(name) int name();
#include "test_list.h"
#undef TEST_FOUND

int sk_test_run_all() {
#define TEST_FOUND(name) name();
#include "test_list.h"
#undef TEST_FOUND
	return sk_test_report();
}
