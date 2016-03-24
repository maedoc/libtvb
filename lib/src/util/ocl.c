#include "sddekit.h"

 /*
 * Returns the error string associated with a given OpenCL error code.
 */
const char * ocl_err_code (cl_int err_in)
{
    switch (err_in) {
    case CL_SUCCESS:                          return "Success";
    case CL_DEVICE_NOT_FOUND:                 return "Device not found";
    case CL_DEVICE_NOT_AVAILABLE:             return "Device not available";
    case CL_COMPILER_NOT_AVAILABLE:           return "Compiler not available";
    case CL_MEM_OBJECT_ALLOCATION_FAILURE:    return "Memory object "
                                                     "allocation failure";
    case CL_OUT_OF_RESOURCES:                 return "Out of resources";
    case CL_OUT_OF_HOST_MEMORY:               return "Out of host memory";
    case CL_PROFILING_INFO_NOT_AVAILABLE:     return "Profiling information "
                                                     "not available";
    case CL_MEM_COPY_OVERLAP:                 return "Memory copy overlap";
    case CL_IMAGE_FORMAT_MISMATCH:            return "Image format mismatch";
    case CL_IMAGE_FORMAT_NOT_SUPPORTED:       return "Image format not "
                                                     "supported";
    case CL_BUILD_PROGRAM_FAILURE:            return "Program build failure";
    case CL_MAP_FAILURE:                      return "Map failure";
    case CL_INVALID_VALUE:                    return "Invalid value";
    case CL_INVALID_DEVICE_TYPE:              return "Invalid device type";
    case CL_INVALID_PLATFORM:                 return "Invalid platform";
    case CL_INVALID_DEVICE:                   return "Invalid device";
    case CL_INVALID_CONTEXT:                  return "Invalid context";
    case CL_INVALID_QUEUE_PROPERTIES:         return "Invalid queue properties";
    case CL_INVALID_COMMAND_QUEUE:            return "Invalid command queue";
    case CL_INVALID_HOST_PTR:                 return "Invalid host pointer";
    case CL_INVALID_MEM_OBJECT:               return "Invalid memory object";
    case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:  return "Invalid image format "
                                                     "descriptor";
    case CL_INVALID_IMAGE_SIZE:               return "Invalid image size";
    case CL_INVALID_SAMPLER:                  return "Invalid sampler";
    case CL_INVALID_BINARY:                   return "Invalid binary";
    case CL_INVALID_BUILD_OPTIONS:            return "Invalid build options";
    case CL_INVALID_PROGRAM:                  return "Invalid program";
    case CL_INVALID_PROGRAM_EXECUTABLE:       return "Invalid program "
                                                     "executable";
    case CL_INVALID_KERNEL_NAME:              return "Invalid kernel name";
    case CL_INVALID_KERNEL_DEFINITION:        return "Invalid kernel "
                                                     "definition";
    case CL_INVALID_KERNEL:                   return "Invalid kernel";
    case CL_INVALID_ARG_INDEX:                return "Invalid argument index";
    case CL_INVALID_ARG_VALUE:                return "Invalid argument value";
    case CL_INVALID_ARG_SIZE:                 return "Invalid argument size";
    case CL_INVALID_KERNEL_ARGS:              return "Invalid kernel arguments";
    case CL_INVALID_WORK_DIMENSION:           return "Invalid work dimension";
    case CL_INVALID_WORK_GROUP_SIZE:          return "Invalid work group size";
    case CL_INVALID_WORK_ITEM_SIZE:           return "Invalid work item size";
    case CL_INVALID_GLOBAL_OFFSET:            return "Invalid global offset";
    case CL_INVALID_EVENT_WAIT_LIST:          return "Invalid event wait list";
    case CL_INVALID_EVENT:                    return "Invalid event";
    case CL_INVALID_OPERATION:                return "Invalid operation";
    case CL_INVALID_GL_OBJECT:                return "Invalid OpenGL object";
    case CL_INVALID_BUFFER_SIZE:              return "Invalid buffer size";
    case CL_INVALID_MIP_LEVEL:                return "Invalid mip-map level";
    default:                                  return "Unknown error code";
    }
}

/*
 * Create a context containing a single device. Also return a queue for this
 * device. If prof is true then profiling will be enabled for the queue.
 */
void ocl_get_device_context(cl_uint pid, cl_uint did, cl_context *context,
    cl_command_queue *queue, int prof)
{
    cl_uint num_platforms, num_devices;
    cl_int err = 0;

    //Get list of platforms
    OCL_CHECK_ERROR( clGetPlatformIDs(0, NULL, &num_platforms) );
    cl_platform_id *platforms = sd_malloc(num_platforms * sizeof(*platforms));
    OCL_CHECK_ERROR( clGetPlatformIDs(num_platforms, platforms, NULL) );

    //Get devices
    OCL_CHECK_ERROR( clGetDeviceIDs(platforms[pid], CL_DEVICE_TYPE_ALL,
        0, NULL, &num_devices) );
    cl_device_id *devices = sd_malloc(num_devices * sizeof(*devices));
    OCL_CHECK_ERROR( clGetDeviceIDs(platforms[pid], CL_DEVICE_TYPE_ALL,
        num_devices, devices, NULL) );

    //Create context
    const cl_context_properties cprops[] = {CL_CONTEXT_PLATFORM,
        (cl_context_properties)platforms[pid], 0};
    *context = clCreateContext(cprops, 1, &devices[did], NULL, NULL, &err);
    OCL_CHECK_ERROR( err );

    *queue = clCreateCommandQueue(*context, devices[did],
        prof ? CL_QUEUE_PROFILING_ENABLE : 0, &err);
    OCL_CHECK_ERROR( err );

    free(platforms);
    free(devices);
}

/*
 * Build OpenCL kernel in file with name fname using bopt as build options.
 * Also print build logs if verbosity > 0.
 */
void ocl_compile_kernel(const char *fname, const char *bopt,
    const cl_context context, cl_program *program, int verbosity)
{
    FILE *fsrc;
    char *ssrc;
    long int fsize;
    cl_int err;

    //Open file for binary reading first to find the length
    if((fsrc = fopen(fname, "rb")) == NULL){
        fprintf(stderr, "Could not open OpenCL source file \"%s\""
            "for reading. Exiting.\n", fname);
        exit(EXIT_FAILURE);
    }

    if(fseek(fsrc, 0, SEEK_END)){
        fprintf(stderr, "Error finding end if file in function \"%s\". "
            "Exiting.\n", __func__);
        exit(EXIT_FAILURE);
    }

    fsize = ftell(fsrc);
    
    fclose(fsrc);

    ssrc = sd_malloc((fsize + 1) * sizeof(*ssrc));

    //Open again for reading in text mode, now that we know the size
    if((fsrc = fopen(fname, "r")) == NULL){
        fprintf(stderr, "Could not open OpenCL source file %s "
            "for reading. Exiting.\n", fname);
        exit(EXIT_FAILURE);
    }
    
    size_t numread = fread(ssrc, sizeof(*ssrc), fsize, fsrc);
    ssrc[numread] = '\0';

    fclose(fsrc);

    //Get device list
    cl_uint num_devices;
    #ifdef CL_CONTEXT_NUM_DEVICES
    OCL_CHECK_ERROR( clGetContextInfo(context, CL_CONTEXT_NUM_DEVICES,
        sizeof(num_devices), &num_devices, NULL) );
    #else
    num_devices = 1;
    #endif
    cl_device_id *devices = sd_malloc(num_devices * sizeof(*devices));
    OCL_CHECK_ERROR( clGetContextInfo(context, CL_CONTEXT_DEVICES,
        num_devices * sizeof(*devices), devices, NULL) );

    *program = clCreateProgramWithSource(context, 1,
        (const char **)&ssrc, NULL, &err);
    OCL_CHECK_ERROR( err );

    err = clBuildProgram(*program, num_devices, devices, bopt, NULL, NULL);

    //Print build logs
    if(verbosity > 0 || err != CL_SUCCESS){
        for(cl_uint i = 0; i < num_devices; i++){
            size_t blsize;
            OCL_CHECK_ERROR( clGetProgramBuildInfo(*program, devices[i],
                CL_PROGRAM_BUILD_LOG, 0, NULL, &blsize) );
            char *blog = sd_malloc(blsize * sizeof(*blog));
            OCL_CHECK_ERROR( clGetProgramBuildInfo(*program, devices[i],
                CL_PROGRAM_BUILD_LOG, blsize, blog, NULL) );
            printf("\nBuild log for device %lu:\n\n%s\n",
                (unsigned long)i, blog);
            free(blog);
        }
    }

    OCL_CHECK_ERROR( err );

    free(ssrc);
    free(devices);
}

/*
 * Prints a list of platforms and associated devices, the amount of
 * information being controlled bu verbosity from 0 (nothing) to 2 (a lot).
 */
void ocl_print_platforms(cl_int verbosity)
{
    cl_uint num_platforms;
    cl_platform_id *platforms;
    int pad = 35;

    char lstr[16384];

    //Get the list of platform IDs
    OCL_CHECK_ERROR( clGetPlatformIDs(0, NULL, &num_platforms) );
    platforms = sd_malloc(num_platforms * sizeof(*platforms));
    OCL_CHECK_ERROR( clGetPlatformIDs(num_platforms, platforms, NULL));

    //Nothing more to do for verbosity 0.
    if(verbosity < 1) return;

    //Print info about platforms
    cl_uint pid;
    for(pid = 0; pid < num_platforms; pid++){
        char profile[128], version[128], name[128], vendor[128];

        //Get the desired information
        OCL_CHECK_ERROR( clGetPlatformInfo(platforms[pid], CL_PLATFORM_PROFILE,
            sizeof(profile), profile, NULL) );
        OCL_CHECK_ERROR( clGetPlatformInfo(platforms[pid], CL_PLATFORM_VERSION,
            sizeof(version), version, NULL) );
        OCL_CHECK_ERROR( clGetPlatformInfo(platforms[pid], CL_PLATFORM_NAME,
            sizeof(name), name, NULL) );
        OCL_CHECK_ERROR( clGetPlatformInfo(platforms[pid], CL_PLATFORM_VENDOR,
            sizeof(vendor), vendor, NULL) );
        OCL_CHECK_ERROR( clGetPlatformInfo(platforms[pid], CL_PLATFORM_EXTENSIONS,
            sizeof(lstr), lstr, NULL) );

        if(verbosity == 1)
            printf("Platform %lu (%s):\n", (unsigned long)pid, name);

        if(verbosity > 1){
            printf("Platform %lu:\n"
                "\t%*s %s\n"
                "\t%*s %s\n"
                "\t%*s %s\n"
                "\t%*s %s\n", (unsigned long)pid,
                -pad, "Name:", name,
                -pad, "Vendor:", vendor,
                -pad, "Version:", version,
                -pad, "Profile:", profile);
            
            const char s2 = ' ';
            printf("\t%*s ", -pad, "Platform Extensions:");
            char *token = strtok(lstr, &s2);
            if(token != NULL) printf("%s\n", token);
            token = strtok(NULL, &s2);
            while(token != NULL){
                printf("\t%*s %s\n", -pad, "", token);
                token = strtok(NULL, &s2);
            }
        }

        //Get device IDs for this platform
        cl_uint num_devices;
        OCL_CHECK_ERROR( clGetDeviceIDs(platforms[pid], CL_DEVICE_TYPE_ALL, 0,
            NULL, &num_devices) );
        cl_device_id *dvcs = sd_malloc(num_devices * sizeof(*dvcs));
        OCL_CHECK_ERROR( clGetDeviceIDs(platforms[pid], CL_DEVICE_TYPE_ALL,
            num_devices, dvcs, NULL) );

        cl_uint did;
        for(did = 0; did < num_devices; did++){
            cl_device_type dtype;
            cl_uint cluint;
            size_t  sizet;
            cl_ulong clulong;
            cl_bool clbool;
            cl_device_fp_config fpconf;
            cl_device_mem_cache_type cachetype;
            cl_device_local_mem_type lmemtype;
            cl_device_exec_capabilities execcap;
            cl_command_queue_properties cqprops;

            OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did], CL_DEVICE_NAME,
                sizeof(lstr), lstr, NULL) );
            if(verbosity == 1){
                printf("\tDevice %lu: %s\n", (unsigned long)did, lstr);
                continue; //That's it for verbosity == 1
            }
            
            printf("\n\tDevice %lu in platform %lu:\n", (unsigned long)did,
                (unsigned long)pid);

            OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did], CL_DEVICE_TYPE,
                sizeof(dtype), &dtype, NULL) );
            printf("\t\t%*s ", -pad, "CL_DEVICE_TYPE:");
            if(dtype & CL_DEVICE_TYPE_CPU)
                printf("CL_DEVICE_TYPE_CPU ");
            if(dtype & CL_DEVICE_TYPE_GPU)
                printf("CL_DEVICE_TYPE_GPU ");
            if(dtype & CL_DEVICE_TYPE_ACCELERATOR) 
                printf("CL_DEVICE_TYPE_ACCELERATOR ");
            if(dtype & CL_DEVICE_TYPE_DEFAULT)
                printf("CL_DEVICE_TYPE_DEFAULT ");
            if(verbosity > 1)
                printf("\n");

            printf("\t\t%*s %s\n", -pad, "CL_DEVICE_NAME:", lstr);
            
            OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did], CL_DEVICE_VENDOR,
                sizeof(lstr), lstr, NULL) );
            printf("\t\t%*s %s\n", -pad, "CL_DEVICE_VENDOR:", lstr);

            if(verbosity > 1){

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did], CL_DRIVER_VERSION,
                    sizeof(lstr), lstr, NULL) );
                printf("\t\t%*s %s\n", -pad, "CL_DRIVER_VERSION:", lstr);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did], CL_DEVICE_PROFILE,
                    sizeof(lstr), lstr, NULL) );
                printf("\t\t%*s %s\n", -pad, "PROFILE:", lstr);
                
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did], CL_DEVICE_VERSION,
                    sizeof(lstr), lstr, NULL) );
                printf("\t\t%*s %s\n", -pad, "VERSION:", lstr);

                #ifdef CL_DEVICE_OPENCL_C_VERSION
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did], CL_DEVICE_OPENCL_C_VERSION,
                    sizeof(lstr), lstr, NULL) );
                printf("\t\t%*s %s\n", -pad, "OPENCL_C_VERSION:", lstr);
                #endif

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did], CL_DEVICE_VENDOR_ID,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu\n", -pad, "VENDOR_ID:",
                    (unsigned long)cluint);
    
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MAX_COMPUTE_UNITS,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu\n", -pad, "MAX_COMPUTE_UNITS:",
                    (unsigned long)cluint);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu\n", -pad, "MAX_WORK_ITEM_DIMENSIONS:",
                    (unsigned long)cluint);

                size_t *wisizes = sd_malloc(cluint * sizeof(*wisizes));
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MAX_WORK_ITEM_SIZES, cluint * sizeof(*wisizes),
                    wisizes, NULL) );
                printf("\t\t%*s (", -pad, "MAX_WORK_ITEM_SIZES:");
                cl_uint i;
                for(i = 0; i < cluint; i++)
                    printf(" %zu ", wisizes[i]);
                printf(")\n");
                free(wisizes);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MAX_WORK_GROUP_SIZE,
                    sizeof(sizet), &sizet, NULL) );
                printf("\t\t%*s %zu\n", -pad, "MAX_WORK_GROUP_SIZE:", sizet);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu\n", -pad, "PREFERRED_VECTOR_WIDTH_FLOAT:",
                    (unsigned long)cluint);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu\n", -pad, "PREFERRED_VECTOR_WIDTH_DOUBLE:",
                    (unsigned long)cluint);

                #ifdef CL_DEVIC_NATIVE_VECTOR_WIDTH_FLOAT
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu\n", -pad, "NATIVE_VECTOR_WIDTH_FLOAT:",
                    (unsigned long)cluint);
                #endif

                #ifdef CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu\n", -pad, "NATIVE_VECTOR_WIDTH_DOUBLE:",
                    (unsigned long)cluint);
                #endif

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MAX_CLOCK_FREQUENCY,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu MHz\n", -pad, "MAX_CLOCK_FREQUENCY:",
                    (unsigned long)cluint);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did], CL_DEVICE_IMAGE_SUPPORT,
                    sizeof(clbool), &clbool, NULL) );
                printf("\t\t%*s %s\n", -pad, "IMAGE_SUPPORT:",
                    (clbool == CL_TRUE) ? "CL_TRUE" : "CL_FALSE");

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MAX_READ_IMAGE_ARGS,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu\n", -pad, "MAX_READ_IMAGE_ARGS:",
                    (unsigned long)cluint);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MAX_WRITE_IMAGE_ARGS,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu\n", -pad, "MAX_WRITE_IMAGE_ARGS:",
                    (unsigned long)cluint);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_IMAGE2D_MAX_WIDTH,
                    sizeof(sizet), &sizet, NULL) );
                printf("\t\t%*s %zu\n", -pad, "IMAGE2D_MAX_WIDTH:", sizet);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                    sizeof(sizet), &sizet, NULL) );
                printf("\t\t%*s %zu\n", -pad, "IMAGE2D_MAX_HEIGHT:", sizet);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_IMAGE3D_MAX_WIDTH,
                    sizeof(sizet), &sizet, NULL) );
                printf("\t\t%*s %zu\n", -pad, "IMAGE3D_MAX_WIDTH:", sizet);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_IMAGE3D_MAX_HEIGHT,
                    sizeof(sizet), &sizet, NULL) );
                printf("\t\t%*s %zu\n", -pad, "IMAGE3D_MAX_HEIGHT:", sizet);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_IMAGE3D_MAX_DEPTH,
                    sizeof(sizet), &sizet, NULL) );
                printf("\t\t%*s %zu\n", -pad, "IMAGE3D_MAX_DEPTH:", sizet);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MAX_SAMPLERS, sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu\n", -pad, "MAX_SAMPLERS:",
                    (unsigned long)cluint);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MAX_PARAMETER_SIZE,
                    sizeof(sizet), &sizet, NULL) );
                printf("\t\t%*s %zu B (%.1f KiB)\n", -pad,
                    "MAX_PARAMETER_SIZE:", sizet, sizet / (double)(1 << 10));

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MEM_BASE_ADDR_ALIGN,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu b\n", -pad, "MEM_BASE_ADDR_ALIGN:",
                    (unsigned long)cluint);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu B\n", -pad, "MIN_DATA_TYPE_ALIGN_SIZE:",
                    (unsigned long)cluint);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_SINGLE_FP_CONFIG,
                    sizeof(fpconf), &fpconf, NULL) );
                printf("\t\t%*s ", -pad, "SINGLE_FP_CONFIG:");
                if(fpconf & CL_FP_DENORM) printf("DENORM ");
                if(fpconf & CL_FP_INF_NAN) printf("INF_NAN ");
                if(fpconf & CL_FP_ROUND_TO_NEAREST) printf("ROUND_TO_NEAREST ");
                if(fpconf & CL_FP_ROUND_TO_ZERO) printf("ROUND_TO_ZERO ");
                if(fpconf & CL_FP_ROUND_TO_INF) printf("ROUND_TO_INF ");
                if(fpconf & CL_FP_FMA) printf("FMA ");
                #ifdef CL_FP_SOFT_FLOAT
                if(fpconf & CL_FP_SOFT_FLOAT) printf("SOFT_FLOAT ");
                #endif
                printf("\n");
                
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,
                    sizeof(cachetype), &cachetype, NULL) );
                printf("\t\t%*s ", -pad, "GLOBAL_MEM_CACHE_TYPE:");
                if(cachetype == CL_NONE)
                    printf("CL_NONE\n");
                if(cachetype == CL_READ_ONLY_CACHE)
                    printf("CL_READ_ONLY_CACHE\n");
                if(cachetype == CL_READ_WRITE_CACHE)
                    printf("CL_READ_WRITE_CACHE\n");
    
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu B\n", -pad, "GLOBAL_MEM_CACHELINE_SIZE:",
                    (unsigned long)cluint);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,
                    sizeof(clulong), &clulong, NULL) );
                printf("\t\t%*s %llu B (%.1f KiB)\n", -pad,
                    "GLOBAL_MEM_CACHE_SIZE:",
                    (unsigned long long)clulong,  clulong / (double)(1 << 10));

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_ADDRESS_BITS, sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu\n", -pad, "ADDRESS_BITS:",
                    (unsigned long)cluint);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_GLOBAL_MEM_SIZE,
                    sizeof(clulong), &clulong, NULL) );
                printf("\t\t%*s %llu B (%.1f GiB)\n", -pad, "GLOBAL_MEM_SIZE:",
                    (unsigned long long)clulong,  clulong / (double)(1 << 30));

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MAX_MEM_ALLOC_SIZE,
                    sizeof(clulong), &clulong, NULL) );
                printf("\t\t%*s %llu B (%.1f GiB)\n", -pad,
                    "MAX_MEM_ALLOC_SIZE:",
                    (unsigned long long)clulong,  clulong / (double)(1 << 30));

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_LOCAL_MEM_TYPE,
                    sizeof(lmemtype), &lmemtype, NULL) );
                printf("\t\t%*s ", -pad, "LOCAL_MEM_TYPE:");
                if(lmemtype == CL_LOCAL) printf("CL_LOCAL\n");
                if(lmemtype == CL_GLOBAL) printf("CL_GLOBAL\n");

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_LOCAL_MEM_SIZE,
                    sizeof(clulong), &clulong, NULL) );
                printf("\t\t%*s %llu B (%.1f KiB)\n", -pad, "LOCAL_MEM_SIZE:",
                    (unsigned long long)clulong,  clulong / (double)(1 << 10));

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_ERROR_CORRECTION_SUPPORT,
                    sizeof(clbool), &clbool, NULL) );
                printf("\t\t%*s %s\n", -pad, "ERROR_CORRECTION_SUPPORT:",
                    (clbool == CL_TRUE) ? "CL_TRUE" : "CL_FALSE");

                #ifdef CL_DEVICE_HOST_UNIFIED_MEMORY
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_HOST_UNIFIED_MEMORY,
                    sizeof(clbool), &clbool, NULL) );
                printf("\t\t%*s %s\n", -pad, "HOST_UNIFIED_MEMORY:",
                    (clbool == CL_TRUE) ? "CL_TRUE" : "CL_FALSE");
                #endif
    
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_ENDIAN_LITTLE, sizeof(clbool), &clbool, NULL) );
                printf("\t\t%*s %s\n", -pad, "ENDIAN_LITTLE:",
                    (clbool == CL_TRUE) ? "CL_TRUE" : "CL_FALSE");
    
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_AVAILABLE, sizeof(clbool), &clbool, NULL) );
                printf("\t\t%*s %s\n", -pad, "AVAILABLE:",
                    (clbool == CL_TRUE) ? "CL_TRUE" : "CL_FALSE");
    
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_COMPILER_AVAILABLE,
                    sizeof(clbool), &clbool, NULL) );
                printf("\t\t%*s %s\n", -pad, "COMPILER_AVAILABLE:",
                    (clbool == CL_TRUE) ? "CL_TRUE" : "CL_FALSE");
    
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
                    sizeof(clulong), &clulong, NULL) );
                printf("\t\t%*s %llu B (%.1f KiB)\n", -pad,
                    "MAX_CONSTANT_BUFFER_SIZE:",
                    (unsigned long long)clulong,  clulong / (double)(1 << 10));

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_MAX_CONSTANT_ARGS,
                    sizeof(cluint), &cluint, NULL) );
                printf("\t\t%*s %lu\n", -pad, "MAX_CONSTANT_ARGS:",
                    (unsigned long)cluint);
    
                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_PROFILING_TIMER_RESOLUTION,
                    sizeof(sizet), &sizet, NULL) );
                printf("\t\t%*s %zu ns\n", -pad,
                    "PROFILING_TIMER_RESOLUTION:", sizet);

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_EXECUTION_CAPABILITIES,
                    sizeof(execcap), &execcap, NULL) );
                printf("\t\t%*s ", -pad, "EXECUTION_CAPABILITIES:");
                if(execcap == CL_EXEC_KERNEL)
                    printf("CL_EXEC_KERNEL ");
                if(execcap == CL_EXEC_NATIVE_KERNEL)
                    printf("CL_EXEC_NATIVE_KERNEL ");
                printf("\n");

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_QUEUE_PROPERTIES,
                    sizeof(cqprops), &cqprops, NULL) );
                printf("\t\t%*s ", -pad, "CL_DEVICE_QUEUE_PROPERTIES:");
                if(cqprops & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE)
                    printf("CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE ");
                if(cqprops & CL_QUEUE_PROFILING_ENABLE)
                    printf("CL_QUEUE_PROFILING_ENABLE");
                printf("\n");

                OCL_CHECK_ERROR( clGetDeviceInfo(dvcs[did],
                    CL_DEVICE_EXTENSIONS, sizeof(lstr), lstr, NULL) );
                printf("\t\t%*s ", -pad, "Device Extensions:");
                {
                    const char s2 = ' ';
                    char *token = strtok(lstr, &s2);
                    if(token != NULL) printf("%s\n", token);
                    token = strtok(NULL, &s2);
                    while(token != NULL){
                        printf("\t\t%*s %s\n", -pad, "", token);
                        token = strtok(NULL, &s2);
                    }
                    printf("\n");
                }
            }
        }

        free(dvcs);
    }

    free(platforms);
}
