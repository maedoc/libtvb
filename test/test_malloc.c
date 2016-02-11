/* copyright 2016 Apache 2 sddekit authors */

#include <stdlib.h>

#include "sddekit.h"
#include "test.h"

TEST(malloc, reg0) {

	sd_malloc_reg_init();

	int *foo = sd_malloc(sizeof(int));

	EXPECT_EQ( SD_OK, sd_malloc_reg_query(foo) );

	sd_free(foo);

	sd_malloc_reg_stop();

}

TEST(malloc, reg1) {

	/* when not using register, don't know anything even for NULL */
	EXPECT_EQ( SD_UNKNOWN, sd_malloc_reg_query(NULL) );

	/* no reg, unknown */
	int *foo = sd_malloc (sizeof(int));
	EXPECT_EQ( SD_UNKNOWN, sd_malloc_reg_query(foo) );

	sd_malloc_reg_init();

	/* no way to know what was alloc before tracking */
	EXPECT_EQ( SD_ERR, sd_malloc_reg_query(foo) );

	sd_free(foo);
	foo = sd_malloc(sizeof(int));

	EXPECT_EQ( SD_OK, sd_malloc_reg_query(foo) );

	sd_free(foo);

	sd_malloc_reg_stop();
}

TEST(malloc, reg2) {

	sd_malloc_reg_init();
	/* alloc series of memory regions */
	int i;
	char *bar[10];
	for (i=0; i<10; i++)
		bar[i] = sd_malloc(sizeof(char)*4);

	/* check inside those regions */
	for (i=0; i<10; i++)
		EXPECT_EQ( SD_OK, sd_malloc_reg_query( bar[i] + (i % 4) ) );

	/* realloc a part of them for test */
	for (i=3; i<8; i++)
		bar[i] = sd_realloc(bar[i], sizeof(char)*10);

	/* free part of them */
	for (i=0; i<3; i++)
		sd_free(bar[i]);

	/* freed part returns err, part still in memory or the one reallocated is ok */
	for (i=0; i<10; i++)
	{
		if (i < 3)
			EXPECT_EQ( SD_ERR, sd_malloc_reg_query( bar[i] + (i % 4) ) );
		else if ((i >= 3) && (i < 8))
			EXPECT_EQ( SD_OK, sd_malloc_reg_query( bar[i] + ((3 * i) % 10) ) );
		else
			EXPECT_EQ( SD_OK, sd_malloc_reg_query( bar[i] + (i % 4) ) );
	}

	
	sd_malloc_reg_stop();

	/* check unknown and free the rest */
	for (i=0; i<7; i++)
	{
		EXPECT_EQ( SD_UNKNOWN, sd_malloc_reg_query(bar[i+3]) );
		sd_free(bar[i+3]);
	}
}
