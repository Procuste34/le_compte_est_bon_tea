#include "elt.h"
#include "rpn.h"

#define STACK_NBMAX_ELT 10

#ifdef IMPLEMENTATION_CS
typedef struct {
	int sp; 
	T_elt data[STACK_NBMAX_ELT];
} T_stack;


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