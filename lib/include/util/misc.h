/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

/* TODO organize a performance primitive section, e.g. sd_pp_* */

/**
 * Obtain unique sorted integers.
 * \note Caller must free uints when done.
 * \param n number of elements
 * \param ints array of at least n integers.
 * \param[out] nuniq address of number of unique integers.
 * \param[out] uints address of array of unique integers.
 * \return Returns SD_OK if call succeeds, SD_ERR if error occurs.
 */
SD_API enum sd_stat 
sd_util_uniqi(uint32_t n,
	      uint32_t *ints, 
	      uint32_t *nuniq, 
	      uint32_t **uints);

/**
 * Create CSR format sparse matrix from dense matrix, possibly thresholding.
 *
 * Caller responsible for freeing Or, Ic, sA when done.
 *
 * \param[in] m number of rows.
 * \param[in] n number of cols.
 * \param[in] dA elements of dense matrix.
 * \param[in] dB elements of second dense matrix (can be null).
 * \param[in] eps absolute threshold to consider element non-zero (can be 0.0 for no .
 * thresholding).
 * \param[out] nnz number of non-zeros.
 * \param[out] Or row offsets.
 * \param[out] Ic column indices.
 * \param[out] sA non-zeros elements of dA.
 * \param[out] sB non-zeros elements of dB. (is dB is null, this is unused).
 * \return SD_OK if conversion succeeds, SD_ERR if error occurred.
 */
SD_API enum sd_stat 
sd_util_sparse_from_dense(
	uint32_t m, uint32_t n, 
	double *dA, double *dB, double eps,
	uint32_t *nnz, uint32_t **Or, uint32_t **Ic, 
	double **sA, double **sB);

/* memcpy is declared here to avoid sprinkling string.h includes all
 * over the code base.
 */
extern void *memcpy(void * restrict str1, const void * restrict str2, size_t n);

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288419716939937510)
#endif
