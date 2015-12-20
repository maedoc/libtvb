/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_TEST_H
#define SK_TEST_H

void sk_test_true(int cond, char *scond, char *fname, int lineno);

void sk_test_failed(char *scond, char *fname, int lineno);

int sk_test_report();

#define EXPECT_TRUE(cond) sk_test_true(cond, #cond, __FILE__, __LINE__)

#define EXPECT_EQ(l, r) EXPECT_TRUE((l)==(r))

#define ASSERT_NEAR(l, r, tol) EXPECT_TRUE((((l)-(r))*((l)-(r)))<tol)

#define TEST(topic, name) void sk_test__ ## topic ## _ ## name ()

#endif
