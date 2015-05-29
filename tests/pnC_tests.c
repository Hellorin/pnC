#include "pnC_tests.h"

/* A test case that test the normal creation of a PN */
void create_pn_test1(void **state) {
	signed int marking[1] = {1};
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
void add_pre_arc_test1(void **state) {
	int marking[1] = {1,0};
	struct PN * pn = new_pn(2, 1, marking);
	assert_non_null(pn);

	assert_return_code(add_pre_arc(pn, 0, 0, 1), 0);
	assert_return_code(add_pre_arc(pn, 1, 0, 1), 0);

	destroy_pn(pn);

}