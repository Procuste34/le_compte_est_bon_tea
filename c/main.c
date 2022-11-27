#include <stdio.h>
#include <assert.h>
#include <string.h> //strcat, strcpy, strcmp

#include "../include/traces.h" 
#include "../include/check.h" 

#include "elt.h"
#include "list.h"

#include "rpn.h"

#define NB_CARTONS_INITIAL 6

#define A_TROUVER 859//631//945//219 //945
#define C1 3//2// 5//8 //5
#define C2 5// 9//3 //9
#define C3 7// 7//10 //7
#define C4 9// 4//7 //4
#define C5 25// 1//4 //1
#define C6 50// 6//2 //6

int a_trouver;
int best_diff;
char * best_rpn_string = "";

void showTab(int tab[], int len){
	for(int i=0; i<len; i++){
		printf("%d\n", tab[i]);
	}
}

void appel_rec(char * rpn_string, int cartons_restants[], int len_cartons_restants){
	//printf("--------- RPN : '%s' ---------\n", rpn_string);

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
		//char * str = malloc(sizeof(char) * (int)log10(cartons_restants[i]));
		char * str;
		CHECK_IF(str = malloc(sizeof(char) * 3), NULL, "malloc");

		if(strcmp(rpn_string, "") == 0){
			sprintf(str, "%d", cartons_restants[i]);
		}else {
			sprintf(str, " %d", cartons_restants[i]);
		}
		
		//concat
		//char* rpn_new = malloc(strlen(rpn_string) + 10*(int)log10(cartons_restants[i])); /* (should check the return value ...) */
		char * rpn_new;
		CHECK_IF(rpn_new = malloc(strlen(rpn_string) + 10*3), NULL, "malloc");
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

		//free(str);
		//free(rpn_new);
	}

	if(res.statut == RPN_VALEUR){
		return;
	}

	//pour chaque operateur : appel rec
	for(int i = 0; i<4; i++){ //4 opérateurs
		char * str = "";

		switch (i)
		{
		case 0:
			str = " +";
			break;
		case 1:
			str = " -";
			break;
		case 2:
			str = " *";
			break;
		default:
			str = " /";
			break;
		}

		//char* rpn_new = malloc(strlen(rpn_string) + 10*3); /* (should check the return value ...) 3 = 2 espaces + 1 opérateur */
		char* rpn_new;
		CHECK_IF(rpn_new = malloc(strlen(rpn_string) + 10*3), NULL, "malloc");
		strcpy(rpn_new, rpn_string);
		strcat(rpn_new, str);

		appel_rec(rpn_new, cartons_restants, len_cartons_restants);

		//free(rpn_new);
	}

	//TODO : free les strings
	//TODO : 2 fois le meme carton pris...
}

int main(int argc, char ** argv) {
	printf("***********************\n");

	assert(argc==NB_CARTONS_INITIAL+2);

	int cartons[NB_CARTONS_INITIAL] = {0};
	for(int i = 0; i<NB_CARTONS_INITIAL; i++){
		cartons[i] = (int)strtol(argv[i+1], NULL, 10);
	}
	a_trouver = (int)strtol(argv[7], NULL, 10);
	best_diff = a_trouver;

	appel_rec("", cartons, NB_CARTONS_INITIAL);

	printf("%d\n", best_diff);
	printf("%s\n", best_rpn_string);

	affiche_operations_rpn(best_rpn_string);

	return 0;
}






//sources : https://stackoverflow.com/questions/4176326/arguments-to-main-in-c
//https://stackoverflow.com/questions/9748393/how-can-i-get-argv-as-int