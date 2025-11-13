#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char prod[MAX][MAX];
char nonterminals[MAX];
int n, ntCount = 0;

/* Add without duplicates */
void add(char res[], char ch) {
    for (int i = 0; res[i] != '\0'; i++)
        if (res[i] == ch) return;
    int len = strlen(res);
    res[len] = ch;
    res[len + 1] = '\0';
}

/* FIRST function */
void FIRST(char X, char res[]) {
    res[0] = '\0';  // clear result

    if (!isupper(X)) {
        add(res, X);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (prod[i][0] == X) {
            int j = 2; // after '='

            while (prod[i][j] != '\0') {
                char Y = prod[i][j];

                if (Y == '$') {        // epsilon
                    add(res, '$');
                    break;
                }
                else if (!isupper(Y)) { // terminal
                    add(res, Y);
                    break;
                }
                else {                 // non-terminal
                    char temp[20];
                    FIRST(Y, temp);

                    int eps = 0;
                    for (int k = 0; temp[k] != '\0'; k++) {
                        if (temp[k] == '$')
                            eps = 1;
                        else
                            add(res, temp[k]);
                    }

                    if (!eps) break; // stop if FIRST(Y) has no epsilon
                }
                j++;
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions like S=AB or A=a or A=$:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
        char lhs = prod[i][0];

        // store unique non-terminals
        int exists = 0;
        for (int j = 0; j < ntCount; j++)
            if (nonterminals[j] == lhs)
                exists = 1;
        if (!exists)
            nonterminals[ntCount++] = lhs;
    }

    printf("\n--- FIRST SETS ---\n");
    for (int i = 0; i < ntCount; i++) {
        char res[20];
        FIRST(nonterminals[i], res);

        printf("FIRST(%c) = { ", nonterminals[i]);
        for (int j = 0; res[j] != '\0'; j++)
            printf("%c ", res[j]);
        printf("}\n");
    }

    return 0;
}
