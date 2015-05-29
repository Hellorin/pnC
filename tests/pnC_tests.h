#ifndef PNC_TESTS_H
#define PNC_TESTS_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "pnc.h"

void create_pn_test1(void **state);
void create_pn_test2(void **state);
void create_pn_test3(void **state);
void create_pn_test4(void **state);

void add_pre_arc_test1(void **state);
void add_pre_arc_test2(void **state);
void add_pre_arc_test3(void **state);

void add_post_arc_test1(void **state);
void add_post_arc_test2(void **state);
void add_post_arc_test3(void **state);

#endif