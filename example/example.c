#include "pnC.h"

int main(void) {
	int marking[2] = {1,0}; 
	struct PN * pn = new_pn(2, 1, marking);
	add_pre_arc(pn, 0, 0, 1);
	add_post_arc(pn, 1, 0, 1);
	
	int * marking2 = fire_transition(pn, 0);
	for (int i=0; i<2; i++) printf("%i ",marking2[i]);
}