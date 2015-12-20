/* Apache 2.0 INS-AMU 2015 */

#include "matrix.h"
#include "mex.h"

#include "sddekit.h"

static int init = 0;

void do_solv(char *msg, int nrhs, const mxArray *prhs[]) {

}
void do_hist(char *msg, int nrhs, const mxArray *prhs[]) {

}
void do_sys(char *msg, int nrhs, const mxArray *prhs[]) {

}
void do_sys_exc(char *msg, int nrhs, const mxArray *prhs[]) {

}
void do_sys_wc(char *msg, int nrhs, const mxArray *prhs[]) {

}
void do_sch(char *msg, int nrhs, const mxArray *prhs[]) {

}
void do_sch_em(char *msg, int nrhs, const mxArray *prhs[]) {

}
void do_sch_emcolor(char *msg, int nrhs, const mxArray *prhs[]) {

}
void do_sch_heun(char *msg, int nrhs, const mxArray *prhs[]) {

}
void do_net(char *msg, int nrhs, const mxArray *prhs[]) {

}

void mexFunction(int nlhs, mxArray *plhs[], int nlhs, const mxArray *prhs[]) {
	char type[255], msg[255];

	if (!init) {
		sk_malloc_set_allocators(&mxMalloc, &mxRealloc, &mxFree);
	}

	mxGetString(prhs[0], type, 255);
	mxGetString(prhs[1], msg, 255);

	/* check for two arguments to identify types, then pass args along */
	if (!strcmp("solv", type)) {
		do_solv(msg, nrhs, prhs+2);
	} else if (!strcmp("hist", type)) {
		do_hist(msg, nrhs, prhs+2);
	} else if (!strcmp("sys", type)) {
		do_sys(msg, nrhs, prhs+2);
	} else if (!strcmp("sys_exc", type)) {
		do_sys_exc(msg, nrhs, prhs+2);
	} else if (!strcmp("sys_wc", type)) {
		do_sys_wc(msg, nrhs, prhs+2);
	} else if (!strcmp("sch", type)) {
		do_sch(msg, nrhs, prhs+2);
	} else if (!strcmp("sch_em", type)) {
		do_sch_em(msg, nrhs, prhs+2);
	} else if (!strcmp("sch_emcolor", type)) {
		do_sch_emcolor(msg, nrhs, prhs+2);
	} else if (!strcmp("sch_heun", type)) {
		do_sch_heun(msg, nrhs, prhs+2);
	} else if (!strcmp("net", type)) {
		do_net(msg, nrhs, prhs+2);
	}
