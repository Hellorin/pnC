#include "pnC.h"

int main(void) {
    // Create the initial marking
    int marking[2] = {1,0};

    // Create the Petri net with the initial marking,
    // 2 places and 1 transition
    struct PN * pn = new_pn(2, 2, marking);

    // Add a pre arc to the transition 0 of the Petri net pn of weight 1
    add_pre_arc(pn, 0, 0, 1);
    // Add a post arc to the transition 0 of the Petri net pn of weight 1
    add_post_arc(pn, 1, 0, 1);

    printf("Marking before firing the transition t0\n");
    for (int i=0; i<2; i++) printf("p%i: %i\n", i, get_marking(pn)[i]);
    printf("\n");

    // Fire the transition 0
    int * marking2 = fire_transition(pn, 0);
    set_marking(pn, marking2, 2);
    printf("\n");

    printf("Marking after firing the transition t0\n");
    for (int i=0; i<2; i++) printf("p%i: %i\n", i, get_marking(pn)[i]);

    printf("\n");
}
