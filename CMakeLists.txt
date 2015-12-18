cmake_minimum_required(VERSION 2.6)
project(sddekit)

message("project src dir is ${CMAKE_SOURCE_DIR}")

include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory(src)
add_subdirectory(bench)
add_subdirectory(test)
#add_subdirectory(cython)
#add_subdirectory(mex)
#add_subdirectory(jni)
