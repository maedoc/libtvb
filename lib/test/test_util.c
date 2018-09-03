/* copyright 2016 Apache 2 libtvb authors */

#include <stdlib.h>

#include "libtvb.h"
#include "test.h"

#define N 10

TEST(util, uniqi) {
	{
		uint32_t i, *ints, *uints, nuniq;

		ints = tvb_malloc (sizeof(uint32_t) * N);

		for (i=0; i<(N-2); i++)
			ints[i] = (i + 2) % 3;
		ints[8] = 3;
		ints[9] = 4;

		tvb_util_uniqi(N, ints, &nuniq, &uints);

		EXPECT_EQ( 5,nuniq );
		EXPECT_EQ( 0,uints[0] );
		EXPECT_EQ( 1,uints[1] );
		EXPECT_EQ( 2,uints[2] );
		EXPECT_EQ( 3,uints[3] );
		EXPECT_EQ( 4,uints[4] );

		tvb_free(uints);
		tvb_free(ints);
	}

	{
		uint32_t i, nuniq, *uints;
		i=3;
		tvb_util_uniqi(1, &i, &nuniq, &uints);
		EXPECT_EQ(1,nuniq);
		EXPECT_EQ(3,uints[0]);
		tvb_free(uints);
	}

	{
		uint32_t ints[2], nuniq, *uints;
		ints[0] = 1;
		ints[1] = 0;
		tvb_util_uniqi(2, ints, &nuniq, &uints);
		EXPECT_EQ(2,nuniq);
		EXPECT_EQ(0,uints[0]);
		EXPECT_EQ(1,uints[1]);
		tvb_free(uints);
	}
}
