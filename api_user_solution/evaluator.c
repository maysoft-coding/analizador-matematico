#include "evaluator.h"

int evaluate_postfix(Fila* postfix) {
    Pilha_int stack;
    initPilhaInt(&stack);

    NO* no = postfix->ini;  // CORRIGIDO: era 'inicio'

    while (no && no->token.type != NONE) {  // era no->tk
        Token tk = no->token;

        if (tk.type == NUMERO) {
            push_int(&stack, tk.value - '0');
        } else if (tk.type == OPERADOR) {
            if (vaziaPilhaInt(&stack)) return INT_MIN;
            int b = top_int(&stack);
            pop_int(&stack);

            if (vaziaPilhaInt(&stack)) return INT_MIN;
            int a = top_int(&stack);
            pop_int(&stack);

            int result = 0;

            switch (tk.value) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) return -2; // Erro divisão por zero
                    result = a / b;
                    break;
                case '^':
                    result = 1;
                    for (int i = 0; i < b; i++) result *= a;
                    break;
            }

            push_int(&stack, result);
        }

        no = no->prox;
    }

    if (vaziaPilhaInt(&stack)) return INT_MIN;
    return top_int(&stack);
}
