#ifndef __tree_h__
#define __tree_h__

#include <stdbool.h>

#include "symbol.h"

// дерево выражения
typedef struct _TN {
    symbol t;		//значение узла
    struct _TN* l;	//указатель на левое поддерево
    struct _TN* r;	//указатель на правое поддерево
} TN;

#endif
