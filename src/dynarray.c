#include "dynarray.h"

/**
 * Create a new array with default max_size
 */
dyn_array * new_array() {
	dyn_array *array = malloc(sizeof(*array));

	array->max_size = MAX_ELEMS;
	array->nb_elems = 0;
	array->inc = MAX_ELEMS;
	array->elems = malloc(sizeof(array->elems) * MAX_ELEMS);

	return array;
}

/**
 * Create a new array with given max_size
 */
dyn_array * new_array_wbounds(signed int max_size) {
	if (max_size == 0) {
		return NULL;
	}
	
	dyn_array *array = malloc(sizeof(dyn_array));

	array->max_size = max_size;
	array->inc = max_size;
	array->nb_elems = 0;
	array->elems = malloc(sizeof(array->elems) * max_size);

	return array;
}

/**
 * Extend the maximum size of the array if overflowed
 */
int extend_array(dyn_array * array) {
	array->max_size += array->inc;
	
	arc * new_array = malloc(sizeof(array->elems) * array->max_size);
	for (int i=0; i<array->nb_elems; i++) {
		new_array[i] = array->elems[i];
	}
	array->elems = new_array;
	return 0;
}

/**
 * Append an element to the array
 */
int append_element(dyn_array * array, arc elem) {
	if (array->nb_elems == array->max_size) {
		extend_array(array);
	}
	array->elems[array->nb_elems] = elem;
	array->nb_elems++;

	return 0;
}

/**
 * Set the arc element to the given index 
 */
int set_element(dyn_array * array, signed int index, arc elem) {
	if (index < 0 || index >= array->nb_elems) {
		return -1;
	}

	array->elems[index] = elem;
	return 0;
}

/**
 * Get the element at the given index 
 */
arc* get_element(dyn_array * array, signed int index) {
	if (index < 0 || index >= array->nb_elems) {
		arc *a = malloc(sizeof(*a));
		a->place = -1;
		a->transition = -1;
		a->weight = -1;
		return a;
	}

	return &array->elems[index];
}

/**
 * Destroy the array
 */
void destroy_array(dyn_array * array) {
	free(array->elems);
}