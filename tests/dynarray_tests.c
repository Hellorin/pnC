#include "dynarray_tests.h"

/* A testcase that test the creation of an array with no given
 maximum bound */
void create_array_test1(void **state) {
	dyn_array * array = new_array();
	assert_non_null(array);
	assert_true(array->nb_elems == 0);
}

/* A testcase that test the creation of an array with a given
 maximum bound */
void create_array_test2(void **state) {
	signed int bound = 2;
	dyn_array * array = new_array_wbounds(bound);

	assert_non_null(array);
	assert_true(array->nb_elems == 0);
	assert_true(array->max_size == 2);
}

/* A testcase that test the creation of an array with a
 maximum bound at 0 */
void create_array_test3(void **state) {
	dyn_array * array = new_array_wbounds(0);
	assert_null(array);
}

/* A testcase that test the addition of element of the end of an array with a
 maximum bound of 2 */
void append_test1(void **state) {
	dyn_array * array = new_array_wbounds(2);
	assert_non_null(array);
	assert_true(array->max_size == 2);
	
	append_element(array, 1);
	assert_true(array->nb_elems == 1);
	assert_true(array->elems[0] == 1);
	assert_true(array->max_size == 2);
	
	append_element(array, 2);
	assert_true(array->nb_elems == 2);
	assert_true(array->elems[0] == 1);
	assert_true(array->elems[1] == 2);
	assert_true(array->max_size == 2);
}

/* A testcase that test the addition of 2++ elements of the end of an array with a
 maximum bound of 2. The array should resize */
void append_test2(void **state) {
	dyn_array * array = new_array_wbounds(2);
	assert_non_null(array);
	assert_true(array->max_size == 2);
	
	append_element(array, 1);
	append_element(array, 2);
	assert_true(array->max_size == 2);
	
	// Add one more element than the maximal capacity
	append_element(array, 3);
	assert_true(array->max_size == 4);
	assert_true(array->elems[2] == 3);
	
	// Add two more element to resize again the array
	append_element(array, 4);
	append_element(array, 5);
	assert_true(array->max_size == 6);
}

/* A testcase that test the addition of 50++ elements of the end of an array with a
 maximum bound of 50. The array should resize */
void append_test3(void **state) {
	dyn_array * array = new_array();
	assert_non_null(array);
	assert_true(array->max_size == MAX_ELEMS);
	
	for (int i=0; i<MAX_ELEMS; i++) append_element(array, i);
	assert_true(array->nb_elems == MAX_ELEMS);
	
	append_element(array, 3);
	assert_true(array->max_size == MAX_ELEMS * 2);
	assert_true(array->nb_elems == MAX_ELEMS + 1);
	
}

/* A testcase that test the normal setting and getting of elements of the array */
void getset_test1(void ** state) {
	dyn_array * array = new_array();
	assert_non_null(array);
	assert_true(array->max_size == MAX_ELEMS);

	for (int i=0; i<MAX_ELEMS; i++) append_element(array, i);

	for (int i=0; i<MAX_ELEMS; i++) assert_true(i == get_element(array, i));

	for (int i=0; i<MAX_ELEMS; i++) assert_true(0 == set_element(array, i, 10));

	for (int i=0; i<MAX_ELEMS; i++) assert_true(10 == array->elems[i]);
}

/* A testcase that test the getting of elements out of the bounds of the array */
void get_test1(void ** state) {
	dyn_array * array = new_array();
	assert_non_null(array);
	assert_true(array->max_size == MAX_ELEMS);

	assert_true(get_element(array, -1, 10) == -1);

	assert_true(get_element(array, 7, 10) == -1);
}

/* A testcase that test the setting of elements out of the bounds of the array */
void set_test1(void ** state) {
	dyn_array * array = new_array();
	assert_non_null(array);
	assert_true(array->max_size == MAX_ELEMS);
	
	assert_true(set_element(array, -1, 10) == -1);
	
	assert_true(set_element(array, 4, 10) == -1);
}