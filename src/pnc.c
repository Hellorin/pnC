

// Std includes


// Personal includes
#include "pnc.h"

typedef struct {
	signed int pre_place;
	signed int transition;
	signed int weight;
} pre_arc;

typedef struct {
	signed int transition;
	signed int post_place;
	signed int weight;
} post_arc;

typedef struct {
	signed int nb_pre_arcs;
	pre_arc *pre_arcs;
} pre_conds;

// 
typedef struct {
	post_arc *post_arcs;
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
struct PN *new_pn(int nb_places, int nb_transitions, signed int marking[]) {
	assert(nb_transitions != 0 && nb_places != 0);
	
	if (nb_transitions == 0 && nb_places == 0) {
		return NULL;
	}

	
	struct PN *pn = malloc(sizeof(struct PN));

	// Initialize places
	pn->nb_places = nb_places;
	pn->places = malloc (sizeof (int) * nb_places);
	for (int i=0; i<nb_places; i ++) {
		pn->places[i] = i;
	}

	// Initialize pre conditions	
	pn->pre_conditions = malloc (sizeof (pre_conds) * nb_transitions);
	for (int i=0; i<nb_transitions; i++) {
		pn->pre_conditions[i].nb_pre_arcs = 0;
	}

	// Initialize post conditions
	pn->post_conditions = malloc (sizeof (post_conds) * nb_transitions);
	for (int i=0; i<nb_transitions; i++) {
		pn->post_conditions[i].nb_post_arcs = 0;
	}

	// Initialize transitions
	pn->nb_transitions = nb_transitions;
	pn->transitions = malloc (sizeof (int) * nb_transitions);
	for (int i=0; i<nb_transitions; i ++) {
		pn->transitions[i] = i;
	}

	// Initialize marking
	pn->marking = malloc(sizeof(int) * nb_places);
	for (int i=0; i<nb_places; i++) {
		pn->marking[i] = marking[i];
	}
	
	assert(pn != NULL);
	return pn;
}

/**
 * Add a pre arc to a transition
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
	pre_arc *pre = pn->pre_conditions[transition].pre_arcs;
	pre_arc *new_pres = malloc(sizeof(pre_arc) * (nb_before + 1));

	// Add the existing pre conditions to the new list of pre conditions
	for (int i=0; i<nb_before; i++) {
		new_pres[i].pre_place = pre[i].pre_place;
		new_pres[i].transition = pre[i].transition;
		new_pres[i].weight = pre[i].weight;
	}
	
	// Create the new pre condition for that transition and add it to the list
	// of pre conditions
	pre_arc new_pre = {pre_place, transition, weight};
	new_pres[nb_before] = new_pre;
	pn->pre_conditions[transition].pre_arcs = new_pres;

	#ifdef VERBOSE
	printf("Adding a pre arc:\n");
	printf("\tPre place p%i\n", pre_place);
	printf("\tTransition t%i\n", transition);
	printf("\tWeight %i\n\n", weight);
	#endif

	assert(pn->pre_conditions[transition].pre_arcs[nb_before].pre_place == pre_place);
	assert(pn->pre_conditions[transition].pre_arcs[nb_before].transition == transition);
	
	return 0;
}


/**
 * Add a post arc to a transition
 */
int add_post_arc(struct PN *pn, signed int post_place, signed int transition, signed int weight) {
	assert(pn != NULL);
	assert(post_place >= 0);
	assert(transition >= 0);
	
	// Assure that the given transition exists
	if (transition >= pn->nb_transitions) {
		// Error
		return -1;
	}
	// Assure that the post place to which the arc goes exists
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
	post_arc *post = pn->post_conditions[transition].post_arcs;
	post_arc *new_posts = malloc(sizeof(post_arc) * (nb_before + 1));

	// Add the existing post conditions to the new list of post conditions
	for (int i=0; i<nb_before; i++) {
		new_posts[i].post_place = post[i].post_place;
		new_posts[i].transition = post[i].transition;
		new_posts[i].weight = post[i].weight;
	}
	
	// Create the new post condition for that transition and add it to the list
	// of post conditions
	post_arc new_post = {transition, post_place, weight};
	new_posts[nb_before] = new_post;
	pn->post_conditions[transition].post_arcs = new_posts;

	#ifdef VERBOSE
	printf("Adding a post arc:\n");
	printf("\tTransition t%i\n", transition);
	printf("\tPost place p%i\n", post_place);
	printf("\tWeight %i\n\n", weight);
	#endif

	// Ensure that the post condition is correctly added
	assert(pn->post_conditions[transition].post_arcs[nb_before].post_place == post_place);
	assert(pn->post_conditions[transition].post_arcs[nb_before].transition == transition);

	return 0;
}


void consume_pre(struct PN * pn, signed int t, signed int * marking) {
	for (int i=0; i<pn->pre_conditions[t].nb_pre_arcs; i++) {
		int pre_place = pn->pre_conditions[t].pre_arcs[i].pre_place;
		int weight = pn->pre_conditions[t].pre_arcs[i].weight;
		marking[pre_place] -= weight;
	}
}

void produce_post(struct PN * pn, signed int t, signed int * marking) {
	for (int i=0; i<pn->post_conditions[t].nb_post_arcs; i++) {
		int post_place = pn->post_conditions[t].post_arcs[i].post_place;
		int weight = pn->post_conditions[t].post_arcs[i].weight;
		marking[post_place] += weight;
	}
}

/**
 * Fire the transition t
 */
int *fire_transition(struct PN * pn, signed int t) {
	// Assure that the given transition exists
	if (t >= pn->nb_transitions) {
		// Error
		return pn->marking;
	}
	
	
	int * new_marking = malloc(sizeof(int) * pn->nb_places);
	
	// Copy a the current marking to a new marking
	for (int i=0; i<pn->nb_places; i++) {
		new_marking[i] = pn->marking[i];
	}
	
	// Fire the transition
	if (t_m_enabled(pn, t)) {
		consume_pre(pn, t, new_marking);

		produce_post(pn, t, new_marking);
	}

	return new_marking;
}

int **fire_all_enabled_transitions(struct PN * pn) {
	int ** all_reachable_marking = malloc(sizeof (int *) * pn->nb_transitions);

	for (int i=0; i<pn->nb_transitions; i++) {
		if (t_m_enabled) {
			int * new_marking = fire_transition(pn, i);
			all_reachable_marking[i] = new_marking;
		} else {
			int * new_marking = malloc(sizeof(int) * pn->nb_places);
			for (int j=0; j<pn->nb_places; j++) {
				new_marking[j] = -1;
			}
		}
	}

	return all_reachable_marking;
}

/**
 * Return if the transition t is M-enabled
 */
int t_m_enabled(struct PN *pn, signed int t) {
	int nb_pre_arcs = pn->pre_conditions[t].nb_pre_arcs;
	int nb_successful_pre = 0;
	
	// Check the precondition of the transition
	for (int j=0; j<nb_pre_arcs; j++) {
		int pre_place = pn->pre_conditions[t].pre_arcs[j].pre_place;
		if (pn->pre_conditions[t].pre_arcs[j].weight <= pn->marking[pre_place]) {
			nb_successful_pre++;
		}
	}
	
	// Return 1 if the pre condition is true, 0 otherwise
	return nb_pre_arcs == nb_successful_pre;
}


/**
 * Return all the M-enabled transition
 */
int* m_enabled(struct PN *pn) {
	int * transitions = malloc(sizeof(int) * pn->nb_transitions);

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

/**
 * Destroy a PN (free memory)
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


/*int main()
{
	int marking[4] = {1,0,1,0};
	struct PN *pn = new_pn(4, 2, marking);
	
	add_pre_arc(pn, 0, 0, 1);
	add_post_arc(pn, 1, 0, 1);
	
	add_pre_arc(pn, 2, 1, 1);
	add_post_arc(pn, 3, 1, 1);
	
	int * en_transitions = m_enabled(pn);
	for (int i=0; i<2; i++) {
		if (en_transitions[i] == -1) {
			break;
		}
		printf("t%i = %i\n", i, en_transitions[i]);
	}
	
	int * new_marking = fire_transition(pn, 0);
	for (int i=0; i<pn->nb_places; i++) {
		printf("%i, ", new_marking[i]);
	}
	printf("\n");
	
	int ** all_marking = fire_all_enabled_transitions(pn);
	for (int i=0; i<pn->nb_transitions; i++) {
		for (int j=0; j<pn->nb_places; j++) {
			if (all_marking[i][j] != -1) {
				printf("%i ", all_marking[i][j]);
			} else {
				continue;
			}
		}
		printf("\n");
	}
		
	destroy_pn(pn);
	
	return 0;
}*/



