/* copyright 2016 Apache 2 sddekit authors */

void sd_test_true(bool cond, char *scond, char *fname, int lineno);

void sd_test_failed(char *scond, char *fname, int lineno);

int sd_test_report();

#define EXPECT_TRUE(cond) sd_test_true(cond, #cond, __FILE__, __LINE__)

#define EXPECT_EQ(l, r) EXPECT_TRUE((l)==(r))

#define ASSERT_NEAR(l, r, tol) EXPECT_TRUE((((l)-(r))*((l)-(r)))<tol)

#define TEST(topic, name) void sd_test__ ## topic ## _ ## name ()
