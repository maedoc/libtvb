/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct sd_conn sd_conn;

struct sd_conn
{
	void *ptr;
};

typedef struct connd
{
	bool d_not_null;
	uint32_t nnz
	       , * restrict Or
	       , * restrict Ic;
	double * restrict w
	     , * restrict d;
} connd;

static bool have_delays(sd_conn *conn)
{
	return ((connd*)conn)->d_not_null;
}
