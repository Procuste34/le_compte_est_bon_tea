# le_compte_est_bon_tea
 AAP TEA2 : Le Compte est bon, en C (brute force) 

dossier c :
elt.c/elt.h : (fait en TD, et agrémenté) implementation du type T_elt qui 
permet de representer un RPN (grace a la constante dynamique ELT_RPN) 
(Partie 1 du TEA). Definition de la structure d'un rpn avec les champ de 
value et statut. Fonctions toString pour afficher sous forme de string un 
T_elt RPN et genElt pour generer un T_elt RPN arbitraire. Dans elt.h, 
defintion des constantes symboliques, valeurs que peut prendre le champ 
statut d'un RPN.

list.c/list.h : (fait en TD, non modifié) implémentation d'une liste 
chainée

stack_cd.c/stack_cd.h : (fait en TD, non modifié) implémentation d'une 
pile de manière contigue dynamique

stack_cs.c/stack_cs.h : (fait en TD, non modifié) implémentation d'une 
pile de manière contigue statique

stack_cld.c/stack_cld.h : (fait en TD, non modifié) implémentation d'une 
pile grâce à une liste chainée.

rpn.c/rpn.h : implementation des fonctions s2list et rpn_eval. 
Egalement la fonction affiche_operations_rpn pour afficher les 
opérations effectuées lors de l'évaluation d'une RPN, dans le 
format demandé dans l'énoncé (Partie 1 du TEA)

stack_choix.h : choix du type d'implementation pour la pile (cs, cd, ou 
cld)

rec.c : algorithme de recherche à la volée en profondeur d'abord (Partie 2 
du TEA)
