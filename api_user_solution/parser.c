#include "parser.h"

Fila shunting_yard(Fila* input) {
    Fila output;
    initFila(&output);

    Pilha operadores;
    initPilha(&operadores);

    NO* no_atual = input->ini;  // <-- aqui trocamos 'inicio' por 'ini'

    while (no_atual && no_atual->token.type != NONE) {  // 'tk' -> 'token'
        Token tk = no_atual->token;

        if (tk.type == NUMERO) {
            inserir(&output, tk);
        } else if (tk.type == OPERADOR) {
            while (!vaziaPilha(&operadores) &&
                   top(&operadores).type == OPERADOR &&
                   top(&operadores).peso >= tk.peso) {
                Token op = top(&operadores);
                pop(&operadores);
                inserir(&output, op);
            }
            push(&operadores, tk);
        } else if (tk.type == PARENTESES) {
            if (tk.value == '(') {
                push(&operadores, tk);
            } else if (tk.value == ')') {
                while (!vaziaPilha(&operadores) && top(&operadores).value != '(') {
                    Token op = top(&operadores);
                    pop(&operadores);
                    inserir(&output, op);
                }

                if (!vaziaPilha(&operadores) && top(&operadores).value == '(')
                    pop(&operadores); // Remove '('
                else {
                    Fila erro;
                    initFila(&erro);
                    Token t = {'e', NONE, -1};
                    inserir(&erro, t);
                    return erro;
                }
            }
        }

        no_atual = no_atual->prox;
    }

    while (!vaziaPilha(&operadores)) {
        Token op = top(&operadores);
        pop(&operadores);
        inserir(&output, op);
    }

    return output;
}
