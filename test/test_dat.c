/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "sddekit.h"

static int sk_res_conn76_tl25[25] = { 
	2, 2, 0, 2, 0, 
	3, 2, 0, 0, 0,
	0, 0, 2, 0, 0,
	2, 0, 2, 2, 2,
	2, 2, 0, 1, 2
};

TEST(dat, read_square_matrix) {
	int i, n;
	double *w;
	char *fname;
	sk_util_res_name("res/conn76/weights.txt", &fname);
	sk_dat_read_square_matrix(fname, &n, &w);
	EXPECT_EQ(76,n);
	for (i=0; i<25; i++)
		EXPECT_EQ(sk_res_conn76_tl25[i], w[(i/5)*76 + (i%5)]);
	sk_free(w);
	sk_free(fname);
}
