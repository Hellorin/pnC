

// Std includes


// Personal includes
#include "pnc.h"

typedef struct {
	int pre_place;
	int transition;
	int weight;
} pre_arc;

typedef struct {
	int transition;
	int post_place;
	int weight;
} post_arc;

typedef struct {
	int nb_pre_arcs;
	pre_arc *pre_arcs;
} pre_conds;

// 
typedef struct {
	post_arc *post_arcs;
	int nb_post_arcs;
} post_conds;

struct PN {
	int nb_places;
	int nb_transitions;

	// P (places)
	int *places;

	// T (transitions)
	int *transitions;
	
	// F = F_1 U F_2 (flow)
	// W = W_1 U W_2 (weight)
	pre_conds *pre_conditions; // F_1 and W_1
	post_conds *post_conditions; // F_2 and W_2
	
	// M (marking)
	int *marking;
};

/**
 * Create a new PN. Gives the number of places, transitions and M0,
 * the initial marking
 */
struct PN *new_pn(int nb_places, int nb_transitions, int marking[]) {
	
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
int add_pre_arc(struct PN *pn, int pre_place, int transition, int weight) {
	assert(pn != NULL);
	assert(pre_place >= 0);
	assert(transition >= 0);

	// Assure that the pre place to which the arc start from exists
	if (pre_place >= pn->nb_places) {
		// Error
		return -1;
	}
	// Assure that the given transition exists
	if (transition >= pn->nb_transitions) {
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
	
	assert(pn->pre_conditions[transition].pre_arcs[nb_before].pre_place == pre_place);
	assert(pn->pre_conditions[transition].pre_arcs[nb_before].transition == transition);
	
	return 0;
}


/**
 * Add a post arc to a transition
 */
int add_post_arc(struct PN *pn, int transition, int post_place, int weight) {
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

	// Ensure that the post condition is correctly added
	assert(pn->post_conditions[transition].post_arcs[nb_before].post_place == post_place);
	assert(pn->post_conditions[transition].post_arcs[nb_before].transition == transition);

	return 0;
}


int* m_enabled(struct PN *pn) {
	
	for (int i=0; i<pn->nb_transitions; i++) {
		int nb_pre_arcs = pn->pre_conditions[i].nb_pre_arcs;
		for (int j=0; j<nb_pre_arcs; j++) {
			int pre_place = pn->pre_conditions[i].pre_arcs[j].pre_place
			if (pn->pre_conditions[i].pre_arcs[j].weight <= pn->marking[pre_place])
		}
		printf("%i\n", nb_pre_arcs);
	}
	int * transitions;

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
		if (pn->pre_conditions[i].pre_arcs != NULL)
			free(pn->pre_conditions[i].pre_arcs);
		free(pn->pre_conditions);
	}

	// Free post conditions
	for (int i=0; i<pn->nb_transitions; i++) {
		int nb_arcs = pn->post_conditions[i].nb_post_arcs;
		
		// Free post arcs
		if (pn->post_conditions[i].post_arcs != NULL)
			free(pn->post_conditions[i].post_arcs);
		free(pn->post_conditions);
	}

	// Free marking
	free(pn->marking);
}


int main()
{
	int marking[3] = {0,0,0};
	struct PN *pn = new_pn(3, 1, marking);
	
	add_pre_arc(pn, 0, 0, 1);
	add_pre_arc(pn, 1, 0, 1);
	
	add_post_arc(pn, 0, 1, 1);
	
	m_enabled(pn);
	
	destroy_pn(pn);
	
	return 0;
}



