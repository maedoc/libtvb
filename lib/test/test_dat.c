/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"
#include "test.h"

static int tvb_res_conn76_tl25[25] = { 
	2, 2, 0, 2, 0, 
	3, 2, 0, 0, 0,
	0, 0, 2, 0, 0,
	2, 0, 2, 2, 2,
	2, 2, 0, 1, 2
};

TEST(dat, read_square_matrix) {
	uint32_t i, n;
	double *w;
	tvb_util_read_square_matrix("bench/conn76/weights.txt", &n, &w);
	EXPECT_EQ(76, n);
	for (i=0; i<25; i++)
		EXPECT_EQ(tvb_res_conn76_tl25[i], w[(i/5)*76 + (i%5)]);
	tvb_free(w);
}
