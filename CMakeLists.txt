cmake_minimum_required(VERSION 2.6)
project(sddekit)

# build time config
set(sk_ver_major 0)
set(sk_ver_minor 0)
set(sk_res_dir ${PROJECT_SOURCE_DIR})
configure_file(${CMAKE_SOURCE_DIR}/include/sk_config.h.in ${PROJECT_BINARY_DIR}/sk_config.h)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR})
message("done configuring!")

if(gprof)
	message("compiling for profiling")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
endif()

add_subdirectory(src)
add_subdirectory(bench)
add_subdirectory(test)
#add_subdirectory(cython)
#add_subdirectory(mex)
#add_subdirectory(jni)
