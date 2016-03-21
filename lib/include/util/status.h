/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

/*! Status codes returned by various functions. */
enum sd_stat
{
	/*! Function call succeeded */
	SD_OK,
    
	/*! An error occurred during the function call or one of the functions it called. */
	SD_ERR,
    
	/*! Returned by output object to indicate solver should continue */
	SD_CONT,
    
	/*! Returned by output object to indicate solver should stop */
	SD_STOP,
    
	/*! Returned by function it doesn't know */
	SD_UNKNOWN,
    
	/*! Returned to indicate zero value in sparse matrix */
	SD_ZERO,
    
	/*! Returned to indicate non zero value in sparse matrix */
	SD_NON_ZERO,
    
	/*! Returned to indicate an out-of-bounds condition */
	SD_OUT_OF_BOUNDS
    
};