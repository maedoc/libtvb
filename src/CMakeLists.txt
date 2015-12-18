set(libsk_srcs randomkit.c sk_dat.c sk_hist.c sk_net.c sk_out.c
	sk_scheme.c sk_solv.c sk_sparse.c sk_sys.c sk_sys_wc.c sk_test.c
	sk_util.c)

add_library(libsk ${libsk_srcs})
target_link_libraries(libsk m)
