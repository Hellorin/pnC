/**
 * pnC_tests.c
 *
 * Tests for the pnC library especially
 *
 * @author David LAWRENCE
 *
 **/

#include "pnC_tests.h"

/* A test case that test the normal creation of a PN */
void create_pn_test1(void **state) {
    signed int marking[1] = {1};
    struct PN * pn = new_pn(1, 1, marking);

    assert_non_null(pn);

    destroy_pn(pn);
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

/* A test case that test the retrieving of the set of transitions enabled */
void t_enabled_test1(void **state) {
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
    }
}

/* A second test case that test the retrieving of the set of transitions enabled */
void t_enabled_test2(void **state) {
    signed int marking[4] = {1,0,0,0};
    struct PN *pn = new_pn(4, 2, marking);
    assert_non_null(pn);

    assert_true(add_pre_arc(pn, 0, 0, 1) == 0);
    assert_true(add_post_arc(pn, 1, 0, 1) == 0);

    assert_true(add_pre_arc(pn, 2, 1, 1) == 0);
    assert_true(add_post_arc(pn, 3, 1, 1) == 0);

    signed int * en_transitions = m_enabled(pn);
    signed int expected_transitions[1] = {0};

    for (int i=0; i<2; i++) {
        if (en_transitions[i] == -1) {
            break;
        }
        assert_true(en_transitions[i] == expected_transitions[i]);
    }
}

/* A third test case that test the retrieving of the set of transitions enabled */
void t_enabled_test3(void **state) {
    signed int marking[4] = {0,0,0,0};
    struct PN *pn = new_pn(4, 2, marking);
    assert_non_null(pn);

    assert_true(add_pre_arc(pn, 0, 0, 1) == 0);
    assert_true(add_post_arc(pn, 1, 0, 1) == 0);

    assert_true(add_pre_arc(pn, 2, 1, 1) == 0);
    assert_true(add_post_arc(pn, 3, 1, 1) == 0);

    signed int * en_transitions = m_enabled(pn);

    for (int i=0; i<1; i++) {
        if (en_transitions[i] == -1) {
            break;
        }
        assert_true(0);
    }
}

/* A test case that test the firing of a transition */
void t_enabled_fire_test1(void **state) {
    signed int marking[2] = {1,0};
    struct PN *pn = new_pn(2, 2, marking);
    assert_non_null(pn);

    assert_true(add_pre_arc(pn, 0, 0, 1) == 0);
    assert_true(add_post_arc(pn, 1, 0, 1) == 0);

    assert_true(add_pre_arc(pn, 1, 1, 1) == 0);
    assert_true(add_post_arc(pn, 0, 1, 1) == 0);

    assert_true(t_m_enabled(pn,0) == 1);
    assert_true(t_m_enabled(pn,1) == 0);

    int * marking1 = fire_transition(pn, 0);
    int expected1[2] = {0,1};
    for (int i=0; i<2; i++) {
        assert_true(expected1[i] == marking1[i]);
    }

    int expected2[2] = {1,0};
    marking1 = fire_transition(pn, 1);
    for (int i=0; i<2; i++) {
        assert_true(expected2[i] == marking1[i]);
    }

    int nb_markings = 0;
    int ** list_markings = fire_all_enabled_transitions(pn, &nb_markings);

    assert_true(nb_markings == 1);
}

/* A test case that test the retrieving of the set of transitions enabled */
void fire_a_transition_test1(void **state) {
    signed int marking[4] = {1,0,1,0};
    struct PN *pn = new_pn(4, 2, marking);
    assert_non_null(pn);
    assert_true(add_pre_arc(pn, 0, 0, 1) == 0);
    assert_true(add_post_arc(pn, 1, 0, 1) == 0);
    assert_true(add_pre_arc(pn, 2, 1, 1) == 0);
    assert_true(add_post_arc(pn, 3, 1, 1) == 0);

    int expected[4] = {0,1,1,0};
    int * new_marking = fire_transition(pn, 0);
    for (int i=0; i<pn->nb_places; i++) {
        assert_true(new_marking[i] == expected[i]);
    }
}
