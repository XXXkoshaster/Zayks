#ifndef __symbol_h__
#define __symbol_h__

// перечислимый тип ассоциативности операции
typedef enum _OP_ASSOC {
    ASSOC_LEFT, ASSOC_RIGHT
} OP_ASSOC;


// максимальная длина имени переменной
#define VARNAME_LEN 10

// перечислимый тип категорий символов (лексем, токенов)
typedef enum _symb_TYPE {
    symb_NONE,    // не символ вовсе (С) Дубинин А.В.
	symb_ENDL,	  // конец строки
	symb_EOF,	  // конец файла
    symb_NUMBER,  // число
    symb_VAR,     // переменная
    symb_OP,      // оператор
    symb_LEFT_BR, // открывающая скобка
    symb_RIGHT_BR // закрывающая скобка
} symb_TYPE;

// перечислимый тип допустимых операций
typedef enum _OP {
    OP_MINUS = '-',
    OP_PLUS = '+',
    OP_MULT = '*',
    OP_DIVIDE = '/',
    OP_POW = '^',
    OP_UNARY_MINUS = '!' // а тут что угодно может быть, главное, чтобы с простым минусом не путать (С) Дубинин А.В.
} OP;

// тип и значение символа
typedef struct {
    symb_TYPE type;			// тип символа
    union {
        float number;          // если символ - число
        char var[VARNAME_LEN]; // если символ - переменная
        OP op;                 // если символ - оператор
        char c;                // на случай ошибок, здесь будет считанный непонятный char
    } data;
} symbol;

#endif