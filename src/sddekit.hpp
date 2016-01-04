/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

#include <string>
#include <vector>

/**
 * \file sddekit.hpp C++ interface to sddekit.
 *
 */

namespace sd
{
	const uint32_t ver_major = sd_ver_major;
	const uint32_t ver_minor = sd_ver_minor;

	inline std::vector<double>
	read_square_matrix(std::string fname)
	{
		int i, n;
		double *w;
		std::vector<double> out;
		sd_util_read_square_matrix(fname.c_str(), &n, &w);
		for (i=0; i<n; i++)
			out.push_back(w[i]);
		sd_free(w);
		return out;
	}

	inline int
	uniqi(const int n, const int * restrict ints, 
		      int * restrict nuniq, int ** restrict uints)
	{
		return sd_util_uniqi(n, ints, nuniq, uints);
	}

} /* namespace sd */
