#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "symbol.h"
#include "stack.h"
#include "tree.h"

void destructor(STACK *a, STACK *b) {
	stack_delete(a);
	stack_delete(b);
}

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
    //return -1;
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

OP int_to_op(int i) {
	switch(i){
		case '+': return OP_PLUS;
		case '*': return OP_MULT;
		case '/': return OP_DIVIDE;
		case '^': return OP_POW;
	}
}

bool is_space(int c) {
    return (c == ' ') || (c == '\t');
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
        out->type = symb_EOF; 
        prev_type = symb_NONE; 
        return false; 
	} else if(c == '\n'){
		out->type = symb_ENDL; 
        prev_type = symb_NONE; 
        return false; 
    } else if(c == '.' || (c >= '0' && c <= '9')) {
        ungetc(c, stdin);
        out->type = symb_NUMBER;
        scanf("%f", &(out->data.number));
    } else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        ungetc(c, stdin);
        out->type = symb_VAR;
        scanf("%[^ \n\t+-*/^()]", out->data.var);
    } else if(c == '(') {
        out->type = symb_LEFT_BR;
    } else if(c == ')') {
        out->type = symb_RIGHT_BR;
    } else if(c == '+' || c == '*' || c == '/' || c == '^') {
        out->type = symb_OP;
        out->data.op = int_to_op(c);
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
                printf("(");
                print_expr(tree->l);
                printf("%c", op_to_char(tree->t.data.op));
                print_expr(tree->r);
                printf(")");
            }
            break;
        default:
            fprintf(stderr, "This symlbol must not be in the tree already\n");
            return;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Функция для печати одного элемента типа symbol
void print_symbol(symbol* s) {
    if (s == NULL) 
        return;

    if (s->type == symb_NUMBER)
        printf("Константа: %.2f\n", s->data.number);
    else if (s->type == symb_VAR)
        printf("Переменная: %s\n", s->data.var);
    else
        printf("Неизвестный тип\n");
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int compareSymbols(symbol* s1, symbol* s2) {
    // Проверяем, что типы символов совпадают
    if (s1->type != s2->type) {
        return 0; // Типы символов различны, символы не равны
    }

    // Теперь сравниваем значения в зависимости от типа
    if (s1->type == symb_NUMBER)
        // Для чисел сравним их значения
        return (s1->data.number == s2->data.number);
    else if (s1->type == symb_VAR)
        // Для переменных сравним их имена
        return (strcmp(s1->data.var, s2->data.var) == 0);
    else
        // Е<сли тип не symb_VAR и не symb_NUMBER, считаем символы не равными
        return 0;
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

    // Функция для создания узла с числом 1.0
TN *create_one_node() {
    TN *one = (TN *)malloc(sizeof(TN));
    if (one) {
        one->l = NULL;
        one->r = NULL;
        one->t.type = symb_NUMBER;
        one->t.data.number = 1.0;
    }
    return one;
}


void collapse_mult_nodes(TN **node, TN *root) {
    if (*node == NULL) return;

    // Применяем функцию рекурсивно к потомкам
    collapse_mult_nodes(&((*node)->l), root);
    collapse_mult_nodes(&((*node)->r), root);

    // Проверяем, является ли текущий узел оператором умножения
    if ((*node)->t.type == symb_OP && (*node)->t.data.op == OP_MULT) {
        // Проверяем, является ли один из потомков числом 1.0, а другой - числом
        if ((*node)->l && (*node)->r == NULL) {
            // Заменяем текущий узел на правый потомок
            TN *new_node = (*node)->l;
            free(*node);      // Освобождаем память текущего узла
            *node = new_node; // Установка нового узла
        } else if ((*node)->r && (*node)->l == NULL) {
            // Заменяем текущий узел на левый потомок
            TN *new_node = (*node)->r;
            free(*node);      // Освобождаем память текущего узла
            *node = new_node; // Установка нового узла
        } else if ((*node)->r == NULL && (*node)->l == NULL) {
            TN *p = findParent(root, (*node));
            deletNode(p, *(node));
        }
    }
}

void deletTree(TN *root) 
{
    if (root == NULL)
        return;

    deletTree(root->l);
    deletTree(root->r);

    free(root);
}

void equal_one(TN *root)
{
    if ((root->l && root->l->t.type == symb_NUMBER && root->l->t.data.number == 1.00) && (root->r && root->r->t.type == symb_NUMBER && root->r->t.data.number == 1.00)) {
        deletTree(root->l);
        deletTree(root->r);

        root->l = NULL;
        root->r = NULL;

        root->t.type = symb_NUMBER;
        root->t.data.number = 1.00;
    }
}

void adding_one(TN *root) {
    if (root == NULL) return;

    // Проверяем, является ли узел листом и оператором умножения
    if (root->l == NULL && root->r == NULL && root->t.type == symb_OP) {
        root->t.type = symb_NUMBER;
        root->t.data.number = 1.0;
        return;
    }


    // Обрабатываем левый и правый узлы, если они являются листами
    if (root->l && root->l->l == NULL && root->l->r == NULL && root->l->t.type == symb_OP) {
        free(root->l); // Освобождаем память текущего левого узла
        root->l = create_one_node(); // Создаем новый узел с числом 1.0
    }
    if (root->r && root->r->l == NULL && root->r->r == NULL && root->r->t.type == symb_OP) {
        free(root->r); // Освобождаем память текущего правого узла
        root->r = create_one_node(); // Создаем новый узел с числом 1.0
    }

    // Если левый или правый узел отсутствует, создаем узел с числом 1.0dd
    if (root->l == NULL) {
        root->l = create_one_node();
    }
    if (root->r == NULL) {
        root->r = create_one_node();
    }

    equal_one(root);
}

void collectTerms(TN *root, symbol *terms[], int *termsSize) {
    if (root == NULL) return;

    // Проверяем, является ли узел числом или переменной
    if (root->t.type == symb_NUMBER || root->t.type == symb_VAR) {
        terms[*termsSize] = &root->t;
        (*termsSize)++;
    } else {
        // Рекурсивно проходим по поддеревьям
        collectTerms(root->l, terms, termsSize);
        collectTerms(root->r, terms, termsSize);
    }
}


// Функция для упрощения дерева
void simplify(TN* root, symbol *numerator[], symbol *denominator[]) {
    int numSize = 0;
    int denSize = 0;
    TN *tmp = root;
    // Собираем термины для числителя из левого поддерева
    collectTerms(tmp->l, numerator, &numSize);

    // Собираем термины для знаменателя из правого поддерева
    collectTerms(tmp->r, denominator, &denSize);
    //print_arrays(numerator, numSize, denominator, denSize);

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

    collapse_mult_nodes(&root, root);
    adding_one(root);
}

int enter_and_build_tree() {
    STACK *s, *rev;
    symbol t;
	symb_TYPE checker;
    
    s = stack_create();
    rev = stack_create();
    
    while(next_symbol(&t)) {
        switch(t.type) {
            case symb_NONE:
                fprintf(stderr, "Error: symbol %c not recognized\n",t.data.c);
				destructor(s, rev);
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
                        fprintf(stderr, "Error: closing bracket hasn’t pair\n");
						destructor(s, rev);
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
		
	checker = t.type;
	
	if(checker == symb_EOF) {
		destructor(s, rev);
		return 0;
	}

	printf("\n-------------------\n");
	
    while(!stack_empty(s)) {
        t = stack_pop(s);
        if(t.type == symb_LEFT_BR) {
            fprintf(stderr, "Error: opening bracket hasn’t pair\n");
			destructor(s, rev);
            return 2;
        }
        stack_push(rev, t);
    }
    
    // Build tree
    if(stack_empty(rev)) {
        fprintf(stderr, "Error: expression is empty\n");
		destructor(s, rev);
        return 3;
    }

    TN *root = NULL;
    if(!build_tree(&root, rev)) {
        fprintf(stderr, "Error while building tree: don’t find one of operands\n");
		destructor(s, rev);
        return 4;
    }
    if(!stack_empty(rev)) {
        fprintf(stderr, "Error while building tree: extra operands or opetators\n");
		destructor(s, rev);
        return 4;
    }

    print_tree(root, 0);
	destructor(s, rev);
    printf("\n-------------------\n");
    symbol *numerator[100];
    symbol *denominator[100];
    simplify(root, numerator, denominator);
    print_tree(root, 0);
    printf("\n=============================================================\n");    
    print_expr(root);   
    deletTree(root);
    //root = NULL;
	printf("\n\n");
	if(checker == symb_ENDL) return 5;
	else return 6;
}

int main(int argc, char* argv[]) {
	int error_code;

	do{
		error_code = enter_and_build_tree();
	}while(error_code);
	
	printf("\n-------------------\n");
	
	return 0;
}