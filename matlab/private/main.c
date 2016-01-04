/* copyright 2016 Apache 2 sddekit authors */

/* main.c handles initializing the wrapper and dispatching calls */

#include "mex.h"
#include "sddekit.h"
#include "wplut.h"

static int isinit = 0;
static int ncalls = 0;

void err_handler(int err, char *file, int line, char *func, char *reason)
{
	char msgid[1024];
	sd_log_debug("\n\t%s at <a href=\"matlab: "
		     "opentoline('%s', %d)\">%s:%d</a> `%s'.",
		     func, file, line, file, line, reason);
	sprintf(msgid, "sddekit:%s", func);
	mexErrMsgIdAndTxt(msgid, reason);
}

void *malloc_persistent(size_t size) {
    void *p = mxMalloc(size);
    if (p!=NULL);
        mexMakeMemoryPersistent(p);
    return p;
}

void *realloc_persistent(void *ptr, size_t size) {
    void *p = mxRealloc(ptr, size);
    if (p!=NULL)
        mexMakeMemoryPersistent(p);
    return p;
}

void mexFunction(int nlhs, mxArray *plhs[], 
		 int nrhs, const mxArray *prhs[])
{
	char obj[256], meth[256];
	wp p;

	if (!isinit)
	{
		/* set memory allocators, log & error handlers */
		sd_malloc_set_allocators(( sd_malloc_t) malloc_persistent, 
				(sd_realloc_t) realloc_persistent,
				(   sd_free_t) mxFree);
		sd_err_set_handler((sd_err_handler_fp) err_handler);
		sd_log_set_msg((sd_log_msg_fp) mexPrintf);
		isinit = 1;
		sd_log_info("sddekit gateway initialized.");
	}
	ncalls++;

	if (nrhs < 2 || !mxIsChar(prhs[0]) || !mxIsChar(prhs[1]))
		sd_err("gateway requires at least two string arguments.");

	mxGetString(prhs[0], obj, 256);
	mxGetString(prhs[1], meth, 256);

	if ((p = sd_mex_lut(obj, meth))==NULL)
		sd_err("unknown obj or meth name combination.");

	(*p)(nlhs, plhs, nrhs - 2, prhs + 2);
}
