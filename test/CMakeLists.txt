enable_testing()

set(tests dat exc hist net out solv sparse util)

foreach(testnm ${tests})
	set(test test_${testnm})
	add_executable(${test} ${test}.c)
	target_link_libraries(${test} libsk)
	add_test(do_${test} ${test})
endforeach(testnm)
