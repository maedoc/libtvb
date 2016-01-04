/* copyright 2016 Apache 2 sddekit authors */

/* callbacks (sys, sch, out, hfill) support */

#include "matrix.h"
#include "sddekit.h"

/* Define system in MATLAB, callable from sddekit */
typedef struct sd_sys_matlab_data sd_sys_matlab_data;

SK_DEFSYS(sd_sys_matlab);

sd_sys_matlab_data *sd_sys_matlab_alloc();
int sd_sys_matlab_init(sd_sys_matlab_data *d, int nc_out);


/* the rest TODO */
typedef struct { mxArray *data; } sd_sch_matlab_data;

SK_DEFSCH(sd_sch_matlab);

typedef struct { mxArray *data; } sd_out_matlab_data;

SK_DEFOUT(sd_out_matlab);

SK_DEFHFILL(sd_hist_hfill_matlab);
