/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>

#include "sk_test.h"
#include "sk_sparse.h"

int test_sparse_from_dense()
{
	int n, nnz, *Or, *Ic;
	double A[4], B[4], *sA, *sB; 

	n = 2;
	A[0] = 1.0;
	A[1] = 1e-9;
	A[2] = 0.0;
	A[3] = 1e-3;
	B[0] = 1;
	B[1] = 2;
	B[2] = 3;
	B[3] = 4;

	/* no cutoff, eps=0 */
	sk_sparse_from_dense(n, n, A, NULL, 0.0, &nnz, &Or, &Ic, &sA, NULL);

	sk_test_true(nnz==3);
	sk_test_true(Or[0]==0);
	sk_test_true(Or[1]==2);
	sk_test_true(Or[2]==3);
	sk_test_true(Ic[0]==0);
	sk_test_true(Ic[1]==1);
	sk_test_true(Ic[2]==1);
	sk_test_true(sA[0]==A[0]);
	sk_test_true(sA[1]==A[1]);
	sk_test_true(sA[2]==A[3]);

	free(Or);
	free(Ic);
	free(sA);

	/* with auxiliary matrix */
	sk_sparse_from_dense(n, n, A, B, 0.0, &nnz, &Or, &Ic, &sA, &sB);

	sk_test_true(nnz==3);
	sk_test_true(sB[0]==B[0]);
	sk_test_true(sB[1]==B[1]);
	sk_test_true(sB[2]==B[3]);

	free(Or);
	free(Ic);
	free(sA);
	free(sB);

	/* apply cutoff */
	sk_sparse_from_dense(n, n, A, NULL, 1e-5, &nnz, &Or, &Ic, &sA, NULL);

	sk_test_true(nnz==2);
	sk_test_true(Or[0]==0);
	sk_test_true(Or[1]==1);
	sk_test_true(Or[2]==2);
	sk_test_true(Ic[0]==0);
	sk_test_true(Ic[1]==1);
	sk_test_true(sA[0]==A[0]);
	sk_test_true(sA[1]==A[3]);

	free(Or);
	free(Ic);
	free(sA);

	/* with auxiliary matrix */
	sk_sparse_from_dense(n, n, A, B, 1e-5, &nnz, &Or, &Ic, &sA, &sB);

	sk_test_true(nnz==2);
	sk_test_true(sB[0]==B[0]);
	sk_test_true(sB[1]==B[3]);

	free(Or);
	free(Ic);
	free(sA);
	free(sB);

	return 0;
}

int main() {
	test_sparse_from_dense();
	return sk_test_report();
}
