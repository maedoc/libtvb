/* copyright 2016 Apache 2 sddekit authors */

#include <stdlib.h>

#include "sddekit.h"
#include "test.h"

#define N 10

TEST(util, uniqi) {
	{
		uint32_t i, *ints, *uints, nuniq;

		ints = sd_malloc (sizeof(uint32_t) * N);

		for (i=0; i<(N-2); i++)
			ints[i] = (i + 2) % 3;
		ints[8] = 3;
		ints[9] = 4;

		sd_util_uniqi(N, ints, &nuniq, &uints);

		EXPECT_EQ( 5,nuniq );
		EXPECT_EQ( 0,uints[0] );
		EXPECT_EQ( 1,uints[1] );
		EXPECT_EQ( 2,uints[2] );
		EXPECT_EQ( 3,uints[3] );
		EXPECT_EQ( 4,uints[4] );

		sd_free(uints);
		sd_free(ints);
	}

	{
		uint32_t i, nuniq, *uints;
		i=3;
		sd_util_uniqi(1, &i, &nuniq, &uints);
		EXPECT_EQ(1,nuniq);
		EXPECT_EQ(3,uints[0]);
		sd_free(uints);
	}

	{
		uint32_t ints[2], nuniq, *uints;
		ints[0] = 1;
		ints[1] = 0;
		sd_util_uniqi(2, ints, &nuniq, &uints);
		EXPECT_EQ(2,nuniq);
		EXPECT_EQ(0,uints[0]);
		EXPECT_EQ(1,uints[1]);
		sd_free(uints);
	}
}
