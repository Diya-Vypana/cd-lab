#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *fp=fopen("input.txt","r");
    if(!fp)
    {
        printf("error opening file\n");
        return 1;
    }
    
    char ch,first;
    char buffer[100];
    int i;
    
    while((ch=fgetc(fp))!=EOF)
    {
        if(isspace(ch))
            continue;
        switch(ch)
        {
            case '+': case '-': case '*': case '/':
            case '=':
            {
                first=ch;
                ch=fgetc(fp);
                if(ch=='=')
                {
                    printf("%c%c -> assignment operator\n",first,ch);
                }
                else if(ch=='/')
                {
                    while((ch=fgetc(fp))!=EOF && ch!='\n');
                }
                else
                {
                    printf("%c -> operator\n",first);
                }
                ungetc(ch,fp);
                break;
            }
            
            case ',':
            {
                printf("%c -> comma\n",ch);
                break;
            }
            case ';':
            {
                printf("%c -> semicolon\n",ch);
                break;
            }
            
            default:
            {
                //char buffer[100];
                i=0;
                
                if(isalpha(ch) || ch=='_')
                {
                    buffer[i++]=ch;
                    while((ch=fgetc(fp))!=EOF && (isalnum(ch) || ch=='_'))
                    {
                        buffer[i++]=ch;
                    }
                    buffer[i]='\0';
                    ungetc(ch,fp);
                    
                    if(strcmp(buffer,"int")==0 || strcmp(buffer,"float")==0 || strcmp(buffer,"char")==0 ||strcmp(buffer,"break")==0)
                    {
                        printf("%s -> keyword\n",buffer);
                    }
                    else
                    {
                        printf("%s -> identifier\n",buffer);
                    }
                }
                
                else if(isdigit(ch))
                {
                    i=0;
                    int isfloat=0;
                    buffer[i++]=ch;
                    while((ch=fgetc(fp))!=EOF && (isdigit(ch) || ch=='.'))
                    {
                        if(ch=='.')
                            isfloat=1;
                        buffer[i++]=ch;
                    }
                    buffer[i]='\0';
                    ungetc(ch,fp);
                    
                    if(isfloat)
                        printf("%s -> floating point\n",buffer);
                    else
                        printf("%s -> integer\n",buffer);
                    
                }
                else
                {
                    printf("%c -> unknown\n",ch);
                }
            }
        }
    }
    
    return 0;
}
