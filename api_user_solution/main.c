#include "dstlib_include.h"
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "error.h"

void process_line(FILE* out, const char* line) {
    char expr[256];
    strcpy(expr, line);

    if (unbalanced_parentheses(expr)) {
        fprintf(out, "Erro: Parênteses desbalanceados\n");
        return;
    }

    Fila tokens = tokenize(expr);
    if (has_invalid_token(&tokens)) {
        fprintf(out, "Erro: Caracteres inválidos\n");
        return;
    }

    Fila postfix = shunting_yard(&tokens);
    if (frente(&postfix).type == NONE && frente(&postfix).value == 'e') {
        fprintf(out, "Erro: Expressão malformada\n");
        return;
    }

    int result = evaluate_postfix(&postfix);
    if (result == -2) {
        fprintf(out, "Erro: Divisão por zero\n");
    } else if (result == INT_MIN) {
        fprintf(out, "Erro: Expressão malformada\n");
    } else {
        fprintf(out, "%d\n", result);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Uso: %s <entrada> <saida>\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

    if (!input || !output) {
        perror("Erro ao abrir arquivos.");
        return 2;
    }

    char line[256];
    while (fgets(line, sizeof(line), input)) {
        line[strcspn(line, "\n")] = 0;
        process_line(output, line);
    }

    fclose(input);
    fclose(output);
    return 0;
}