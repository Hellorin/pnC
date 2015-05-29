#include "pnC_tests.h"

/* A test case that test the normal creation of a PN */
void create_pn_test1(void **state) {
	signed int marking[1] = {1};
	struct PN * pn = new_pn(1, 1, marking);
	
	assert_non_null(pn);
	
	destroy_pn(pn);

	//(void) state; /* unused */
}

/* A test case that test the abnormal creation of a PN 
 (number places = 0) and (number transitions = 0)*/
void create_pn_test2(void **state) {
	signed int marking[1] = {1};
	struct PN * pn = new_pn(0, 0, marking);
	
	assert_null(pn);
}

/* A test case that test the creation of a PN 
 with 0 transition. This is technically not wrong*/
void create_pn_test3(void **state) {
	signed int nb_transitions = 0;
	signed int marking[1] = {1};
	struct PN * pn = new_pn(1, nb_transitions, marking);
	
	assert_non_null(pn);
}

/* A test case that test the creation of a PN 
 with 0 place. This is technically not wrong*/
void create_pn_test4(void **state) {
	signed int nb_places = 0;
	signed int marking[1] = {1};
	struct PN * pn = new_pn(nb_places, 1, marking);
	
	assert_non_null(pn);
}

/* A test case that test if the creation of a correct pre arc works */
void add_pre_arc_test1(void **state) {
	signed int marking[2] = {1,0};
	struct PN * pn = new_pn(2, 1, marking);
	assert_non_null(pn);

	assert_true(add_pre_arc(pn, 0, 0, 1) == 0);
	assert_true(add_pre_arc(pn, 1, 0, 1) == 0);

	destroy_pn(pn);
}


/* A test case that test if the creation of a pre arc
with inexistant place do fail correctly */
void add_pre_arc_test2(void **state) {
	signed int marking[2] = {1,0};
	struct PN * pn = new_pn(2, 1, marking);
	assert_non_null(pn);

	// There is no such place (3)
	signed int place = 3;
	assert_false(add_pre_arc(pn, place, 0, 1) == 0);
	assert_false(add_pre_arc(pn, 1, place, 1) == 0);

	destroy_pn(pn);
}


/* A test case that test if the creation of a pre arc
with weight = 0 do fail correctly */
void add_pre_arc_test3(void **state) {
	signed int marking[2] = {1,0};
	struct PN * pn = new_pn(2, 1, marking);
	assert_non_null(pn);

	// Cannot put a weight of 0 to an arc
	signed int weight = 0;
	assert_false(add_pre_arc(pn, 0, 0, weight) == 0);
	assert_false(add_pre_arc(pn, 1, 0, weight) == 0);

	destroy_pn(pn);
}


/* A test case that test if the creation of a correct post arc works */
void add_post_arc_test1(void **state) {
	signed int marking[2] = {1,0};
	struct PN * pn = new_pn(2, 1, marking);
	assert_non_null(pn);

	// Everything should work fine
	assert_true(add_post_arc(pn, 0, 0, 1) == 0);
	assert_true(add_post_arc(pn, 1, 0, 1) == 0);

	destroy_pn(pn);
}


/* A test case that test if the creation of a post arc
with inexistant place do fail correctly */
void add_post_arc_test2(void **state) {
	signed int marking[2] = {1,0};
	struct PN * pn = new_pn(2, 1, marking);
	assert_non_null(pn);

	// Everything should work fine
	assert_false(add_post_arc(pn, 3, 0, 1) == 0);
	assert_false(add_post_arc(pn, 1, 3, 1) == 0);

	destroy_pn(pn);
}


/* A test case that test if the creation of a post arc
with weight = 0 do fail correctly */
void add_post_arc_test3(void **state) {
	signed int marking[2] = {1,0};
	struct PN * pn = new_pn(2, 1, marking);
	assert_non_null(pn);
	
	// Cannot put a weight of 0 to an arc
	signed int weight = 0;
	assert_false(add_post_arc(pn, 0, 0, weight) == 0);
	assert_false(add_post_arc(pn, 1, 0, weight) == 0);

	destroy_pn(pn);
}


/* TODO: comment */
void t_enabled1_test(void **state) {
	signed int marking[4] = {1,0,1,0};
	struct PN *pn = new_pn(4, 2, marking);
	assert_non_null(pn);
	
	assert_true(add_pre_arc(pn, 0, 0, 1) == 0);
	assert_true(add_post_arc(pn, 1, 0, 1) == 0);
	
	assert_true(add_pre_arc(pn, 2, 1, 1) == 0);
	assert_true(add_post_arc(pn, 3, 1, 1) == 0);
	
	signed int * en_transitions = m_enabled(pn);
	signed int expected_transitions[2] = {0,1};
	
	for (int i=0; i<2; i++) {
		if (en_transitions[i] == -1) {
			break;
		}
		assert_true(en_transitions[i] == expected_transitions[i]);
		printf("t%i = %i\n", i, en_transitions[i]);
	}
	
}
