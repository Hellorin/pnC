/**
 * arc.h
 *
 * Define arcs of a Petri net
 *
 **/

#ifndef ARC_H
#define ARC_H

typedef struct {
	signed int place;
	signed int transition;
	signed int weight;
} arc;

#endif