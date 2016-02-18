/* copyright 2016 Apache 2 sddekit authors */

#include <stdlib.h>

#include "sddekit.h"
#include "test.h"

TEST(sparse, fromdense) {
	uint32_t n, nnz, *Or, *Ic;
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
	sd_sparse_from_dense(n, n, A, NULL, 0.0, &nnz, &Or, &Ic, &sA, NULL);

	EXPECT_EQ(3,nnz);
	EXPECT_EQ(0,Or[0]);
	EXPECT_EQ(2,Or[1]);
	EXPECT_EQ(3,Or[2]);
	EXPECT_EQ(0,Ic[0]);
	EXPECT_EQ(1,Ic[1]);
	EXPECT_EQ(1,Ic[2]);
	EXPECT_EQ(A[0],sA[0]);
	EXPECT_EQ(A[1],sA[1]);
	EXPECT_EQ(A[3],sA[2]);

	sd_free(Or);
	sd_free(Ic);
	sd_free(sA);

	/* with auxiliary matrix */
	sd_sparse_from_dense(n, n, A, B, 0.0, &nnz, &Or, &Ic, &sA, &sB);

	EXPECT_EQ(3,nnz);
	EXPECT_EQ(B[0],sB[0]);
	EXPECT_EQ(B[1],sB[1]);
	EXPECT_EQ(B[3],sB[2]);

	sd_free(Or);
	sd_free(Ic);
	sd_free(sA);
	sd_free(sB);

	/* apply cutoff */
	sd_sparse_from_dense(n, n, A, NULL, 1e-5, &nnz, &Or, &Ic, &sA, NULL);

	EXPECT_EQ(2,nnz);
	EXPECT_EQ(0,Or[0]);
	EXPECT_EQ(1,Or[1]);
	EXPECT_EQ(2,Or[2]);
	EXPECT_EQ(0,Ic[0]);
	EXPECT_EQ(1,Ic[1]);
	EXPECT_EQ(A[0],sA[0]);
	EXPECT_EQ(A[3],sA[1]);

	sd_free(Or);
	sd_free(Ic);
	sd_free(sA);

	/* with auxiliary matrix */
	sd_sparse_from_dense(n, n, A, B, 1e-5, &nnz, &Or, &Ic, &sA, &sB);

	EXPECT_EQ(2,nnz);
	EXPECT_EQ(B[0],sB[0]);
	EXPECT_EQ(B[3],sB[1]);

	sd_free(Or);
	sd_free(Ic);
	sd_free(sA);
	sd_free(sB);
}

/*
int main() {
	test_sparse_from_dense();
	return sd_test_report();
}
*/
