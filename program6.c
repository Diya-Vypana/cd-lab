#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

char production[MAX][MAX];
char first[MAX];
int n;

void addToResult(char ch) {
    for (int i = 0; first[i] != '\0'; i++)
        if (first[i] == ch) return;
    int len = strlen(first);
    first[len] = ch;
    first[len + 1] = '\0';
}

void findFirst(char c) {
    if (!isupper(c)) { // terminal
        addToResult(c);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (production[i][0] == c) {
            int j = 2; // start after '='
            while (production[i][j] != '\0') {
                char next = production[i][j];

                if (next == '$') { // epsilon
                    addToResult('$');
                    break;
                } else if (!isupper(next)) { // terminal
                    addToResult(next);
                    break;
                } else { // non-terminal
                    int oldLen = strlen(first);
                    findFirst(next);

                    // check if ε is in FIRST(next)
                    int hasEpsilon = 0;
                    for (int k = oldLen; first[k] != '\0'; k++)
                        if (first[k] == '$')
                            hasEpsilon = 1;

                    if (!hasEpsilon)
                        break; // stop if no ε, else continue next symbol
                }
                j++;
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g., A=aB):\n");
    for (int i = 0; i < n; i++)
        scanf("%s", production[i]);

    char ch;
    int choice;

    do {
        printf("\nFind FIRST of which non-terminal? ");
        scanf(" %c", &ch);

        first[0] = '\0';
        findFirst(ch);

        printf("FIRST(%c) = { ", ch);
        for (int i = 0; first[i] != '\0'; i++)
            printf("%c ", first[i]);
        printf("}\n");

        printf("\nDo you want to find FIRST of another symbol? (1 = Yes / 0 = No): ");
        scanf("%d", &choice);
    } while (choice == 1);

    return 0;
}
