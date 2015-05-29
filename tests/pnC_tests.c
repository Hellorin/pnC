#include "pnC_tests.h"

/* A test case that test the normal creation of a PN */
void create_pn_test1(void **state) {
	int marking[1] = {1};
	struct PN * pn = new_pn(1, 1, marking);
	
	assert_non_null(pn);
	
	destroy_pn(pn);

	//(void) state; /* unused */
}

/* A test case that test the abnormal creation of a PN */
void create_pn_test2(void **state) {
	int marking[1] = {1};
	struct PN * pn = new_pn(0, 0, marking);
	
	assert_null(pn);
	
}

/* A test case that test the abnormal creation of a PN */
void create_pn_test3(void **state) {
	int marking[1] = {1};
	struct PN * pn = new_pn(0, 0, marking);
	
	assert_null(pn);
	//(void) state; /* unused */
}