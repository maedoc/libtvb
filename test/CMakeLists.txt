add_custom_command(OUTPUT test_all.c
	COMMAND python "${CMAKE_CURRENT_LIST_DIR}/test_all.c.py" --to-cwd)

add_library(sk_tests test_dat.c test_exc.c test_hist.c test_net.c
	test_out.c test_solv.c test_sparse.c test_util.c 
	test_all.c)

add_executable(sk_test "test_main.c")
target_link_libraries(sk_test sk_tests m sk)

add_test(test_all sk_test)
