/* function to replace macro according to issue at- 
https://github.com/maedoc/sddekit/issues/88
This function generates a string and passes on the same to the appropriate logger.*/

/* add include for logger function */
#include "sddekit.h"

#define SIZE 256 // change this appropriately

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
	
	logger(msg);
}
