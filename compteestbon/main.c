#include <assert.h>

#include "../include/traces.h" 
#include "../include/check.h" 

#include "rec.h"

#define NB_CARTONS_INITIAL 6

int main(int argc, char ** argv){
	assert(argc==NB_CARTONS_INITIAL+2);

	//on recupere les arguments passés lors de l'appel du programme dans argv
	int cartons[NB_CARTONS_INITIAL] = {0};
	for(int i = 0; i<NB_CARTONS_INITIAL; i++){
		cartons[i] = (int)strtol(argv[i+1], NULL, 10);
	}
	int cible = (int)strtol(argv[7], NULL, 10); //strtol pour convertir une string en long

	set_cible(cible);
	parcours_profondeur("", cartons, NB_CARTONS_INITIAL);
	affiche_rpn();

	return 0;
}