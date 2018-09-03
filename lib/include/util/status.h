/* copyright 2016 Apache 2 libtvb authors */


#include "../libtvb.h"

/*! Status codes returned by various functions. */
enum tvb_stat
{
	/*! Function call succeeded */
	TVB_OK,
    
	/*! An error occurred during the function call or one of the functions it called. */
	TVB_ERR,
    
	/*! Returned by output object to indicate solver should continue */
	TVB_CONT,
    
	/*! Returned by output object to indicate solver should stop */
	TVB_STOP,
    
	/*! Returned by function it doesn't know */
	TVB_UNKNOWN,
    
	/*! Returned to indicate zero value in sparse matrix */
	TVB_ZERO,
    
	/*! Returned to indicate non zero value in sparse matrix */
	TVB_NON_ZERO,
    
	/*! Returned to indicate an out-of-bounds condition */
	TVB_OUT_OF_BOUNDS
    
};
