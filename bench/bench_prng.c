//NOT NOW

/*
 * Measure the performance of the generator.
 */
/*
void measurePerformance(size_t wg_size, size_t wg_num, int gen_per_it,
	cl_mem *buff_state, cl_mem *buff_prns,
	cl_program program, cl_command_queue queue)
{
	cl_int err;

	cl_event event_start, event_end;
	cl_ulong time_start, time_end, iter_num, tot_num;
	double time_elapsed, time_goal = 15.0;
	size_t wi_tot = wg_size * wg_num;

	cl_kernel kernel_prn_light = clCreateKernel(program,
		"kernelPrnLight", &err);
	IUNCLERR( err );

	IUNCLERR( clSetKernelArg(kernel_prn_light, 0, 
		sizeof(buff_state), buff_state) );
	IUNCLERR( clSetKernelArg(kernel_prn_light, 1, 
		sizeof(buff_prns), buff_prns) );

	//First measure approx time for a single iteration and scale
	//to hit time goal.
	IUNCLERR( clEnqueueNDRangeKernel(queue, kernel_prn_light, 1, NULL,
		&wi_tot, &wg_size, 0, NULL, &event_start) );

	IUNCLERR( clFinish(queue) );
	
	IUNCLERR( clGetEventProfilingInfo(event_start, CL_PROFILING_COMMAND_QUEUED,
		sizeof(time_start), &time_start, NULL) );

	IUNCLERR( clGetEventProfilingInfo(event_start, CL_PROFILING_COMMAND_END,
		sizeof(time_end), &time_end, NULL) );

	time_elapsed = (time_end - time_start) * 1E-9;
	iter_num = (cl_ulong)ceil(time_goal / time_elapsed);

	printf("%*s %llu iterations\n", -PAD, "Starting performance run with:",
		(unsigned long long)iter_num);

	tot_num = iter_num * wi_tot * gen_per_it * 4;

	IUNCLERR( clEnqueueNDRangeKernel(queue, kernel_prn_light, 1, NULL,
		&wi_tot, &wg_size, 0, NULL, &event_start) );

	for(cl_ulong iter = 1; iter < iter_num; iter++)
		IUNCLERR( clEnqueueNDRangeKernel(queue, kernel_prn_light, 1, NULL,
			&wi_tot, &wg_size, 0, NULL, &event_end) );

	IUNCLERR( clFinish(queue) );

	IUNCLERR( clGetEventProfilingInfo(event_start, CL_PROFILING_COMMAND_QUEUED,
		sizeof(time_start), &time_start, NULL) );

	IUNCLERR( clGetEventProfilingInfo((iter_num < 2) ? event_start : event_end,
		CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL) );

	time_elapsed = (time_end - time_start) * 1E-9;

	printf("%*s %.3f s\n%*s %.3f M num / s\n\n", 
		-PAD, "Finised run in:", time_elapsed,
		-PAD, "Generation speed:", tot_num / (time_elapsed * 1E6));
}

*/
