#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

double func(cb c, void* data, double x) {
	double y;
	fprintf(stderr, "[lib/func] calling cb with %f\n", x);
	y = (*c)(data, x);
	fprintf(stderr, "[lib/func] done with %f\n", y);
	return y - 42.0;
}

void func2(cb2 c, void *data) {
	int i, n = 5;
	double *x = malloc(sizeof(double) *n);
	for (i=0; i<n; i++)
		fprintf(stderr, "x[%d]=%.2f ", i, x[i]=i*1.2);
	fprintf(stderr, "\n");
	(*c)(data, n, x);
	for (i=0; i<n; i++)
		fprintf(stderr, "x[%d]=%.2f ", i, x[i]);
	fprintf(stderr, "\n");
}

