#include "lexer.h"
#include <ctype.h>
#include <string.h>

Fila tokenize(char* expr) {
    Fila fila;
    initFila(&fila);

    for (int i = 0; expr[i]; i++) {
        char c = expr[i];
        if (isspace(c)) continue;

        Token token;

        if (isdigit(c)) {
            token.value = c;
            token.type = NUMERO;
            token.peso = 0;
        } else if (c == '(' || c == ')') {
            token.value = c;
            token.type = PARENTESES;
            token.peso = -1;
        } else if (strchr("+-*/^", c)) {
            token.value = c;
            token.type = OPERADOR;

            switch (c) {
                case '+':
                case '-': token.peso = 1; break;
                case '*':
                case '/': token.peso = 2; break;
                case '^': token.peso = 3; break;
            }
        } else {
            Token invalido = {'i', NONE, -1};
            inserir(&fila, invalido);
            return fila;
        }

        inserir(&fila, token);
    }

    Token fim = {'\0', NONE, -1};
    inserir(&fila, fim);
    return fila;
}
