/**
 * alltests.c
 *
 * All tests for the pnC library
 *
 * @author David LAWRENCE
 *
 **/

// Std includes
#include <stdarg.h>
#include <stddef.h>

// Testing includes
#include <setjmp.h>
#include <cmocka.h>

// Personal includes
#include "pnC_tests.h"
#include "dynarray_tests.h"

int main() {
    const struct CMUnitTest tests[] = {
        // Testing the creation of a PN
        cmocka_unit_test(create_pn_test1),
        cmocka_unit_test(create_pn_test2),
        cmocka_unit_test(create_pn_test3),
        cmocka_unit_test(create_pn_test4),

        // Testing the addition of pre arcs to a PN
        cmocka_unit_test(add_pre_arc_test1),
        cmocka_unit_test(add_pre_arc_test2),
        cmocka_unit_test(add_pre_arc_test3),

        // Testing the addition of post arcs to a PN
        cmocka_unit_test(add_post_arc_test1),
        cmocka_unit_test(add_post_arc_test2),
        cmocka_unit_test(add_post_arc_test3),

        // Testing the function that tells you which transition are enabled 
        cmocka_unit_test(t_enabled_test1),
        cmocka_unit_test(t_enabled_test2),
        cmocka_unit_test(t_enabled_test3),

        // Testing the function that fire a transition if the later is enabled
        cmocka_unit_test(t_enabled_fire_test1),
        cmocka_unit_test(fire_a_transition_test1),

        // Testing the creation of a dynamic array
        cmocka_unit_test(create_array_test1),
        cmocka_unit_test(create_array_test2),
        cmocka_unit_test(create_array_test3),

        // Testing the appending of an arc to a dynamic array
        cmocka_unit_test(append_test1),
        cmocka_unit_test(append_test2),
        cmocka_unit_test(append_test3),

        // Testing the setter and getter of the dynamic array
        cmocka_unit_test(getset_test1),
        cmocka_unit_test(get_test1),
        cmocka_unit_test(set_test1)

    };

    // Execute tests
    return cmocka_run_group_tests(tests, NULL, NULL);
}
