#include "elt.h"
#include "stack_choix.h"

#ifdef IMPLEMENTATION_CD

typedef struct {
	int sp; 
	int nbMaxElt;
	T_elt * data;
} T_stack;

void emptyStack (T_stack *p);
T_stack newStack(int size);
void showStack (const T_stack * p);

T_elt pop(T_stack *p);
T_elt top(const T_stack *p);
void push(T_elt e, T_stack *p);
int isEmpty (const T_stack * p);
T_stack exampleStack(int n);

void freeStack (T_stack *p);
#endif