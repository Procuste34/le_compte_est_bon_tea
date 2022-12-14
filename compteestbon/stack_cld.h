#include "elt.h"	// T_elt
#include "list.h"	// T_list, T_node
#include "stack_choix.h"

#ifdef IMPLEMENTATION_CLD

typedef T_node * T_stack;

void emptyStack (T_stack *p);
T_stack newStack(void);
void showStack (const T_stack * p);

T_elt pop(T_stack *p);
T_elt top(const T_stack *p);
void push(T_elt e, T_stack *p);
int isEmpty (const T_stack * p);
T_stack exampleStack(int n);

void freeStack (T_stack *p);
#endif
