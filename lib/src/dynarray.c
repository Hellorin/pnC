/**
 * dynarray.c
 *
 * Define dynamic array of arcs and operations
 *
 **/

#include "dynarray.h"

/**
 * Create a new array of arcs with default MAX_ELEMS (defined in dynarray.h)
 *
 * @return
 *      A new dynamic array of size MAX_ELEMS.
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
 * Create a new array of arcs with given max_size
 *
 * @param max_size
 *      Current maximum size of the new dynamic array
 *
 * @return
 *      A new dynamic array of maximum size max_size
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
 *
 * @param array
 *      The array in pointer for which the max size must be extended
 */
void extend_array(dyn_array * array) {
    array->max_size += array->inc;

    arc * new_array = malloc(sizeof(array->elems) * array->max_size);
    for (int i=0; i<array->nb_elems; i++) {
        new_array[i] = array->elems[i];
    }

    array->elems = new_array;
}

/**
 * Append an arc to the dynamic array
 *
 * @param array
 *      Array of arcs for which the arc must be added
 * @param elem
 *      Arc that is added to the list of arcs
 */
void append_element(dyn_array * array, arc elem) {
    if (array->nb_elems == array->max_size) {
        extend_array(array);
    }
    array->elems[array->nb_elems] = elem;
    array->nb_elems++;
}

/**
 * Set the arc element to the given index 
 *
 * @param array
 *      Array for which an arc must be added
 * @param index
 *      Index in which the arc must be added in the list of arcs
 * @param elem
 *      Arc that must be added at the given index of the list of arcs
 * @return
 *      0 if the arc could be added correctly, -1 otherwise
 */
int set_element(dyn_array * array, signed int index, arc elem) {
    if (index < 0 || index >= array->nb_elems) {
        return -1;
    }

    array->elems[index] = elem;

    return 0;
}

/**
 * Get the arc at the given index of a list of arcs
 *
 * @param array
 *      The list of arcs in which the arc at the given index must be taken
 * @param index
 *      The index of the arc that must be returned
 * @return
 *      The arc at the given index of the list of arcs array or null if no arc
 *      exists at the given index
 */
arc* get_element(dyn_array * array, signed int index) {
    if (index < 0 || index >= array->nb_elems) {
        return NULL;
    }

    return &array->elems[index];
}

/**
 * Destroy the array
 *
 * @param array
 *      Free the memory of that array
 */
void destroy_array(dyn_array * array) {
	free(array->elems);
}