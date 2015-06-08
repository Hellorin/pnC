#ifndef PNC_TESTS_H
#define PNC_TESTS_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "pnc.h"

// Testing the creation of a PN
void create_pn_test1(void **state);
void create_pn_test2(void **state);
void create_pn_test3(void **state);
void create_pn_test4(void **state);

// Testing the addition of pre arcs to a PN
void add_pre_arc_test1(void **state);
void add_pre_arc_test2(void **state);
void add_pre_arc_test3(void **state);

// Testing the addition of post arcs to a PN
void add_post_arc_test1(void **state);
void add_post_arc_test2(void **state);
void add_post_arc_test3(void **state);

// Testing the function that tells you which transition are enabled 
void t_enabled_test1(void **state);
void t_enabled_test2(void **state);
void t_enabled_test3(void **state);

// Testing the function fire a transition
void t_enabled_fire_test1(void **state);

// Testing the function that

#endif