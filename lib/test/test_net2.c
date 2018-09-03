/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"
#include "test.h"

/* this test checks that net impl satisfies semantics of net sys wrt. sparse delay terms. */

struct net_data {};

static tvb_stat net_apply(
		void *data, 
		struct tvb_sys_in *in,
		struct tvb_sys_out *out
		)
{
	struct net_data *d = data;
	return TVB_OK;
}

TEST(net, sparse)
{
}
