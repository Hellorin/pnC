#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "pnC_tests.h"

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
		cmocka_unit_test(add_post_arc_test3)
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
