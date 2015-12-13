/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>

#include "sk_test.h"
#include "sk_util.h"

#define N 10

int test_util_uniqi()
{
	int i, *ints, *uints, nuniq;

	ints = (int*) malloc (sizeof(int) * N);

	for (i=0; i<N; i++)
		ints[i] = (i - 2) % 3;

	sk_util_uniqi(N, ints, &nuniq, &uints);

	sk_test_true(nuniq == 5);
	sk_test_true(uints[0] == -2);
	sk_test_true(uints[1] == -1);
	sk_test_true(uints[2] == 0);
	sk_test_true(uints[3] == 1);
	sk_test_true(uints[4] == 2);

	free(uints);
	free(ints);

	return 0;
}
