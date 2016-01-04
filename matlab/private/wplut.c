/* copyright 2016 Apache 2 sddekit authors */

#include <string.h>

#include "wplut.h"

/* generate functions */
#include "wps.c"

/* generate function lut */
static struct { char *o, *m; wp p; } lut[] = {
#define _(obj, meth, ...) {.o=#obj, .m=#meth, \
    .p=&sd_mex_wrap_ ## obj ## _ ## meth},
#include "wps.c"
	{.o=NULL, .m=NULL, .p=NULL}
};
#undef _

#undef fn

wp sd_mex_lut(char *obj, char *meth)
{
	int i=0;
	while (lut[i].o != NULL)
	{
		if (!(strcmp(lut[i].o, obj) || strcmp(lut[i].m, meth)))
			return lut[i].p;
        i++;
	}
	return NULL;
}
