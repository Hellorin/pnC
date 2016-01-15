/**
 * pnc.c
 *
 * Define black and white Petri nets and theirs operations
 *
 * @author David LAWRENCE
 *
 **/

// Std includes

// Personal includes
#include "pnc.h"

/**
 * Create a new PN. Gives the number of places, transitions and M0,
 * the initial marking.
 *
 * @param nb_places
 *      Number of places of the new Petri net
 * @param nb_transitions
 *      Number of transitions of the new Petri net
 * @param marking
 *      Initial marking for the Petri net
 * @return
 *      The newly created Petri net or NULL if there was a problem
 */
struct PN *new_pn(signed int nb_places, signed int nb_transitions, signed int marking[]) {
    assert(nb_transitions != 0 && nb_places != 0);

    #ifdef VERBOSE
    printf("Creating a new PN:\n");
    printf("\t%i places\n", nb_places);
    printf("\t%i transitions\n\n", nb_transitions);
    #endif

    if (nb_transitions <= 0 && nb_places <= 0) {
        return NULL;
    }

    struct PN *pn = malloc(sizeof(*pn));

    // Initialize places
    pn->nb_places = nb_places;
    pn->places = malloc (sizeof (pn->places) * nb_places);
    for (int i=0; i<nb_places; i ++) {
        pn->places[i] = i;
    }

    // Initialize pre conditions	
    pn->pre_conditions = malloc (sizeof (*pn->pre_conditions) * nb_transitions);
    for (int i=0; i<nb_transitions; i++) {
        pn->pre_conditions[i].nb_pre_arcs = 0;
        pn->pre_conditions[i].pre_arcs = new_array();
    }

    // Initialize post conditions
    pn->post_conditions = malloc (sizeof (*pn->post_conditions) * nb_transitions);
    for (int i=0; i<nb_transitions; i++) {
        pn->post_conditions[i].nb_post_arcs = 0;
        pn->post_conditions[i].post_arcs = new_array();
    }

    // Initialize transitions
    pn->nb_transitions = nb_transitions;
    pn->transitions = malloc (sizeof (*pn->transitions) * nb_transitions);
    for (int i=0; i<nb_transitions; i ++) {
        pn->transitions[i] = i;
    }

    // Initialize marking
    pn->marking = malloc(sizeof(*pn->marking) * nb_places);
    for (int i=0; i<nb_places; i++) {
        pn->marking[i] = marking[i];
    }

    assert(pn != NULL);
    return pn;
}

/**
 * Destroy a PN (free memory)
 *
 * @param pn
 *      The Petri net to be destroyed
 */
void destroy_pn(struct PN *pn) {
    free(pn->places);
    free(pn->transitions);

    // Free pre conditions
    for (int i=0; i<pn->nb_transitions; i++) {
        int nb_arcs = pn->pre_conditions[i].nb_pre_arcs;

        // Free pre arcs
        if (nb_arcs != 0) {
            free(pn->pre_conditions[i].pre_arcs);
        }
    }

    // Free post conditions
    for (int i=0; i<pn->nb_transitions; i++) {
        int nb_arcs = pn->post_conditions[i].nb_post_arcs;

        // Free post arcs
        if (nb_arcs != 0) {
            free(pn->post_conditions[i].post_arcs);
        }
    }

    // Free marking
    free(pn->marking);
}

/**
 * Return the current marking of a Petri net
 *
 * @param pn
 *      The Petri net from which we desire the marking
 * @return
 *      The marking of the Petri net given in parameter
 */
int* get_marking(struct PN *pn) {
    return pn->marking;
}

/**
 * Set the current marking of a Petri net
 *
 * @param pn
 *      The Petri net from which we desire to set the marking
 * @param marking
 *      The marking to be set
 * @param size
 *      The size of the marking to be set
 */
void set_marking(struct PN *pn, signed int marking[], signed int size) {
    for (int i = 0; i < size; i++) {
        pn->marking[i] = marking[i];
    }
}

/**
 * Add a pre arc to a transition
 *
 * @param pn
 *      The Petri net for which we must add a pre arc from a given place to a transition.
 * @param pre_place
 *      The pre place of the arc
 * @param transition
 *      The transition of the arc
 * @param weight
 *      The weight of the arc
 * @return
 *      -1 if there was a problem, 0 otherwise
 */
int add_pre_arc(struct PN *pn, signed int pre_place, signed int transition, signed int weight) {
    assert(pn != NULL);
    assert(pre_place >= 0);
    assert(transition >= 0);
    assert(weight > 0);

    // Ensure that the pre place to which the arc start from exists
    if (pre_place >= pn->nb_places) {
        // Error
        return -1;
    }

    // Ensure that the given transition exists
    if (transition >= pn->nb_transitions) {
        // Error
        return -1;
    }
    // Ensure that the given weight is higher than 0
    if (weight == 0) {
        // Error
        return -1;
    }

    int nb_before = pn->pre_conditions[transition].nb_pre_arcs;
    pn->pre_conditions[transition].nb_pre_arcs += 1;

    // Create a new list of pre conditions of the size of the old + 1
    // for that transition
    dyn_array *pre = pn->pre_conditions[transition].pre_arcs;

    // Create the new pre condition for that transition and add it to the list
    // of pre conditions
    arc new_pre = {pre_place, transition, weight};
    append_element(pn->pre_conditions[transition].pre_arcs, new_pre);

    #ifdef VERBOSE
    printf("Adding a pre arc:\n");
    printf("\tPre place p%i\n", pre_place);
    printf("\tTransition t%i\n", transition);
    printf("\tWeight %i\n\n", weight);
    #endif

    return 0;
}


/**
 * Add a post arc to a transition
 *
 * @param pn
 *      The Petri net for which we must add a post arc from a given transition to a place.
 * @param post_place
 *      The post place of the arc
 * @param transition
 *      The transition of the arc
 * @param weight
 *      The weight of the arc
 * @return
 *      -1 if there was a problem, 0 otherwise
 */
int add_post_arc(struct PN *pn, signed int post_place, signed int transition, signed int weight) {
    assert(pn != NULL);
    assert(post_place >= 0);
    assert(transition >= 0);

    // Ensure that the given transition exists
    if (transition >= pn->nb_transitions) {
        // Error
        return -1;
    }

    // Ensure that the post place to which the arc goes exists
    if (post_place >= pn->nb_places) {
        // Error
        return -1;
    }

    // Ensure that the given weight is higher than 0
    if (weight == 0) {
        // Error
        return -1;
    }

    int nb_before = pn->post_conditions[transition].nb_post_arcs;
    pn->post_conditions[transition].nb_post_arcs += 1;

    // Create a new list of post conditions of the size of the old + 1
    // for that transition
    dyn_array *post = pn->post_conditions[transition].post_arcs;

    // Create the new post condition for that transition and add it to the list
    // of post conditions
    arc new_post = {post_place, transition, weight};
    append_element(pn->post_conditions[transition].post_arcs, new_post);

    #ifdef VERBOSE
    printf("Adding a post arc:\n");
    printf("\tTransition t%i\n", transition);
    printf("\tPost place p%i\n", post_place);
    printf("\tWeight %i\n\n", weight);
    #endif

    return 0;
}


void consume_pre(struct PN * pn, signed int t, signed int * marking) {
    for (int i=0; i<pn->pre_conditions[t].nb_pre_arcs; i++) {
        arc * a = get_element(pn->pre_conditions[t].pre_arcs, i);
        int pre_place = a->place;
        int weight = a->weight;

        marking[pre_place] -= weight;
    }
}

void produce_post(struct PN * pn, signed int t, signed int * marking) {
    for (int i=0; i<pn->post_conditions[t].nb_post_arcs; i++) {
        arc * a = get_element(pn->post_conditions[t].post_arcs, i);
        int post_place = a->place;
        int weight = a->weight;

        marking[post_place] += weight;
    }
}

/**
 * Fire the transition t
 */
int *fire_transition(struct PN * pn, signed int t) {
    // Ensure that the given transition exists
    if (t < 0 || t >= pn->nb_transitions) {
        // Error
        return pn->marking;
    }

    int * new_marking = malloc(sizeof(* new_marking) * pn->nb_places);

    // Copy a the current marking to a new marking
    for (int i=0; i<pn->nb_places; i++) {
        new_marking[i] = pn->marking[i];
    }

    // Fire the transition
    if (t_m_enabled(pn, t)) {
        #ifdef VERBOSE
        printf("Firing the transition t%d\n", t);
        #endif

        consume_pre(pn, t, new_marking);

        produce_post(pn, t, new_marking);
    } else {
        #ifdef VERBOSE
        printf("Cannot fire the transition t%d\n", t);
        #endif
    }

    return new_marking;
}

/**
 * Fire all enabled transitions
 * 
 * @param pn
 *      The Petri net itself
 * @param nb_markings
 *      A pointer to let know the caller how many markings were reached
 * @return
 *      All reachable markings
 */
int **fire_all_enabled_transitions(struct PN * pn, int * nb_markings) {
    int ** all_reachable_marking = malloc(sizeof (int *) * pn->nb_transitions);
    int curr_nb_markings = *nb_markings;

    // Iterate over all transitions
    for (int i=0; i<pn->nb_transitions; i++) {

        // If the transition is fireable, fire it
        if (t_m_enabled(pn, i)) {
            int * new_marking = fire_transition(pn, i);
            all_reachable_marking[curr_nb_markings] = new_marking;
            curr_nb_markings++;
        }
    }

    *nb_markings = curr_nb_markings;

    return all_reachable_marking;
}

/**
 * Return if the transition t is M-enabled
 *
 * @param pn
 *      The Petri net from which we want to know all enabled transitions
 *      from its current marking.
 * @param t
 *      The transition that we want to know if it is enabled or not
 * @return
 *      1 if the pre conditions are met, 0 if not, -1 if the transitions doesn't exist
 */
int t_m_enabled(struct PN *pn, signed int t) {
    // The transition doesn't exist
    if (t >= pn->nb_transitions) {
        return -1;
    }

    int nb_pre_arcs = pn->pre_conditions[t].nb_pre_arcs;
    int nb_successful_pre = 0;

    // Check the precondition of the transition
    for (int j=0; j<nb_pre_arcs; j++) {
        arc * a = get_element(pn->pre_conditions[t].pre_arcs, j);
        int pre_place = a->place;
        if (a->weight <= pn->marking[pre_place]) {
            nb_successful_pre++;
        }
    }

    // Return 1 if the pre condition is true, 0 otherwise
    return nb_pre_arcs == nb_successful_pre;
}


/**
 * Return all the M-enabled transition
 *
 * @param pn
 *      The Petri net from which we want to know all enabled transitions
 *      from its current marking.
 * @return
 *      A list of enabled transitions
 */
int* m_enabled(struct PN *pn) {
    int * transitions = malloc(sizeof(*transitions) * pn->nb_transitions);

    // Check for each transition, if its pre condition is satisfied
    int nb_enabled_transition = 0;
    for (int i=0; i<pn->nb_transitions; i++) {
        if (t_m_enabled(pn, i)) {
            transitions[nb_enabled_transition] = i;
            nb_enabled_transition++;
        }
    }

    // The value of -1 help to determine the transition not having
    // its pre condition satisfied
    for (int i=nb_enabled_transition; i<pn->nb_transitions; i++) {
        transitions[i] = -1;
    }

    return transitions;
}
