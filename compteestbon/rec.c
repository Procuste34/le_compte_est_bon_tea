#include <stdio.h>
#include <assert.h>
#include <string.h> //strcat, strcpy, strcmp

#include "../include/traces.h" 
#include "../include/check.h" 

#include "elt.h"
#include "rpn.h"
#include "rec.h"

int a_trouver;
int best_diff;
char * best_rpn_string = "";

void set_cible(int cible){
	//a appeler avant de lancer le parcours en profondeur

    a_trouver = cible;
    best_diff = cible;
}

void affiche_rpn(){
	//a appeler après le parcours en profondeur

    //printf("RPN trouve (best_diff=%d) : %s\n", best_diff, best_rpn_string);
	affiche_operations_rpn(best_rpn_string);
}

void parcours_profondeur(char * rpn_string, int cartons_restants[], int len_cartons_restants){
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

	//si la RPN rpn_string donne un résultat, alors lui rajouter un opérateur donnera
	//nécessairement une RPN avec une syntaxe fausse (exemple : 1 2 +)
	//donc il est dans ce cas inutile de lancer les appels récursifs
	if(res.statut != RPN_VALEUR){
		//pour chaque operateur : appel rec
		for(int i = 0; i<4; i++){
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

			//portion de code pour concatener rpn_string et str
			char* rpn_new;
			CHECK_IF(rpn_new = malloc(strlen(rpn_string) + strlen(str) + 1), NULL, "malloc new string");
			strcpy(rpn_new, rpn_string);
			strcat(rpn_new, str);

			parcours_profondeur(rpn_new, cartons_restants, len_cartons_restants);
		}
	}

	//pour chaque carton restant : appel rec
	for(int i=0; i<len_cartons_restants; i++){

		//construire la nouvelle RPN par concat de l'actuelle et de cartons_restants[i]

		//convertir cartons_restants[i] en string
		char * str;
		CHECK_IF(str = malloc(sizeof(char) * 3), NULL, "malloc new string");
		sprintf(str, " %d", cartons_restants[i]);
		
		//concat
		char * rpn_new;
		CHECK_IF(rpn_new = malloc(strlen(rpn_string) + 3), NULL, "malloc new string"); //cartons_restants[i] s'écrit sur 3 caractères
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

		parcours_profondeur(rpn_new, cartons_restants_2, len_cartons_restants-1);
	}
}