/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>

#include "gtest/gtest.h"

#include "sddekit.h"

#define N 10

TEST(util, uniqi) {
	{
		int i, *ints, *uints, nuniq;

		ints = (int*) sk_malloc (sizeof(int) * N);

		for (i=0; i<N; i++)
			ints[i] = (i - 2) % 3;

		sk_util_uniqi(N, ints, &nuniq, &uints);

		EXPECT_EQ( 5,nuniq );
		EXPECT_EQ( -2,uints[0] );
		EXPECT_EQ( -1,uints[1] );
		EXPECT_EQ( 0,uints[2] );
		EXPECT_EQ( 1,uints[3] );
		EXPECT_EQ( 2,uints[4] );

		sk_free(uints);
		sk_free(ints);
	}

	{
		int i, nuniq, *uints;
		i=3;
		sk_util_uniqi(1, &i, &nuniq, &uints);
		EXPECT_EQ(1,nuniq);
		EXPECT_EQ(3,uints[0]);
		sk_free(uints);
	}

	{
		int ints[2], nuniq, *uints;
		ints[0] = 1;
		ints[1] = 0;
		sk_util_uniqi(2, ints, &nuniq, &uints);
		EXPECT_EQ(2,nuniq);
		EXPECT_EQ(0,uints[0]);
		EXPECT_EQ(1,uints[1]);
		sk_free(uints);
	}
}
