#include <stdio.h>
#include <string.h>

char lhs[100],rhs[100][100],stack[100];
char input[100];
int top=-1,ip=0,n;

void push(char c)
{
    top++;
    stack[top]=c;
    stack[top+1]='\0';
}

void pop(int n)
{
    top-=n;
    if(top<-1)
        top=-1;
    stack[top+1]='\0';
}

void reduce()
{
    int reduced=1;
    while(reduced)
    {
        reduced=0;
        for(int i=0;i<n;i++)
        {
            int len=strlen(rhs[i]);
            if(top+1>=len) //enough items to pop? 
            {
                if(strncmp(stack+top-len+1,rhs[i],len)==0)
                {
                    if(ip>=strlen(input) && lhs[i]!=lhs[0]) //not last prod
                        continue;
                    
                    pop(len);
                    push(lhs[i]);
                    printf("%-20s %-20s Reduce %c->%s\n",stack,input+ip,lhs[i],rhs[i]);  //c or s
                    reduced=1;
                    break;
                }
            }
        }
    }
}

int main()
{
    int i;
    
    printf("enter no of prod\n");
    scanf("%d",&n);
    
    printf("Enter prods\n");
    for(i=0;i<n;i++)
    {
        char prod[50];
        scanf("%s",prod);
        lhs[i]=prod[0];
        strcpy(rhs[i],prod+3);
        
    }
    
    printf("enter input string\n");
    scanf("%s",input);
    
    while(1)
    {
        char c=input[ip];
        if(c!='\0')
        {
            push(c);
            printf("%-20s %-20s Shift %c\n",stack,input+ip+1,c);
            ip++;
            reduce();
        }
        else
            break;
    }
    
    reduce();
    
    if(top==0 && stack[top]==lhs[0])
        printf("\nsuccess\n");
    else
        printf("\ninput rejected\n");
    
    return 0;
}
