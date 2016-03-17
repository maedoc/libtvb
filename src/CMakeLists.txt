# copyright 2016 Apache 2 sddekit authors

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "-std=c99 ${CMAKE_C_FLAGS}")
endif()

add_library(SDDEKit
# find src -name '*.c*' | cut -c5-
    conn/conn.c
    conn/cfun.cpp
    util/malloc.c
    util/util.c
    util/log.c
    util/ver.c
    util/sparse.c
    rng.c
    out/conv_kern.c
    out/linop.c
    out/ign.c
    out/until.c
    out/conv.c
    out/fork.c
    out/cb.c
    out/mem.c
    sys/gen2d.c
    sys/wc.c
    sys/hmje.c
    sys/cb.c
    sys/net.c
    sys/rww.c
    sys/mean.c
    sch/heun.c
    sch/one_step.c
    sch/emc.c
    sch/cb.c
    history.c
    extern/randomkit.c
    solv.c
)

if (UNIX)
	target_link_libraries(SDDEKit m)
endif(UNIX)