#include <assert.h>
#include <string.h>
#include <math.h>

#include "../include/traces.h" 
#include "../include/check.h"

#include "rpn.h"

T_list s2list(char * exp){
    T_list p = NULL;

    int current_int = 0;
    int last_entiers = 0;

    for(int i = strlen(exp)-1; i>=0; i--){
        char ch = exp[i];

        if(ch == ' ' && last_entiers){
            //ajouter a la liste si on casse un int
            T_elt elt = {current_int, RPN_VALEUR};
            p=addNode(elt, p);

            current_int = 0;
            last_entiers = 0;
            continue;
        }

        if(ch == ' '){
            continue;
        }

        if(ch >= 48 && ch <= 57){
            current_int = pow(10, last_entiers)*(ch-48) + current_int;
            last_entiers++;
        }else {
            //ajouter a la liste l'operateur
            T_elt elt = {0, RPN_PLUS};
            p=addNode(elt, p);
            last_entiers = 0;
        }
    }

    if(last_entiers){
        T_elt elt = {current_int, RPN_VALEUR};
        p=addNode(elt, p);

        current_int = 0;
        last_entiers = 0;
    }

    return p;
}

T_elt rpn_eval(char * exp){
    T_stack pile = newStack();

    
}