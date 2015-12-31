/* copyright 2016 Apache 2 sddekit authors */

#ifndef SK_DAT_H
#define SK_DAT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Read a square matrix from file in ascii format into w.
 * \note w must be freed by user.
 * \param[in] fname string containing filename to readable file.
 * \param[out] n number of rows & cols.
 * \param[out] w matrix of weights.
 * \return 0 if succeeds, 1 if error occurs..
 */
int sk_dat_read_square_matrix(char *fname, int *n, double **w);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
