enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(tests dat exc hist net out solv sparse util)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

foreach(testnm ${tests})
	set(test test_${testnm})
	add_executable(${test} ${test}.cpp)
	target_link_libraries(${test} sk gtest gtest_main)
	add_test(do_${test} ${test})
endforeach(testnm)
