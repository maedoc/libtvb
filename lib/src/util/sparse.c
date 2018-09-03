/* copyright 2016 Apache 2 libtvb authors */

#include <math.h>
#include "libtvb.h"

enum tvb_stat tvb_util_sparse_from_dense(uint32_t m, uint32_t n, 
		double *dA, double *dB, double eps,
		uint32_t *nnz, uint32_t **Or, uint32_t **Ic, 
		double **sA, double **sB)
{
	uint32_t i, j, ci, nm;
	char *errmsg;
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
	*Or = tvb_malloc (sizeof(uint32_t)*(m + 1));
	*Ic = tvb_malloc (sizeof(uint32_t)**nnz);
	*sA = tvb_malloc (sizeof(double)**nnz);
	if (dB!=NULL)
		*sB = tvb_malloc (sizeof(double)**nnz);
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
	if (*Or!=NULL) tvb_free(*Or);
	if (*Ic!=NULL) tvb_free(*Ic);
	if (*sA!=NULL) tvb_free(*sA);
	if (dB!=NULL)
		if (*sB!=NULL) tvb_free(*sB);
	tvb_err("%s", errmsg);
	return 1;
}
