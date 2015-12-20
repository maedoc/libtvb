/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "randomkit.h"
#include "sk_malloc.h"

int main()
{
	int i, j, n, m;
	double *g, *z;
	time_t tic, toc;
	rk_state rng;


	n = 10000;
	m = 10;
	rk_seed(42, &rng);

	g = sk_malloc (sizeof(double) * n);
	z = sk_malloc (sizeof(double) * n);
	for (i=1; i<n; i+=100)
	{
		for (j=0; j<n; j++) g[i] = 0.0;

		/* put i nnz into g */
		for (j=0; j<i; j++) g[i] = 1.0;

		tic = clock();
		for (j=0; j<n; j++)
			if (g[j]!=0.0)
				g[j] *= rk_gauss(&rng);
		toc = clock();

		printf("i=%03d %.3fs\n", i, (double) (toc - tic) / CLOCKS_PER_SEC);

	}

	tic = clock();
	rk_gauss_fill(&rng, n, z);
	for (j=0; j<n; j++)
		g[j] *= z[j];
	toc = clock();
	printf("fill & mult %.3fs\n", (double) (toc - tic) / CLOCKS_PER_SEC);

	return 0;
}
