#ifndef PNC_H
#define PNC_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * Create a new PN. Gives the number of places, transitions and M0,
 * the initial marking
 */
struct PN *new_pn(int nb_places, int nb_transitions, int marking[]);

/**
 * Add a pre arc to a transition
 */
int add_pre_arc(struct PN *pn, int pre_place, int transition, int weight);


/**
 * Add a post arc to a transition
 */
int add_post_arc(struct PN *pn, int transition, int post_place, int weight);

/**
 * Destroy a PN (free memory)
 */
void destroy_pn(struct PN *pn);

#endif
