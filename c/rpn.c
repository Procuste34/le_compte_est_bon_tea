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
    T_list rpn = s2list(exp);

    //tant que la liste n'est pas vide
    //  lire l'elt en tete
    //  si operande : empiler
    //  sinon : dépiler 2 fois, faire le cacul, empiler

    while(rpn != NULL){
        T_elt elt = getFirstElt(rpn);
        rpn = removeFirstNode(rpn);

        if(elt.statut == RPN_VALEUR){
            push(elt, &pile);
        }else{
            T_elt a = pop(&pile);
            T_elt b = pop(&pile);

            if(a.statut != RPN_VALEUR || b.statut != RPN_VALEUR){
                T_elt elt_erreur = {-1, RPN_EXPR_NON_VALIDE};
                return elt_erreur;
            }

            //on peut faire le calcul avec les champs value
            if(elt.statut == RPN_PLUS){
                T_elt c = {a.value+b.value, RPN_VALEUR};
                push(c, &pile);
            }else if(elt.statut == RPN_MOINS){
                T_elt c = {a.value-b.value, RPN_VALEUR};
                push(c, &pile);
            }else if(elt.statut == RPN_FOIS){
                T_elt c = {a.value*b.value, RPN_VALEUR};
                push(c, &pile);
            }else if(elt.statut == RPN_DIVISE){
                T_elt c = {a.value/b.value, RPN_VALEUR};
                push(c, &pile);
            }else{
                T_elt elt_erreur = {-1, RPN_EXPR_NON_VALIDE};
                return elt_erreur;
            }
        }
    }

    showStack(&pile);

    T_elt elt = {0, 0};
    return elt;
}