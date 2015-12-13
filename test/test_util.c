/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>

#include "sk_test.h"
#include "sk_util.h"

#define N 10

int test_util_uniqi()
{
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
	}

	{
		int i, nuniq, *uints;
		i=3;
		sk_util_uniqi(1, &i, &nuniq, &uints);
		sk_test_true(nuniq==1);
		sk_test_true(uints[0]==3);
		free(uints);
		return 0;
	}

	{
		int ints[2], nuniq, *uints;
		ints[0] = 1;
		ints[1] = 0;
		sk_util_uniqi(2, ints, &nuniq, &uints);
		sk_test_true(nuniq==2);
		sk_test_true(uints[0]==0);
		sk_test_true(uints[1]==1);
		free(uints);
		return 0;
	}
	return 0;
}
