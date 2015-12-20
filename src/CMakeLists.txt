add_definitions(-DSKDEBUG)
if(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -fstrict-aliasing -Wstrict-aliasing -ansi")
endif()

set(libsk_srcs randomkit.c sk_dat.c sk_hist.c sk_net.c sk_out.c
	sk_scheme.c sk_solv.c sk_sparse.c sk_sys.c sk_sys_wc.c
	sk_util.c sk_malloc.c)
add_library(sk ${libsk_srcs})

if (UNIX)
	target_link_libraries(sk m)
endif(UNIX)
