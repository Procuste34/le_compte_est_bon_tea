#ifndef _ELT_H_
	#define _ELT_H_ // prévient les includes multiples

	/////////////////////////////////////////////////////////////////////////
	// CHOISIR ICI CE QUE REPRESENTE LE TYPE T_elt 
	//#define ELT_CHAR		// un caractère ?
	//#define ELT_INT		// un entier (choix par défaut) ?
	//#define ELT_STRING	// une chaîne de caractères ?
	#define ELT_RPN
	/////////////////////////////////////////////////////////////////////////


	////////////// Constantes symboliques pour le champ statut du type ELT_RPN
	#define RPN_EXPR_VALIDE 0 //pour un RPN qui est valide mais ne donne pas un résultat lors de son évaluation (exemple : 1 2)
	#define RPN_EXPR_NON_VALIDE 1 //pour un RPN qui a une syntaxe fausse (exemple : 1 +)

	#define RPN_VALEUR 2 //pour un RPN qui, une fois évalué, donne un résultat (exemple : 1 2 +)
	#define RPN_PLUS 3
	#define RPN_MOINS 4
	#define RPN_FOIS 5
	#define RPN_DIVISE 6
	//////////////////////////////////////////////////////////////////////////

	#if ! defined(ELT_CHAR) && ! defined(ELT_INT) && ! defined(ELT_STRING) && ! defined(ELT_RPN)
	#define ELT_INT
	#endif

	#ifdef ELT_CHAR
	typedef char T_elt;
	#endif

	#ifdef ELT_INT
	typedef int T_elt; 
	#endif

	#ifdef ELT_STRING
	typedef char * T_elt; 
	#endif

	#ifdef ELT_RPN
	typedef struct {
		int value;
		char statut;
	} T_elt;
	#endif

	// valable pour tous les types de T_elt 
	char * toString(T_elt e); 
	T_elt genElt(void); 
#endif 

