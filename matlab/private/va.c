/* variadic mexCallMATLAB handling simple marshalling tasks */

#include <stdarg.h>
#include <string.h>
#include "mex.h"

/* convert & pack C args into mxArrays */
void mexMarshalIn(char *fmt, mxArray **mxs, ...)
{
	int i, narg = strlen(fmt);
	va_list ap;
	va_start(ap, narg);
	for (i=0; i<narg; i++)
	switch (fmt[i]) 
	{
		case 'a':
			mxs[i] = mxCreateString(va_arg(ap, char*));
			continue;
		case 'd':
			mxs[i] = mxCreateDoubleScalar(va_arg(ap, double));
			continue;
		case 'D':
			mxs[i] = mxCreateDoubleMatrix(0, 1, mxREAL);
			mxSetM(mxs[i], va_arg(ap, size_t));
			mxSetPr(mxs[i], va_arg(ap, double*));
	}
	va_end(ap);
}

/* unpack & convert mxArray from mxArrays to C args */
void mexMarshalOut(char *fmt, mxArray **mx, ...)
{
}

void mexCallMATLABva(char *args, ...)
{
	/* args should look like "(abcd)efg" where each letter specifies
	 * conversion to apply to argument and parens enclose input / rhs
	 * arguments.
	 *
	 * a - NULL terminated C string (char* in, char **out)
	 * d - scalar double (double in, double *out)
	 */

	char *a = args;
	int argin = 1;
	mxArray **arg;

	while (*a != '\0') { switch (*a) {
		case '(':
			continue;
		case ')':
			argin = 0;
			continue;
		case 'd':
			if (argin)
				*arg = mxCreateDoubleScalar(va_arg());
			else
				va_arg() = mxGetScalar(*arg);
			continue;
	}
}
