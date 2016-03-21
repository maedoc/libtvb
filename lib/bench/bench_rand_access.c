#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>

#define N 10000000

int main()
{
	int r;
	uint32_t i, j, len;
	double sum, *values, values0[1], reft, curt;
	clock_t tic, toc;

	sum = 0;
	tic = clock();
	len = 1;
	values0[0] = 1.0;
	for (i=0; i<N; i++)
	{
		r = rand();
		r %= len;
		sum += values0[r];
	}
	toc = clock();
	reft = (double) (toc - tic) / CLOCKS_PER_SEC;
	printf("S(10M)=%g %0.6f s %g cycles/iter\n", sum, reft,
		reft/N*3.4e9);

	for (j=2; j<(1024*1024); j*=2)
	{
		sum = 0;
		len = j;
		values = malloc (sizeof(double) * j);
		for (i=0; i<j; i++)
			values[i] = i * 1.0;
		tic = clock();
		for (i=0; i<N; i++)
		{
			r = rand();
			r %= len;
			sum += values[r];
		}
		toc = clock();
		free(values);
		curt = (double) (toc - tic) / CLOCKS_PER_SEC;
		if (j==2)
			reft = curt;
		printf("S(10M)=%g %d KB +%0.6f s +%f cycles/iter\n", sum, 
			j*8/1024, (curt - reft), (curt - reft)/N*1.0e9);
	}

	return 0;
}
