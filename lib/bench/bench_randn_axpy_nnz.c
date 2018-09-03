/* copyright 2016 Apache 2 libtvb authors */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "libtvb.h"

int main()
{
	int i, j, n, m;
	double *g, *z;
	time_t tic, toc;
	tvb_rng *rng = tvb_rng_new_default();

	n = 10000;
	m = 10;
	rng->seed(rng, 42);

	g = tvb_malloc (sizeof(double) * n);
	z = tvb_malloc (sizeof(double) * n);
	for (i=1; i<n; i+=100)
	{
		for (j=0; j<n; j++) g[i] = 0.0;

		/* put i nnz into g */
		for (j=0; j<i; j++) g[i] = 1.0;

		tic = clock();
		for (j=0; j<n; j++)
			if (g[j]!=0.0)
				g[j] *= rng->norm(rng);
		toc = clock();

		printf("i=%03d %.3fs\n", i, (double) (toc - tic) / CLOCKS_PER_SEC);

	}

	tic = clock();
	rng->fill_norm(rng, n, z);
	for (j=0; j<n; j++)
		g[j] *= z[j];
	toc = clock();
	printf("fill & mult %.3fs\n", (double) (toc - tic) / CLOCKS_PER_SEC);

	return 0;
}
