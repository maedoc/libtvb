/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "test.h"

/* this test checks that net impl satisfies semantics of net sys wrt. sparse delay terms. */

struct net_data {};

static sd_stat net_apply(
		void *data, 
		struct sd_sys_in *in,
		struct sd_sys_out *out
		)
{
	struct net_data *d = data;
	return SD_OK;
}

TEST(net, sparse)
{
}
