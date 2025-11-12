#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// PRODUCTION RULES
//S  -> a A B e
//A  -> b A'
//A' -> b c A' | ε
//B  -> d

int i=0;
char input[100];

void error()
{
    printf("rejected\n");
    exit(0);
}

void B()
{
    if(input[i]=='d')
    {
        i++;
    }
    else
        error();
}

void Aprime()
{
    if(input[i]=='b' && input[i+1]=='c')
    {
        i+=2;
        Aprime();
    }
}

void A()
{
    if(input[i]=='b')
    {
        i++;
        Aprime();
    }
    else
        error();
}

void S()
{
    if(input[i]=='a')
    {
        i++;
        A();
        B();
        if(input[i]=='e')
        {
            i++;
            if(input[i]=='\0')
            {
                printf("String accepted\n");
            }
        }
        else
            error();
    }
    else
        error();
}


int main()
{
    printf("enter input string: ");
    scanf("%s",input);
    S();
    
    return 0;
}
