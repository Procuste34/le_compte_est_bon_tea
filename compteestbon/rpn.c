#include <assert.h>
#include <string.h> // strcmp, strlen
#include <math.h> // pow

#include "../include/traces.h" 
#include "../include/check.h"

#include "rpn.h"


/*
convertit une RPN sous forme de string en liste de T_elt
*/
T_list s2list(char * exp){
    T_list p = NULL;

    //on parcourt la string à partir de la fin puisque qu'on ajoute en tête de liste
    //afin que l'ordre des éléments dans la liste finale soit le même que 
    //l'ordre des éléments de la string d'entrée

    int current_int = 0; //nombre en cours de lecture depuis le dernier espace
    int last_entiers = 0; //nombre d'entiers (entre 0 et 9) lus depuis le dernier espace

    for(int i = strlen(exp)-1; i>=0; i--){
        char ch = exp[i];

        if(ch == ' ' && last_entiers){
            //on ajoute à la liste le nombre qui vient d'être lu
            T_elt elt = {current_int, RPN_VALEUR};
            p=addNode(elt, p);

            current_int = 0;
            last_entiers = 0;
            continue;
        }

        if(ch == ' '){
            continue;
        }

        if(ch >= 48 && ch <= 57){ //le caractère lu est un entier entre 0 et 9 : ch-48 est l'entier lu
            //on met à jour current_int et last_entiers
            current_int = pow(10, last_entiers)*(ch-48) + current_int;
            last_entiers++;
        }else { //le caractère lu est un oéprateur
            //on ajoute l'operateur à la liste 
            
            if(ch == '+'){
                T_elt elt = {0, RPN_PLUS};
                p=addNode(elt, p);
            }else if(ch == '-'){
                T_elt elt = {0, RPN_MOINS};
                p=addNode(elt, p);
            }else if(ch == '*'){
                T_elt elt = {0, RPN_FOIS};
                p=addNode(elt, p);
            }else{
                T_elt elt = {0, RPN_DIVISE};
                p=addNode(elt, p);
            }
            
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

/*
évalue une RPN sous forme de string
renvoit un T_elt avec un statut d'erreur si la RPN est fausse syntaxiquement
*/
T_elt rpn_eval(char * exp){
    if(strcmp(exp, "") == 0){ //cas particulier
        T_elt elt = {0, RPN_EXPR_VALIDE};
        return elt;
    }

    #ifndef IMPLEMENTATION_CD
    T_stack pile = newStack();
    #endif

    #ifdef IMPLEMENTATION_CD
    T_stack pile = newStack(20);
    #endif
    
    T_list rpn = s2list(exp);

    //tant que la liste n'est pas vide:
    //   lire l'elt en tete
    //   si operande : empiler
    //   sinon : dépiler 2 fois, faire le cacul, empiler

    //au cours de cet algorithme, si une erreur intervient (exemple : on dépile une pile vide, on divise par 0...)
    //la RPN en cours d'évaluation est fausse et on renvoit un T_elt avec un statut d'erreur

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
                T_elt c = {b.value+a.value, RPN_VALEUR};
                push(c, &pile);
            }else if(elt.statut == RPN_MOINS){

                if(b.value-a.value<0){ //on ne travaille qu'avec des entiers naturels
                    T_elt elt_erreur = {-1, RPN_EXPR_NON_VALIDE};
                    return elt_erreur;
                }

                T_elt c = {b.value-a.value, RPN_VALEUR};
                push(c, &pile);
            }else if(elt.statut == RPN_FOIS){
                T_elt c = {b.value*a.value, RPN_VALEUR};
                push(c, &pile);
            }else if(elt.statut == RPN_DIVISE){
                if(a.value==0){ //division par 0
                    T_elt elt_erreur = {-1, RPN_EXPR_NON_VALIDE};
                    return elt_erreur;
                }

                if(b.value%a.value != 0){ //on ne travaille qu'avec des entiers naturels
                    T_elt elt_erreur = {-1, RPN_EXPR_NON_VALIDE};
                    return elt_erreur;
                }

                T_elt c = {b.value/a.value, RPN_VALEUR};
                push(c, &pile);
            }else{
                T_elt elt_erreur = {-1, RPN_EXPR_NON_VALIDE};
                return elt_erreur;
            }
        }
    }

    //si il reste qu'un int a la fin : c'est une RPN valide, on renvoit le res. (type: RPN_VALEUR)
    //sinon : expr non evaluable mais reste quand meme valide (type : RPN_EXPR_VALIDE)

    T_elt res = pop(&pile);

    if(isEmpty(&pile)){
        if(res.statut==RPN_VALEUR){
            return res;
        }else{
            T_elt elt_erreur = {-1, RPN_EXPR_NON_VALIDE};
            return elt_erreur;
        }
    }else {
        T_elt elt_ok = {-1, RPN_EXPR_VALIDE};
        return elt_ok;
    }
}

/*
évalue une RPN sous forme de string et affiche les opérations faites lors de cette évaluation 
*/
void affiche_operations_rpn(char * exp){
    assert(rpn_eval(exp).statut == RPN_VALEUR);

    #ifndef IMPLEMENTATION_CD
    T_stack pile = newStack();
    #endif

    #ifdef IMPLEMENTATION_CD
    T_stack pile = newStack(20);
    #endif
    
    T_list rpn = s2list(exp);

    while(rpn != NULL){
        T_elt elt = getFirstElt(rpn);
        rpn = removeFirstNode(rpn);

        if(elt.statut == RPN_VALEUR){
            push(elt, &pile);
        }else{
            T_elt a = pop(&pile);
            T_elt b = pop(&pile);

            //on peut faire le calcul avec les champs value
            if(elt.statut == RPN_PLUS){
                T_elt c = {b.value+a.value, RPN_VALEUR};
                push(c, &pile);
                printf("%d + %d = %d\n", b.value, a.value, c.value);

            }else if(elt.statut == RPN_MOINS){
                T_elt c = {b.value-a.value, RPN_VALEUR};
                push(c, &pile);
                printf("%d - %d = %d\n", b.value, a.value, c.value);

            }else if(elt.statut == RPN_FOIS){
                T_elt c = {b.value*a.value, RPN_VALEUR};
                push(c, &pile);
                printf("%d x %d = %d\n", b.value, a.value, c.value);

            }else if(elt.statut == RPN_DIVISE){
                T_elt c = {b.value/a.value, RPN_VALEUR};
                push(c, &pile);
                printf("%d / %d = %d\n", b.value, a.value, c.value);
            }
        }
    }
}