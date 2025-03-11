#include <stdio.h>
#include <stdlib.h>

typedef struct Stack *list;//定义struct Stack类型的指针为list
struct Stack//栈结构体
{
    int pointer;//栈指针
    char data[1000];//单字节

};

void Push(list s,char c)//入栈
{
    s->pointer++;//栈指针加1
    s->data[s->pointer]=c;//存入数据
}

char Pop(list s)//出栈
{
    if(s->pointer==-1)//如果栈是空的
        return 0;
    (s->pointer)--;
    return s->data[(s->pointer)+1];
}
int main() {
    char ls[]="81/3+67*(3+12)-24*5";
    char arr[100]="\0";
    int ls_p=0;
    int arr_p=0;
    char letter;
    list ps=(list)malloc(sizeof(struct Stack));//栈结构体指针
    ps->pointer=-1;
    while(ls[ls_p]!='\0')//字符串末尾会加有‘\0’
    {
        if(ls[ls_p]>='0' && ls[ls_p]<='9')//在数字范围内
        {
            if(!(ls[ls_p+1]>='0' && ls[ls_p+1]<='9')){//数字末尾的字符
                printf("%c#",ls[ls_p]);
            }
            else if(ls[ls_p+1]>='0' && ls[ls_p+1]<='9'){//非末尾字符
                printf("%c",ls[ls_p]);
            }
        }

        else if(ls[ls_p]=='('){//“(”直接入栈
            Push(ps,ls[ls_p]);
        }

        else if(ls[ls_p]==')'){//“)”弹出栈顶算符直到弹出“(”
            letter=Pop(ps);
            while(letter!='('){
                printf("%c",letter);
                letter=Pop(ps);
            }
        }

        else if(ls[ls_p]=='+'||ls[ls_p]=='-'){
            if(ps->pointer==-1)//空栈
                Push(ps,ls[ls_p]);
            else{
                while(ps->pointer!=-1){//"+""-"如果没有（）直接清空栈，再入栈
                    letter=Pop(ps);
                    if(letter=='(') //如果遇到“(”结束，
                    {
                        Push(ps,'(');//还原弹出的“(”
                        break;
                    }
                    else if(letter=='+'||letter=='-'||letter=='*'||letter=='/'){
                        printf("%c",letter);
                    }

                }
                Push(ps,ls[ls_p]);
            }


        }
        else if(ls[ls_p]=='*'||ls[ls_p]=='/'){
            if(ps->pointer==-1)//空栈
                Push(ps,ls[ls_p]);
            else{
                letter=Pop(ps);
                if(letter=='+'|| letter=='-')
                    Push(ps,letter);//恢复
                while(letter!='+'&& letter!='-'){
                    if(letter=='(')
                    {
                        Push(ps,letter);//恢复
                        break;
                    }
                    printf("%c",letter);
                    letter=Pop(ps);
                    if(letter=='+'|| letter=='-')
                        Push(ps,letter);
                }
                Push(ps,ls[ls_p]);
            }

        }
        ls_p++;
    }
    while(ps->pointer!=-1){//中缀表达扫描完清空在栈
        letter=Pop(ps);
        printf("%c",letter);
    }
    return 0;
}