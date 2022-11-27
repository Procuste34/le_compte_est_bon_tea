#include "elt.h"	// T_elt
#include "list.h"	// T_list, T_node
#include "stack_choix.h"

#ifdef IMPLEMENTATION_CS
#include "stack_cs.h"
#endif

#ifdef IMPLEMENTATION_CD
#include "stack_cd.h"
#endif

#ifdef IMPLEMENTATION_CLD
#include "stack_cld.h"
#endif

T_list s2list(char * exp);
T_elt rpn_eval(char * exp);
