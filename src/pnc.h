#ifndef PNC_H
#define PNC_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
 * Add a pre arc to a transition
 */
int add_pre_arc(struct PN *pn, signed int pre_place, signed int transition, signed int weight);

/**
 * Add a post arc to a transition
 */
int add_post_arc(struct PN *pn, signed int transition, signed int post_place, signed int weight);

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

#endif
