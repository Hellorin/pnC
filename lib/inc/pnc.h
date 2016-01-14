#ifndef PNC_H
#define PNC_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dynarray.h"
#include "arc.h"

typedef struct {
	signed int nb_pre_arcs;
	dyn_array *pre_arcs;
} pre_conds;

typedef struct {
	dyn_array *post_arcs;
	signed int nb_post_arcs;
} post_conds;

struct PN {
	signed int nb_places;
	signed int nb_transitions;

	// P (places)
	signed int *places;

	// T (transitions)
	signed int *transitions;
	
	// F = F_1 U F_2 (flow)
	// W = W_1 U W_2 (weight)
	pre_conds *pre_conditions; // F_1 and W_1
	post_conds *post_conditions; // F_2 and W_2
	
	// M (marking)
	signed int *marking;
};


/**
 * Create a new PN. Gives the number of places, transitions and M0,
 * the initial marking
 */
struct PN *new_pn(signed int nb_places, signed int nb_transitions, signed int marking[]);

/**
 * Destroy a PN (free memory)
 */
void destroy_pn(struct PN *pn);

/**
 * Return the current marking of a Petri net
 */
int* get_marking(struct PN *pn);

/**
 * Set the current marking of a Petri net
 */
void set_marking(struct PN *pn, signed int marking[], signed int size);

/**
 * Add a pre arc to a transition
 */
int add_pre_arc(struct PN *pn, signed int pre_place, signed int transition, signed int weight);

/**
 * Add a post arc to a transition
 */
int add_post_arc(struct PN *pn, signed int post_place, signed int transition, signed int weight);

/**
 * Return if the transition t is M-enabled
 */
int t_m_enabled(struct PN *pn, signed int t);

/**
 * Return all the M-enabled transition
 */
int* m_enabled(struct PN *pn);

/**
 * Fire the transition t
 */
int *fire_transition(struct PN * pn, signed int t);

/**
 * Fire all possible transitions
 */
int **fire_all_enabled_transitions(struct PN * pn, int * nb_markings);

#endif
