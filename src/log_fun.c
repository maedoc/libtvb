/**
 * This function generates a string and passes on the same to
 * the appropriate logger. 
 * Once completed, it is expected to replace the existing macros.
 * It needs to be extended further and needs to support error handlers as well.
*/

#include "sddekit.h"

#include <stdarg.h>

#define SIZE 256 // change this as required

int logmsg(char *format, ...)
{
	char msg[256];
	
	va_list args;
	va_start(args, format);
	
	if (vsnprintf(msg, SIZE, format, args) < 0)
	{
		//error
	}

	va_end(args);
	
	/*logger(msg);
	invoke logger after changing in src/sddekit.h
	msg is the only argument that should be passed*/
}

