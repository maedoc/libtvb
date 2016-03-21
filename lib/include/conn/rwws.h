/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

#ifdef __cplusplus
extern "C" {
#endif

void
rwws_pre(struct sd_conn *sd_conn, double *pre, double *post, double *sums);

void
rwws_diff(struct sd_conn *sd_conn, double *pre, double *post, double *sums);

void
rwws_kuramoto(struct sd_conn *sd_conn, double *pre, double *post, double *sums);

#ifdef __cplusplus
}; /* extern "C" */
#endif