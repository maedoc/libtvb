#pragma once
#ifndef IUNOCL_H_INCLUDED
#define IUNOCL_H_INCLUDED

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define IUNCLERR(input)\
	{\
		cl_int IUNCLERR_ERR = (input);\
		if(IUNCLERR_ERR  != CL_SUCCESS){\
			fprintf(stderr, "OpenCL ERROR(%d) in %s(%d): %s\n",\
				IUNCLERR_ERR, __FILE__, __LINE__,\
				iunclGetErrstring(IUNCLERR_ERR));\
			exit(EXIT_FAILURE);\
		}\
	}\

const char * iunclGetErrstring(cl_int);

void iunclPrintPlatforms(cl_int);

void iunclGetSingleDeviceContext(cl_uint, cl_uint, cl_context *,
	cl_command_queue *, int);

void iunclCompileKernel(const char *, const char *, const cl_context,
	cl_program *,  int);

#endif //IUNOCL_H_INCLUDED
