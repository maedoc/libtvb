/* copyright 2016 Apache 2 libtvb authors */

#include <stdlib.h>

#include "libtvb.h"
#include "test.h"

TEST(malloc, reg0) {
	uint32_t tic;

	tvb_malloc_reg_init();

	tic = tvb_malloc_total_nbytes();

	int *foo = tvb_malloc(sizeof(int));

	EXPECT_EQ( (uint32_t)sizeof(int) + tic, tvb_malloc_total_nbytes() );
	EXPECT_EQ( TVB_OK, tvb_malloc_reg_query(foo) );

	tvb_free(foo);

	tvb_malloc_reg_stop();

}

TEST(malloc, reg1) {

	/* when not using register, don't know anything even for NULL */
	EXPECT_EQ( TVB_UNKNOWN, tvb_malloc_reg_query(NULL) );

	/* no reg, unknown */
	int *foo = tvb_malloc (sizeof(int));
	EXPECT_EQ( TVB_UNKNOWN, tvb_malloc_reg_query(foo) );

	tvb_malloc_reg_init();

	/* no way to know what was alloc before tracking */
	EXPECT_EQ( TVB_ERR, tvb_malloc_reg_query(foo) );

	tvb_free(foo);
	foo = tvb_malloc(sizeof(int));

	EXPECT_EQ( TVB_OK, tvb_malloc_reg_query(foo) );

	tvb_free(foo);

	tvb_malloc_reg_stop();
}

TEST(malloc, reg2) {

	tvb_malloc_reg_init();
	/* alloc series of memory regions */
	int i;
	char *bar[10];
	for (i=0; i<10; i++)
		bar[i] = tvb_malloc(sizeof(char)*4);

	/* check inside those regions */
	for (i=0; i<10; i++)
		EXPECT_EQ( TVB_OK, tvb_malloc_reg_query( bar[i] + (i % 4) ) );

	uint32_t tic = tvb_malloc_total_nbytes();
	/* realloc a part of them for test */
	for (i=3; i<8; i++)
		bar[i] = tvb_realloc(bar[i], sizeof(char)*10);

	EXPECT_EQ( (uint32_t)(sizeof(char)*6*5) + tic, tvb_malloc_total_nbytes() );

    tic = tvb_malloc_total_nbytes();
	/* free part of them */
	for (i=0; i<3; i++)
		tvb_free(bar[i]);

	EXPECT_EQ( tic - (uint32_t)(sizeof(char)*4*3), tvb_malloc_total_nbytes() );
	
	/* freed part returns err, part still in memory or the one reallocated is ok */
	for (i=0; i<10; i++)
	{
		if (i < 3)
			EXPECT_EQ( TVB_ERR, tvb_malloc_reg_query( bar[i] + (i % 4) ) );
		else if ((i >= 3) && (i < 8))
			EXPECT_EQ( TVB_OK, tvb_malloc_reg_query( bar[i] + ((3 * i) % 10) ) );
		else
			EXPECT_EQ( TVB_OK, tvb_malloc_reg_query( bar[i] + (i % 4) ) );
	}

	
	tvb_malloc_reg_stop();

	/* check unknown and free the rest */
	for (i=0; i<7; i++)
	{
		EXPECT_EQ( TVB_UNKNOWN, tvb_malloc_reg_query(bar[i+3]) );
		tvb_free(bar[i+3]);
	}
}
