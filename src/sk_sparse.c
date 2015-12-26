/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>
#include <math.h>

#include "sk_sparse.h"
#include "sk_util.h"
#include "sk_malloc.h"
#include "sk_err.h"

int sk_sparse_from_dense(int m, int n, double *dA, double *dB, double eps,
		int *nnz, int **Or, int **Ic, double **sA, double **sB)
{
	int i, j, ci, nm;
	char *errmsg;
	nm = n * m;
	/* count non-zeros*/
	*nnz = 0;
	if (nnz==NULL) {
		sk_err("null nnz pointer.");
		return 1;
	}
#define DO_IF(cond) for (i=0; i<nm; i++) if (cond) *nnz += 1
	if (eps==0.0) {
		DO_IF(dA[i]!=0.0);
	} else {
		DO_IF(fabs(dA[i])>eps);
	}
#undef DO_IF
	/* alloc */
	*Or = sk_malloc (sizeof(int)*(m + 1));
	*Ic = sk_malloc (sizeof(int)**nnz);
	*sA = sk_malloc (sizeof(double)**nnz);
	if (dB!=NULL)
		*sB = sk_malloc (sizeof(double)**nnz);
	if (Or==NULL || Ic==NULL || sA==NULL || (dB!=NULL && sB==NULL)) {
		errmsg = "failed to allocate memory for sparse storage.";
		goto fail;
	}
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
fail:
	if (*Or!=NULL) sk_free(*Or);
	if (*Ic!=NULL) sk_free(*Ic);
	if (*sA!=NULL) sk_free(*sA);
	if (dB!=NULL)
		if (*sB!=NULL) sk_free(*sB);
	sk_err(errmsg);
	return 1;
}
