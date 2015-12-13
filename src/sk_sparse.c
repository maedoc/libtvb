/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>
#include <math.h>

#include "sk_sparse.h"
#include "sk_util.h"

int sk_sparse_from_dense(int m, int n, double *dA, double *dB, double eps,
		int *nnz, int **Or, int **Ic, double **sA, double **sB)
{
	int i, j, ci, nm;
	nm = n * m;
	/* count non-zeros*/
	*nnz = 0;
#define DO_IF(cond) for (i=0; i<nm; i++) if (cond) *nnz += 1
	if (eps==0.0) {
		DO_IF(dA[i]!=0.0);
	} else {
		DO_IF(fabs(dA[i])>eps);
	}
#undef DO_IF
	/* alloc */
	SK_MALLOCHECK(*Or = malloc (sizeof(int)*(m + 1)));
	SK_MALLOCHECK(*Ic = malloc (sizeof(int)**nnz));
	SK_MALLOCHECK(*sA = malloc (sizeof(double)**nnz));
	if (dB!=NULL)
		SK_MALLOCHECK(*sB = malloc (sizeof(double)**nnz));
	/* copy elements */
#define DO_IF(cond)\
		ci = 0;\
		for (i=0; i<m; i++) {\
			(*Or)[i] = ci;\
			for (j=0; j<n; j++) {\
				if (cond) {\
					(*Ic)[ci] = j;\
					(*sA)[ci] = dA[i*m+j];\
					if (dB!=NULL)\
						(*sB)[ci] = dB[i*m+j];\
					ci += 1;\
				}\
			}\
		}\
		(*Or)[m] = ci
	if (eps==0.0) {
		DO_IF(dA[i*m+j]!=0.0);
	} else {
		DO_IF(fabs(dA[i*m+j])>eps);
	}
#undef DO_IF
	return 0;
}
