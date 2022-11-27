#include <stdio.h>
#include <assert.h>
#include <string.h> //pour concat strcat
#include <math.h> //pour log10

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"
#include "list.h"

#include "rpn.h"

#define A_TROUVER 945
#define C1 5
#define C2 9
#define C3 7
#define C4 4
#define C5 1
#define C6 6

int a_trouver = A_TROUVER;

int best_diff = A_TROUVER;
char * best_rpn_string = "";

void appel_rec(char * rpn_string, int cartons_restants[], int len_cartons_restants){
	//printf("--------- RPN : '%s' ---------", rpn_string);

	T_elt res = rpn_eval(rpn_string);

	if(res.statut == RPN_EXPR_NON_VALIDE){
		//printf("pas valide\n");
		return;
	}else{
		//printf("\n");
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
	for(int i=0; i<len_cartons_restants; i++){
		//printf("%d\n", cartons_restants[i]);

		//construire la nouvelle RPN par concat de l'actuelle et de cartons_restants[i]

		//convertir cartons_restants[i] en string
		char * str = malloc(sizeof(char) * (int)log10(cartons_restants[i]));
		sprintf(str, " %d", cartons_restants[i]);
		
		//concat
		char* rpn_new = malloc(strlen(rpn_string) + (int)log10(cartons_restants[i])); /* (should check the return value ...) */
		strcpy(rpn_new, rpn_string);
		strcat(rpn_new, str);

		//construire cartons_restants_2, ie cartons_restants sans cartons_restants[i]
		int cartons_restants_2[len_cartons_restants-1];
		int compteur = 0;
		for(int j=0; j<len_cartons_restants; j++){
			if(j != i){
				cartons_restants_2[compteur] = cartons_restants[j];
				compteur++;
			}
		}

		//lancer l'appel rec
		appel_rec(rpn_new, cartons_restants_2, len_cartons_restants-1);
	}

	//pour chaque operateur : appel rec
	for(int i = 0; i<4; i++){ //4 opérateurs
		char * str = "";
		if(i == 0){
			str = " +";
		}else if(i == 1){
			str = " -";
		}else if(i == 2){
			str = " *";
		}else {
			str = " /";
		}

		char* rpn_new = malloc(strlen(rpn_string) + 3); /* (should check the return value ...) 3 = 2 espaces + 1 opérateur */
		strcpy(rpn_new, rpn_string);
		strcat(rpn_new, str);

		appel_rec(rpn_new, cartons_restants, len_cartons_restants);
	}

	//TODO : free les strings
	//TODO : switch plutot que des if?
}

int main(int argc, char ** argv) {
	printf("***********************\n");
	/*
	char * expression = "1 2 + 4 + 5";
	T_elt elt = rpn_eval(expression);

	if(elt.statut == RPN_EXPR_NON_VALIDE){
		printf("RPN NON VALIDE");
	}
	*/

	//todo : lancer l'appel recursif, avec rpn_string="", cartons_restants=[les cartons complets]

	/*
	char * mon_rpn_1 = "1 2";

	char* name = "hello";
	char* extension = " 1 ";


	char* name_with_extension = malloc(strlen(name)+1+4); // (should check the return value ...)
	
	//strcpy(name_with_extension, name); //copy name into the new var
	//strcat(name_with_extension, extension); //add the extension
	printf("%s\n", name_with_extension);

	char * str = malloc(sizeof(char)*(int)log10(42));
	sprintf(str, " %d ", 42);
	printf("%s\n", str);

	free(name_with_extension);
	free(str);


	printf("EEEEEEEEEEEEEEEE\n");

	int cartons_restants[5] = {3, 6, 1, 4, 5};
	int i = 1;

	int cartons_restants_2[5-1];
	int compteur = 0;
	for(int j=0; j<5; j++){
		if(j != i){
			cartons_restants_2[compteur] = cartons_restants[j];
			compteur++;
		}
	}

	printf("cartons_restants :\n");
	for(int i=0; i<5; i++){
		printf("%d\n", cartons_restants[i]);
	}

	printf("cartons_restants_2 :\n");
	for(int i=0; i<4; i++){
		printf("%d\n", cartons_restants_2[i]);
	} */

	//printf("%d\n", strcmp("aleex", "alex"));

	//T_elt reponse;
	//reponse = rpn_eval("");
	//printf("%d\n", reponse.statut);



	printf("HHHHHHHHHHHHHHHHHHHHHHHHHH\n");

	int cartons_restants[6] = {C1, C2, C3, C4, C5, C6};
	appel_rec("1", cartons_restants, 6);

	printf("%d\n", best_diff);
	printf("%s\n", best_rpn_string);

	return 0;
}





