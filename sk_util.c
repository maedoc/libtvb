/* Apache 2.0 INS-AMU 2015 */

#include "stdlib.h"
#include "string.h"
#include "limits.h"

#include "sk_util.h"

static int compare_int(const void *a, const void *b)
{
	if ( *(int*) a <  *(int*) b ) return -1;
	if ( *(int*) a == *(int*) b ) return  0;
	else /* a > b */ return  1;
}

int sk_util_uniqi(const int n, const int *ints, int *nuniq, int **uints)
{ 
	int i, j, *ints_copy;
       
	/* sort copy of input vector */
	ints_copy = (int*) malloc(sizeof(int) * n);
	memcpy(ints_copy, ints, n*sizeof(int));
	qsort(ints_copy, n, sizeof(int), compare_int);

	/* count uniq */
	*nuniq = 1;
	for (i=0; i<(n-1); i++)
		if (ints_copy[i] != ints_copy[i+1])
			(*nuniq)++;

	*uints = (int*) malloc (sizeof(int) * *nuniq);

	/* copy unique into output array */
	j = 0;
	(*uints)[j++] = ints_copy[0];
	for (i=0; i<(n-1); i++)
		if (ints_copy[i] != ints_copy[i+1])
			(*uints)[j++] = ints_copy[i+1];

	free(ints_copy);
	
	return 0;
}
