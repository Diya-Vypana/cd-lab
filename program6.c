#include <stdio.h>
#include <ctype.h>   // for isupper() — checks if a character is uppercase (non-terminal)
#include <string.h>  // for string operations

#define MAX 10

char production[MAX][MAX];   // stores grammar rules like A=aB
char first[MAX];             // stores the computed FIRST symbols
int n;                       // number of productions


void addToResult(char ch)
{
    for (int i = 0; first[i] != '\0'; i++)
        if (first[i] == ch) return;  // skip duplicates
    int len = strlen(first);
    first[len] = ch;
    first[len + 1] = '\0';
}

void findFirst(char c)
{
    // 🔹 Rule 1: If X is a terminal → FIRST(X) = {X}
    if (!isupper(c)) // not a capital letter → terminal
    {
        addToResult(c);
        return;
    }

    // 🔹 Otherwise, X is a non-terminal → explore its productions
    for (int i = 0; i < n; i++)
    {
        if (production[i][0] == c)   // production starts with X
        {
            // Example: A=aB → production[i][2] = 'a'
            char next = production[i][2];

            // 🔹 Rule 2: If production is X → ε → add ε
            if (next == '$')          // '$' used to represent epsilon
                addToResult('$');

            // 🔹 Rule 3: If X → terminal α → add that terminal
            else if (!isupper(next))  // if RHS starts with terminal
                addToResult(next);

            // 🔹 Rule 4: If X → Yα and Y is non-terminal → FIRST(Y) ⊆ FIRST(X)
            else if (isupper(next))
                findFirst(next);
        }
    }
}


int main()
{
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g., A=aB):\n");
    for (int i = 0; i < n; i++)
        scanf("%s", production[i]);  // input grammar rules

    char ch;
    int choice;

    do {
        printf("\nFind FIRST of which non-terminal? ");
        scanf(" %c", &ch);

        // reset first[] before each new computation
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
