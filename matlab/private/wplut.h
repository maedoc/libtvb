/* copyright 2016 Apache 2 sddekit authors */

/* defines wrapper pointer & look up table query */

#include "matrix.h"

typedef void (*wp)(int nl, mxArray **pl, int nr, mxArray **pr);

wp sd_mex_lut(char *obj, char *meth);
