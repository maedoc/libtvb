set(benchmarks net_exc randn_axpy_nnz)

foreach(bench ${benchmarks})
	add_executable(bench_${bench} bench_${bench}.c)
	target_link_libraries(bench_${bench} libsk)
endforeach(bench)
