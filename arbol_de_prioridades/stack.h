#ifndef Stack_h
#define Stack_h

#include "list.h"

typedef List Stack;

#define stackCreate()  createList()

#define stackPop(stack)  popFront(stack)

#define stackPush(stack, data)  pushFront(stack, data)

#define stackTop(stack)  firstList(stack)

#define stackClean(stack)  cleanList(stack)

#endif /* Stack_h*/
