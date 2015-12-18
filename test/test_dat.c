#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "sk_dat.h"
#include "sk_test.h"

static int sk_res_conn76_tl25[25] = { 
	2, 2, 0, 2, 0, 
	3, 2, 0, 0, 0,
	0, 0, 2, 0, 0,
	2, 0, 2, 2, 2,
	2, 2, 0, 1, 2
};


int main() {
	int i, n;
	double *w;
	sk_dat_read_square_matrix("../../res/conn76/weights.txt", &n, &w);
	sk_test_true(n==76);
	for (i=0; i<25; i++)
		sk_test_true(sk_res_conn76_tl25[i]==w[(i/5)*76 + (i%5)]);
	free(w);
	return sk_test_report();
}
