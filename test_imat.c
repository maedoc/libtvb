/* Apache 2.0 INS-AMU 2015 */

#include <stdio.h>

#include "sk_imat.h"
#include "sk_test.h"

#define M_PI 3.14

int test_imat()
{
	struct sk_imat *m1;

	m1 = sk_imat_from_size(7, 17);
	
	sk_test_true(m1->m==7);
	sk_test_true(m1->n==17);

	sk_imat_set(m1, 3, 4, M_PI);
	sk_test_true(m1->buf[(m1->m)*3 + 4] == M_PI);
	sk_test_true(sk_imat_get(m1, 3, 4) == M_PI);

	fprintf(stderr, "test_mat() o.o.b. error expected: ");
	sk_imat_get(m1, 42, 42);

	return 0;
}
