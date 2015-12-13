/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_SPARSE_H
#define SK_SPARSE_H

/**
 * Provides utilities for sparse structures, such as matrices which are 
 * mostly zero.
 */

/**
 * Solves a linear system A x = b where A is sparse, x & b are dense
 * vectors by reducing problem to dense system of equations and solving
 * with DGESV.
 *
 * TODO implement.
 *
 * \param[in] n number of equations in A x = b.
 * \param[in] A non-zero elements of sparse matrix A.
 * \param[out] x solution vector; if not NULL, memory used, otherwise it is allocated
 * and should be freed by the caller.
 * \param[in] b right hand side vector.
 */
void
sk_sparse_solve_ax_b(int n, double *A, double *x, double *b);

/**
 * Create CSR format sparse matrix from dense matrix, possibly thresholding.
 *
 * Caller responsible for freeing Or, Ic, sA when done.
 *
 * \param[in] m number of rows.
 * \param[in] n number of cols.
 * \param[in] dA elements of dense matrix.
 * \param[in] dB elements of second dense matrix (can be null)
 * \param[in] eps absolute threshold to consider element non-zero (can be 0.0 for no 
 * thresholding).
 * \param[out] nnz number of non-zeros.
 * \param[out] Or row offsets.
 * \param[out] Ic column indices.
 * \param[out] sA non-zeros elements of dA.
 * \param[out] sB non-zeros elements of dB. (is dB is null, this is unused).
 * \return 1 on success, 0 on failure.
 */
int sk_sparse_from_dense(int m, int n, double *dA, double *dB, double eps,
		int *nnz, int **Or, int **Ic, double **sA, double **sB);
#endif
