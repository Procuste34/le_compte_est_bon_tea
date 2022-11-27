#include <stdio.h>
#include <assert.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"
#include "list.h"

#include "rpn.h"

#define A_TROUVER 566

int a_trouver = A_TROUVER;

int best_diff = A_TROUVER;
char * best_rpn_string = "";

void appel_rec(char * rpn_string, int cartons_restants[]){
	T_elt res = rpn_eval(rpn_string);

	if(res.statut == RPN_EXPR_NON_VALIDE){
		return;
	}
	if(res.statut == RPN_VALEUR){
		if(abs(res.value - a_trouver) < best_diff){
			best_diff = abs(res.value - a_trouver);
			best_rpn_string = rpn_string;
		}
		if(best_diff==0){
			return;
		}
	}

	//pour chaque carton restant : appel rec
	for(int i=0; i<len(cartons_restants); i++){
		printf("%d\n", cartons_restants[i]);
	}


	//pour chaque operateur : appel rec




}

int main(int argc, char ** argv) {
	printf("***********************\n");

	char * expression = "1 2 + 4 + 5";
	T_elt elt = rpn_eval(expression);

	if(elt.statut == RPN_EXPR_NON_VALIDE){
		printf("RPN NON VALIDE");
	}

	//todo : lancer l'appel recursif, avec rpn_string="", cartons_restants=[les cartons complets]

	return 0;
}





