#include <assert.h>

#include "../include/traces.h" 
#include "../include/check.h"

#include "rpn.h"

T_list s2list(char * exp){
    T_list p = NULL;

    T_elt mon_elt = {1, 0};
    T_elt mon_elt2 = {69, 0};

    p=addNode(mon_elt, p);
    p=addNode(mon_elt2, p);

    return p;


}

