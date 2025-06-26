#include "error.h"
#include <ctype.h>

int has_invalid_token(Fila* tokens) {
    NO* no = tokens->ini;  // era 'inicio'

    while (no && no->token.type != NONE) {  // era 'no->tk'
        Token tk = no->token;

        if (tk.type == NONE && tk.value != '\0')
            return 1;

        no = no->prox;
    }

    return 0;
}

int unbalanced_parentheses(char* expr) {
    Pilha_int stack;
    initPilhaInt(&stack);

    while (*expr) {
        if (*expr == '(') {
            push_int(&stack, '(');
        } else if (*expr == ')') {
            if (vaziaPilhaInt(&stack)) return 1;
            pop_int(&stack);
        }
        expr++;
    }

    return !vaziaPilhaInt(&stack);
}
