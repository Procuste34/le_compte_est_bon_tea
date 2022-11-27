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
    if(strcmp(exp, "") == 0){ //cas particulier
        T_elt ok = {0, RPN_EXPR_VALIDE};
        return ok;
    }

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
            if(isEmpty(&pile)){
                T_elt elt_erreur = {-1, RPN_EXPR_NON_VALIDE};
                return elt_erreur;
            }
            T_elt a = pop(&pile);

            if(isEmpty(&pile)){
                T_elt elt_erreur = {-1, RPN_EXPR_NON_VALIDE};
                return elt_erreur;
            }
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

    //showStack(&pile);

    //si il reste qu'un int a la fin : c'est une RPN valide, on renvoit le res. (type: RPN_VALEUR)
    //si il reste 2 int : ce sont deux valeurs donc la RPN peut etre valide (type: RPN_EXPR_VALIDE)
    //sinon : pas valide

    T_elt res;

    res = pop(&pile);

    if(isEmpty(&pile)){
        if(res.statut==RPN_VALEUR){
            return res;
        }else{
            T_elt elt_erreur = {-1, RPN_EXPR_NON_VALIDE};
            return elt_erreur;
        }
    }else {
        T_elt res2 = pop(&pile);

        if(res.statut == RPN_VALEUR && res2.statut == RPN_VALEUR && isEmpty(&pile)){
            T_elt elt_ok = {-1, RPN_EXPR_VALIDE};
            return elt_ok;
        }else{
            T_elt elt_erreur = {-1, RPN_EXPR_NON_VALIDE};
            return elt_erreur;
        }
    }
}

//TODO :
//fonction qui verifie si une RPN est valide
//attention, c'est dommage de parcourir 2 fois un RPN (une fois pour voir s'il est valide, une fois pour l'evaluer)
//autant faire une fonction pour les 2 (renvoie un elt special si pas valide, ...)

//rpn_eval peut renvoyer 3 cas différent : elt d'erreur (<-> RPN non valide : RPN_EXPR_NON_VALIDE)
//                                         elt de valeur (<-> RPN valide : RPN_VALEUR)
//                                         elt cas 3 (<-> RPN peut etre valide : RPN_EXP_VALIDE) 