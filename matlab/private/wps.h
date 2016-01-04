/* copyright 2016 Apache 2 sddekit authors */

/* defines common headers for wrapper code */

#ifndef WPS_H
#define WPS_H

#include <string.h>
#include "matrix.h"
#include "mex.h"
#include "sddekit.h"
#include "util.h"
#include "cb.h"

#ifndef _
#define _(o, m, ...) void sd_mex_wrap_ ## o ## _ ## m\
	(int nl, mxArray **pl, int nr, mxArray **pr)\
	{ __VA_ARGS__ }
#endif

#endif

