#include <stdio.h>
#include <assert.h>

//#define CLEAR2CONTINUE
#include "../include/traces.h" 

// C'est dans le fichier elt.h qu'on doit choisir l'implémentation des T_elt
#include "elt.h"
#include "list.h"

#include "stack_cs.h"
#include "stack_cd.h"
#include "stack_cld.h"

#include "rpn.h"

int main(int argc, char ** argv) {
	printf("***********************\n");

	char * expression = "1 2 +";
	T_list p = s2list(expression);

	showList(p);

	return 0;
}







