/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "test.h"

TEST(log, simple)
{
	sd_log_info("formatting %s, answer is %d.", "supported", 42);
	sd_log_debug("Voldemort is %0.2f %% alive.", 32.4); 
}
