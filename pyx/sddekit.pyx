cimport numpy as np
import numpy as np

# generic callbacks
cdef extern from "sk_hist.h":
	struct sk_hist:
		pass
	ctypedef struct sk_hist sk_hist

# a python defined system should implement __call__
cdef public api int sk_pysys(void * restrict data,
		sk_hist * restrict hist,
		double t, int i,
		int nx, double * restrict x,
		double * restrict f, double * restrict g,
		double * restrict Jf, double * restrict Jg,
		int nc, double * restrict c, double * restrict Jce):
	# create numpy views on pointers
	x_ = np.asarray(<np.float64_t[:nx]> x)
	f_ = np.asarray(<np.float64_t[:nx]> f)
	g_ = np.asarray(<np.float64_t[:nx]> g)
	# TODO Jf Jg Jce
	c_ = np.asarray(<np.float64_t[:nc]> c)
	# call object
	return (<object> data)(x_, f_, g_, c_)

# now we can pass <void*>obj and sk_pysys to use a Python-defined system
