#include <stdio.h>
#include <string.h>

#define MAXLINE 100

// Find operator position (+, -, *, /)
int find_operator_pos(const char *s) {
    for (int i = 0; s[i]; i++) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
            return i;
    }
    return -1;
}

int main() {
    char line[MAXLINE];
    int regCount = 0;

    printf("Enter intermediate code lines (type 'exit' to stop):\n");

    while (1) {
        printf("> ");
        scanf("%s", line);

        if (strcmp(line, "exit") == 0)
            break;

        // Split into LHS and RHS
        char *eq = strchr(line, '=');
        if (!eq) continue;

        *eq = '\0';
        char lhs[MAXLINE], rhs[MAXLINE];
        strcpy(lhs, line);
        strcpy(rhs, eq + 1);

        // Find operator
        int pos = find_operator_pos(rhs);
        char reg[10];
        sprintf(reg, "R%d", regCount++);

        if (pos >= 0) {
            // Binary operation
            char op = rhs[pos];
            char op1[MAXLINE], op2[MAXLINE];
            strncpy(op1, rhs, pos);
            op1[pos] = '\0';
            strcpy(op2, rhs + pos + 1);

            printf("Mov %s,%s\n", op1, reg);

            if (op == '+')
                printf("ADD %s,%s\n", op2, reg);
            else if (op == '-')
                printf("SUB %s,%s\n", op2, reg);
            else if (op == '*')
                printf("MUL %s,%s\n", op2, reg);
            else if (op == '/')
                printf("DIV %s,%s\n", op2, reg);

            printf("Mov %s,%s\n\n", reg, lhs);
        } else {
            // Simple assignment
            printf("Mov %s,%s\n", rhs, reg);
            printf("Mov %s,%s\n\n", reg, lhs);
        }
    }

    return 0;
}
