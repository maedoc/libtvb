add_custom_command(OUTPUT test_all.c
	COMMAND python "${CMAKE_CURRENT_LIST_DIR}/test_all.c.py" --to-cwd)

add_library(sd_tests test_dat.c test_exc.c test_hist.c test_net.c
	test_out.c test_solv.c test_sparse.c test_util.c 
	test_all.c)

add_executable(sd_test "test_main.c")
target_link_libraries(sd_test sd_tests m sk)

add_test(test_all sd_test)
