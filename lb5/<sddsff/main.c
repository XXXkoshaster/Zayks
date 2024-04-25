#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "symbol.h"
#include "stack.c"
#include "tree.h"

int op_priority(char op) {
    switch(op) {
        case OP_MINUS:
        case OP_PLUS:
            return 1;
        case OP_MULT:
        case OP_DIVIDE:
            return 2;
        case OP_POW:
            return 3;
        case OP_UNARY_MINUS:
            return 4;
    }
    return -1;
}


OP_ASSOC op_assoc(OP op) {
    switch(op) {
        case OP_MINUS:
        case OP_PLUS:
        case OP_MULT:
        case OP_DIVIDE:
            return ASSOC_LEFT;
        case OP_UNARY_MINUS:
        case OP_POW:
            return ASSOC_RIGHT;
    }
    return -1;
}

char op_to_char(OP op) {
    switch(op) {
        case OP_MINUS:
        case OP_PLUS:
        case OP_MULT:
        case OP_DIVIDE:
        case OP_POW:
            return op;
        case OP_UNARY_MINUS:
            return '-';
    }
    return -1;
}

bool is_space(int c) {
    return (c == ' ') || (c == '\n') || (c == '\t');
}

int next_char() {
    int c;
    while(is_space(c = getchar())) {} 
    return c;
}

bool next_symbol(symbol *out) {
    static symb_TYPE prev_type = symb_NONE;

    int c = next_char();
    if(c == EOF) {
        out->type = symb_NONE; 
        prev_type = symb_NONE; 
        return false; 
    } else if(c == '.' || (c >= '0' && c <= '9')) {
        ungetc(c, stdin);
        out->type = symb_NUMBER;
        scanf("%f", &(out->data.number)); 
    } else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        ungetc(c, stdin);
        out->type = symb_VAR;
		scanf("%[a-zA-Z]", out->data.var);
    } else if(c == '(') {
        out->type = symb_LEFT_BR;
    } else if(c == ')') {
        out->type = symb_RIGHT_BR;
    } else if(c == '+' || c == '*' || c == '/' || c == '^') {
        out->type = symb_OP;
        out->data.op = c;
    } else if(c == '-') {
        out->type = symb_OP;
        if(prev_type == symb_OP || prev_type == symb_NONE) {
            out->data.op = OP_UNARY_MINUS;
        } else {
            out->data.op = OP_MINUS;
        }
    } else {
        out->type = symb_NONE;
        out->data.c = c;
    }
    
    prev_type = out->type;
    
    return true;
}

bool build_tree(TN **tree, STACK *rev) {
    if(stack_empty(rev)) {
        return false;
    }
    symbol t = stack_pop(rev);
    (*tree) = (TN*)malloc(sizeof(TN));
    (*tree)->t = t;

    bool res = true;
    if(t.type == symb_OP) {
        if(t.data.op == OP_UNARY_MINUS) {
            (*tree)->l = NULL;
            res = res && build_tree(&((*tree)->r), rev);
        } else {
            res = res && build_tree(&((*tree)->r), rev);
            res = res && build_tree(&((*tree)->l), rev);
        }
    }
    return res;
}

void print_tree(TN *tree, int lev) {
	if (tree == NULL) return;

	if(tree->t.type == symb_OP)
	{
		print_tree(tree->r, lev+1);
	}
    for(int i = 0; i < lev; i++) {
        printf("\t");
    }
    switch(tree->t.type) {
        case symb_NUMBER:
            printf("%.2lf\n", tree->t.data.number);
            break;
        case symb_VAR:
            printf("%s\n", tree->t.data.var);
            break;
        case symb_OP:
            if(tree->t.data.op == OP_UNARY_MINUS) {
                printf("-\n");
                print_tree(tree->r, lev+1);
            } else {
                printf("%c\n", op_to_char(tree->t.data.op));
            }
            break;
        default:
            fprintf(stderr, "This symlbol must not be in the tree already");
            return;
    }
    if(tree->t.type == symb_OP)
	{
		print_tree(tree->l, lev+1);
	}

}

void print_expr(TN *tree) {
    switch(tree->t.type) {
        case symb_NUMBER:
            printf("%.2lf", tree->t.data.number);
            break;
        case symb_VAR:
            printf("%s", tree->t.data.var);
            break;
        case symb_OP:
            if(tree->t.data.op == OP_UNARY_MINUS) {
                printf("-");
                print_expr(tree->r);
            } else {
                if(tree->l->t.type == symb_OP && op_priority(tree->t.data.op) > op_priority(tree->l->t.data.op))
                {
                	printf("(");
                	print_expr(tree->l);
                	printf(")");
				}
				else
				{
					print_expr(tree->l);
				}
                printf("%c", op_to_char(tree->t.data.op));
				if(tree->r->t.type == symb_OP && op_priority(tree->t.data.op) > op_priority(tree->r->t.data.op))
                {
                	printf("(");
                	print_expr(tree->r);
                	printf(")");
				}
				else
				{
					print_expr(tree->r);
				}
            }
            break;
        default:
            fprintf(stderr, "This symlbol must not be in the tree already");
            return;
    }
}
// Функция для печати одного элемента типа symbol
void print_symbol(const symbol* s) {
    if (s == NULL) return;

    switch (s->type) {
        case symb_NUMBER:
            printf("Число: %.2f\n", s->data.number);
            break;
        case symb_VAR:
            printf("Переменная: %s\n", s->data.var);
            break;
        default:
            printf("Неизвестный тип\n");
    }
}

void print_arrays(symbol* numerator[], int numSize, symbol* denominator[], int denSize) {
    printf("Числитель:\n");
    for (int i = 0; i < numSize; ++i) {
        if (numerator[i] != NULL) { // Проверяем, не является ли элемент NULL
            print_symbol(numerator[i]);
        }
    }

    printf("\nЗнаменатель:\n");
    for (int i = 0; i < denSize; ++i) {
        if (denominator[i] != NULL) { // Проверяем, не является ли элемент NULL
            print_symbol(denominator[i]);
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int compareSymbols(const symbol* s1, const symbol* s2) {
    // Проверяем, что типы символов совпадают
    if (s1->type != s2->type) {
        return 0; // Типы символов различны, символы не равны
    }

    // Теперь сравниваем значения в зависимости от типа
    switch (s1->type) {
        case symb_NUMBER:
            // Для чисел сравним их значения
            return (s1->data.number == s2->data.number);

        case symb_VAR:
            // Для переменных сравним их имена
            return (strcmp(s1->data.var, s2->data.var) == 0);

        default:
            // Если тип не symb_VAR и не symb_NUMBER, считаем символы не равными
            return 0;
    }
}

TN *findParent(TN* root, TN* child) {
    // Если корневой узел равен NULL или мы ищем родителя корневого узла
    if (root == NULL || root == child) {
        return NULL;
    }

    // Если один из дочерних узлов равен искомому узлу, возвращаем текущий узел как родителя
    if (root->l == child || root->r == child) {
        return root;
    }

    // Ищем родителя рекурсивно в левом поддереве
    TN* leftSearch = findParent(root->l, child);
    if (leftSearch != NULL) {
        return leftSearch;
    }

    // Ищем родителя рекурсивно в правом поддереве
    return findParent(root->r, child);
}

TN *findTN(TN *root, symbol key)
{
    if (root == NULL)
        return NULL;
    
    if (compareSymbols(&(root->t), &key))
        return root;

    TN *found = findTN(root->l, key);
    if (found != NULL)
        return found;
    
    return findTN(root->r, key);  
}

void deletNode(TN *parent, TN *node) {
    if (node == NULL) return;

    // Рекурсивно удаляем потомков перед удалением узла
    if (node->l != NULL) {
        deletNode(node, node->l);
    }
    if (node->r != NULL) {
        deletNode(node, node->r);
    }

    // Обнуляем указатель в родительском узле
    if (parent != NULL) {
        if (parent->l == node) {
            parent->l = NULL;
        } else if (parent->r == node) {
            parent->r = NULL;
        }
    }

    free(node); // Освобождаем память, занимаемую узлом
}



void collectTerms(TN *root, symbol *terms[], int *termsSize) {
    if (root == NULL) return;

    // Проверяем, является ли узел числом или переменной
    if (root->t.type == symb_NUMBER) {
        terms[*termsSize] = &root->t;
        (*termsSize)++; // Исправлено на number
    } else if (root->t.type == symb_VAR) {
        terms[*termsSize] = &root->t; // Исправлено на var
        (*termsSize)++;
    } else {
        // Рекурсивно проходим по поддеревьям
        collectTerms(root->l, terms, termsSize);
        collectTerms(root->r, terms, termsSize);
    }
}


// Функция для упрощения дерева, вызываемая из main или другой функции
void simplify(TN* root, symbol *numerator[], symbol *denominator[]) {
    int numSize = 0;
    int denSize = 0;
    TN *tmp = root;
    // Собираем термины для числителя из левого поддерева
    collectTerms(tmp->l, numerator, &numSize);

    // Собираем термины для знаменателя из правого поддерева
    collectTerms(tmp->r, denominator, &denSize);
    print_arrays(numerator, numSize, denominator, denSize);

    // Упрощение дроби, сокращая одинаковые элементы
    TN *finded;
    TN *parent;
    for (int i = 0; i < numSize; i++) {
        for (int j = 0; j < denSize; j++) {
            if (numerator[i] != NULL && denominator[j] != NULL && compareSymbols(numerator[i], denominator[j])) {
                
                finded = findTN(root->l, *numerator[i]);
                if (finded != NULL) {
                    parent = findParent(root, finded);
                    deletNode(parent, finded);
                }
                
                finded = findTN(root->r, *denominator[j]);
                if (finded != NULL) {
                    parent = findParent(root, finded);
                    deletNode(parent, finded);
                }
                numerator[i] = NULL;
                denominator[j] = NULL;
            }
        }
    }
}

int main() {
	STACK *s, *rev;
    symbol t;
    
    s = stack_create();
    rev = stack_create();
    
    while(next_symbol(&t)) {
        switch(t.type) {
            case symb_NONE:
                fprintf(stderr, "Error: symbol %c not recognized\n", t.data.c);
                return 1;
                
            case symb_OP:
                for(;;) {
                    if(stack_empty(s)) break;
                    symbol top = stack_peek(s);
                    if(top.type != symb_OP) break;
                    
                    if((op_assoc(t.data.op) == ASSOC_LEFT && op_priority(t.data.op) <= op_priority(top.data.op))
                    || (op_assoc(t.data.op) == ASSOC_RIGHT && op_priority(t.data.op) < op_priority(top.data.op))
                    ) {
                        stack_pop(s);
                        stack_push(rev, top);
                    } else {
                        break;
                    }
                }

                stack_push(s, t);
                break;
                
            case symb_NUMBER:
            case symb_VAR:
                stack_push(rev, t);
                break;

            case symb_LEFT_BR:
                stack_push(s, t);
                break;
                
            case symb_RIGHT_BR:
                for(;;) {
                    if(stack_empty(s)) {
                        fprintf(stderr, "Error: closing bracket hasn't pair");
                        return 2;
                    }
                    symbol top = stack_peek(s);
                    if(top.type == symb_LEFT_BR) {
                        stack_pop(s);
                        break;
                    } else {
                        stack_pop(s);
                        stack_push(rev, top);
                    }
                }
                break;
        }
    }
    
    while(!stack_empty(s)) {
        t = stack_pop(s);
        if(t.type == symb_LEFT_BR) {
            fprintf(stderr, "Error: opening bracket hasn't pair");
            return 2;
        }
        stack_push(rev, t);
    }
    

    // Build tree
    if(stack_empty(rev)) {
        fprintf(stderr, "Error: expression is empty");
        return 3;
    }

    TN *root = NULL;
    if(!build_tree(&root, rev)) {
        fprintf(stderr, "Error while building tree: don't find one of operands");
        return 4;
    }
    if(!stack_empty(rev)) {
        fprintf(stderr, "Error while building tree: extra operands or opetators");
        return 4;
    }

	print_tree(root, 0);

    symbol *numerator[100];
    symbol *denominator[100];
    simplify(root, numerator, denominator);
    print_tree(root, 0);
    print_expr(root);
    printf("\n");
}

