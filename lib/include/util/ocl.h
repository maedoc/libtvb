/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

#pragma once
#ifndef OCL_H_INCLUDED
#define OCL_H_INCLUDED

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define OCL_CHECK_ERROR(E)\
    {\
        cl_int err = (E);\
        if(err  != CL_SUCCESS){\
            sd_err( "OpenCL ERROR(%d): %s\n", err, ocl_err_code(err));\
            exit(EXIT_FAILURE);\
        }\
    }\

/*
 * Returns the error string associated with a given OpenCL error code.
 */
const char * ocl_err_code(cl_int);

/*
 * Create a context containing a single device. Also return a queue for this
 * device. If prof is true then profiling will be enabled for the queue.
 */
void ocl_get_device_context(cl_uint, cl_uint, cl_context *,
	cl_command_queue *, int);

/*
 * Build OpenCL kernel in file with name fname using bopt as build options.
 * Also print build logs if verbosity > 0.
 */
void ocl_compile_kernel(const char *, const char *, const cl_context,
	cl_program *,  int);

/*
 * Prints a list of platforms and associated devices, the amount of
 * information being controlled bu verbosity from 0 (nothing) to 2 (a lot).
 */
void ocl_print_platform(cl_int);

#endif //OCL_H_INCLUDED
