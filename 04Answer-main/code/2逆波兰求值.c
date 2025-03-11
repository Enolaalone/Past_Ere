#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack *list;
struct Stack{
    int pointer;
    int data[100];
};

void Push(list s,int c)
{
    s->pointer++;
    s->data[s->pointer]=c;
}

int Pop(list s)
{
    if(s->pointer==-1)
        return 0;
    s->pointer--;
    return s->data[s->pointer+1];
}

int Polish(char *str[],int LEN){
    int str_p=0;
    int R;
    int L;
    //建栈
    list ps=(list) malloc(sizeof (struct Stack));//栈地址
    ps->pointer=-1;
    while(str_p!=LEN){
        if(!strcmp(str[str_p],"-"))
        {
            R= Pop(ps);
            L= Pop(ps);
            Push(ps,L-R);
        }
        else if(!strcmp(str[str_p],"+"))//加
        {
            R= Pop(ps);
            L= Pop(ps);
            Push(ps,L+R);
        }
        else if(!strcmp(str[str_p],"*"))
        {
            R= Pop(ps);
            L= Pop(ps);
            Push(ps,L*R);
        }
        else if(!strcmp(str[str_p],"/"))
        {
            R= Pop(ps);
            L=Pop(ps);
            Push(ps,L/R);
        }
        else{
            Push(ps, atoi(str[str_p]));
        }
        str_p++;
    }
    printf("%d",ps->data[0]);
    return ps->data[0];
}
int main() {
    char *tokens[]={"2","1","+","3","*"};
    int LEN=sizeof (tokens) /sizeof (char*);//确定字符串长度 5
    return Polish(tokens,LEN);

}