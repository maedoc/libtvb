
/* copyright 2016 Apache 2 sddekit authors */

/* TODO clang++ doesn't like restrict in c++11 mode? */
#define restrict 

#include "sddekit.h"
#include <math.h>
#include "conn/data.h"
#include "conn/rwws.h"

template <class cfun> static void
rwws_cfun(
    struct sd_conn *sd_conn, double * restrict pre,
    double * restrict post, double * restrict sums)
{
    cfun cf;
    /* TODO would need to move struct conn decl to private header */
	struct conn *conn = (struct conn *) sd_conn->data;
    /* TODO omp parallel */
	for (uint32_t i=0; i<conn->n_row; i++)
	{
		double sum = 0.0;
		for (uint32_t j=conn->row_offsets[i]; j<conn->row_offsets[i+1]; j++)
			sum += conn->weights[j] * cf(pre[j], 0.0 /* TODO */);
		sums[i] = sum;
	}
}

class cf_pre
{
public:
    double operator()(double pre, double post)
    {
        return pre;
    }
};

class cf_diff
{
public:
    double operator()(double pre, double post)
    {
        return post - pre;
    }
};

class cf_kuramoto
{
public:
    double operator()(double pre, double post)
    {
        return sin(post - pre);
    }
};

/* TODO declare these export C, use from conn.c */
void
rwws_pre(struct sd_conn *sd_conn, double *pre, double *post, double *sums)
{
    return rwws_cfun<cf_pre>(sd_conn, pre, post, sums);
}

void
rwws_diff(struct sd_conn *sd_conn, double *pre, double *post, double *sums)
{
    return rwws_cfun<cf_diff>(sd_conn, pre, post, sums);
}

void
rwws_kuramoto(struct sd_conn *sd_conn, double *pre, double *post, double *sums)
{
    return rwws_cfun<cf_kuramoto>(sd_conn, pre, post, sums);
}