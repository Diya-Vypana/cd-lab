#include <stdio.h>
#include <ctype.h>
#include <string.h>

char stack[50];
int top=-1;
int tempcount=0;

char push(char c)
{
    stack[++top]=c;
}

char pop()
{
    return stack[top--];
}

int preced(char c)
{
    if(c=='+' || c=='-')
        return 1;
    else if(c=='*' || c=='/')
        return 2;
    return 0;
}

void infixpost(char infix[],char postfix[])
{
    char c;
    int k=0;
    for(int i=0;infix[i]!='\0';i++)
    {
        c=infix[i];
        if(isalnum(c))
        {
            postfix[k++]=c;
        }
        else if(c=='(')
        {
            push(c);
        }
        else if(c==')')
        {
            while(top!=-1 && stack[top]!='(')
            {
                postfix[k++]=pop();
            }
            pop();
        }
        else if(c=='+' || c=='-' || c=='*' || c=='/')
        {
            while(top!=-1 && preced(stack[top])>=preced(c))
            {
                postfix[k++]=pop();
            }
            push(c);
        }
    }
    
    while(top!=-1)
    {
        postfix[k++]=pop();
    }
    
    postfix[k]='\0';
    
}

void getTAC(char postfix[],char lhs)
{
    char st[100][100];
    int t=-1;
    char c;
    
    for(int i=0;postfix[i]!='\0';i++)
    {
        c=postfix[i];
        
        if(isalnum(c))
        {
            char str[2]={c,'\0'};
            strcpy(st[++t],str);
        }
        else
        {
            char op1[100],op2[100];
            char temp[3];
            strcpy(op2,st[t--]);
            strcpy(op1,st[t--]);
            
            sprintf(temp,"%c",'Z'-tempcount);
            tempcount++;
            
            printf("%s = %s %c %s",temp,op1,c,op2);
            strcpy(st[++t],temp);
        }
    }
    printf("%c = %s",lhs,st[t]);
}

int main()
{
    char expr[50],rhs[50];
    char lhs;
    printf("enter the expr:\n"); //a=b+c*d
    scanf("%s",expr);
    lhs=expr[0];
    strcpy(rhs,expr+2);
    
    char postfix[50];
    infixpost(rhs,postfix);   //bcd*+
    
    getTAC(postfix,lhs);
    
    return 0;
}
