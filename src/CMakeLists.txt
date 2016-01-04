add_definitions(-DSDDEBUG)
if(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -fstrict-aliasing -Wstrict-aliasing -ansi")
endif()

set(libsd_srcs randomkit.c sd_dat.c sd_hist.c sd_net.c sd_out.c
	sd_scheme.c sd_solv.c sd_sparse.c sd_sys.c sd_sys_wc.c
	sd_util.c sd_malloc.c sd_test.c)
add_library(sk ${libsd_srcs})

if (UNIX)
	target_link_libraries(sk m)
endif(UNIX)
