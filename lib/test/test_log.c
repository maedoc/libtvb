/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"
#include "test.h"

TEST(log, simple)
{
	tvb_log_info("formatting %s, answer is %d.", "supported", 42);
	tvb_log_debug("Voldemort is %0.2f %% alive.", 32.4); 
}
