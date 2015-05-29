#ifndef DYNARRAY_TESTS_H
#define DYNARRAY_TESTS_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "dynarray.h"

// Testing the creation of a dynamic array
void create_array_test1(void **state);
void create_array_test2(void **state);
void create_array_test3(void **state);

// Testing the addition of elements at the end of an array
void append_test1(void **state);
void append_test2(void **state);
void append_test3(void **state);

// Testing the get and set of an array
void getset_test1(void ** state);
void get_test1(void ** state);
void set_test1(void ** state);

#endif