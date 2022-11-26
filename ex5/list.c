#include <assert.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

//#define DEBUG
#include "../include/check.h"

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
	CHECK_IF(pNode = (T_node *) malloc(1 * sizeof(T_node)), NULL, "malloc newNode");
	pNode->data=e;
	pNode->pNext=NULL;

	return pNode;
}

T_node * addNode (T_elt e, T_node * n) {
	// Créer une maille (node), la remplir 
	// et l'accrocher en tête d'une liste existante (ou vide)
	// Renvoyer la nouvelle tête
 
	T_node * pNode;
	pNode = newNode(e);
	pNode->pNext=n;

	return pNode;
}

void showList(T_list l) {
	// Afficher la liste en commençant par sa tête 
	// A faire en itératif 

	if (l==NULL) {
		printf("Pile vide !\n"); // pile vide ! 
		return;
	}
 
	while(l != NULL) {
		printf("%s\n", toString(l->data));
		l=l->pNext;
	}
}

void freeList(T_list l) {
	// Libérer la mémoire de toutes les cellules de la liste l 
	// A faire en itératif

	T_list lAux;

	assert(l != NULL);
	while(l != NULL){
		lAux=l->pNext;
		free(l);
		l=lAux;
	}
}

T_elt getFirstElt(T_list l) {
	// Renvoyer l'élément contenu dans la cellule de tête de la liste

	T_elt e; 
	e=l->data;

	return e; 
}

T_list removeFirstNode(T_list l) {
	// Supprimer la tête de la liste 
	// Renvoyer la nouvelle liste privée de sa première cellule

	T_list lAux;
	assert(l != NULL);
	lAux=l->pNext;
	free(l);

	return NULL; 
}

// A produire en version récursive (+ tard dans le sujet)

void showList_rec(T_list l) {
	// Afficher la liste en commençant par sa tête 
	// A faire en récursif 

	TOUCH_HERE("Ben là, c'est à vous ! \n");
}

void showList_inv_rec(T_list l) {
	// Afficher la liste en commençant par sa queue 
	// A faire en récursif 

	TOUCH_HERE("Ben là, c'est à vous ! \n");
}

void freeList_rec(T_list l) {
	// Libérer la mémoire de toutes les cellules de la liste l 
	// A faire en récursif

	TOUCH_HERE("Ben là, c'est à vous ! \n");
}

