/**
 * dynarray.h
 *
 * Define dynamic array of arcs and operations
 *
 **/

#ifndef DYNARRAY_H
#define DYNARRAY_H

#define MAX_ELEMS 50

#include <stdlib.h>
#include "arc.h"

// The array of arcs itself
typedef struct {
	arc * elems;
	signed int max_size;
	signed int inc;
	signed int nb_elems;
} dyn_array;

// Array creation
dyn_array * new_array();
dyn_array * new_array_wbounds(signed int max_size);

// Array destruction
void destroy_array(dyn_array * array);

// Appending element to the array
void append_element(dyn_array * array, arc elem);

// Set and get elements
int set_element(dyn_array * array, signed int index, arc elem);
arc * get_element(dyn_array * array, signed int index);

#endif