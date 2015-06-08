#ifndef DYNARRAY_H
#define DYNARRAY_H

#define MAX_ELEMS 50

#include <stdlib.h>
#include "arc.h"

typedef struct {
	arc * elems;
	signed int max_size;
	signed int inc;
	signed int nb_elems;
} dyn_array;

dyn_array * new_array();
dyn_array * new_array_wbounds(signed int max_size);
	
int append_element(dyn_array * array, arc elem);

int set_element(dyn_array * array, signed int index, arc elem);
arc * get_element(dyn_array * array, signed int index);

#endif