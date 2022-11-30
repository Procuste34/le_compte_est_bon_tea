#include <assert.h>

#include "traces.h" 
#include "check.h"

#include "elt.h" // T_elt 
#include "list.h" // prototypes 

/*
typedef struct node {
	T_elt data;
	struct node *pNext;
} T_node, * T_list;
*/

static T_node * newNode(T_elt e) {
	// Créer une nouvelle cellule contenant l'élément e

	T_node * pNode; 
	CHECK_IF(pNode = malloc(sizeof(T_node)), NULL, "malloc allocateNode"); 
	pNode->data = e; 
	pNode->pNext = NULL;

	return pNode;
}

T_node * addNode (T_elt e, T_node * n) {
	// Créer une maille (node), la remplir 
	// et l'accrocher en tête d'une liste existante (ou vide)
	// Renvoyer la nouvelle tête

	T_node * pNode; 
	pNode = newNode(e); 
	pNode->pNext = n; 
	return pNode;
}

void showList(T_list l) {
	// Afficher la liste en commençant par sa tête 
	// A faire en itératif 

	while(l != NULL) {
		printf("%s ", toString(l->data));
		l = l->pNext; 
	}
}

void freeList(T_list l) {
	// Libérer la mémoire de toutes les cellules de la liste l 
	// A faire en itératif

	assert(l != NULL); 
	T_node * pAux; 
	// Il faut un pointeur auxiliaire : 
	// on ne doit libérer qu'après avoir enregistré quelque part
	// l'adresse de la maille suivante
	while(l != NULL) {
		//printf("Libération de %s\n", l->data);
		pAux = l->pNext; 
		free(l); 
		l = pAux; 
	}
}

T_elt getFirstElt(T_list l) {
	// Renvoyer l'élément contenu dans la cellule de tête de la liste

	return l->data; 
}

T_list removeFirstNode(T_list l) {
	// Supprimer la tête de la liste 
	// Renvoyer la nouvelle liste privée de sa première cellule

	assert(l!= NULL);	
	T_node * p =l->pNext; 
	free(l); 
	return p; 
}