#include <stdio.h>
#include <stdlib.h>
typedef struct Stack *list;
struct Stack{//栈
    int pointer;
    int data[100];
};

void Push(list s,int c)//入栈
{
    s->pointer++;
    s->data[s->pointer]=c;
}

int Pop(list s)//出栈
{
    if(s->pointer==-1)
        return 0;
    s->pointer--;
    return s->data[s->pointer+1];
}

char* Arr() {
    char ls[]="81/3+67*(3+12)-24*5";
    char* arr = (char*)malloc(1000 * sizeof(char));//装字符串的指针
    int ls_p=0;
    int arr_p=0;//arr
    char letter;
    list ps=(list)malloc(sizeof(struct Stack));//栈结构体指针
    ps->pointer=-1;
    while(ls[ls_p]!='\0')//字符串末尾会加有‘\0’
    {
        if(ls[ls_p]>='0' && ls[ls_p]<='9')//在数字范围内
        {
            if(!(ls[ls_p+1]>='0' && ls[ls_p+1]<='9')){//比较ASCII值
//                printf("%c#",ls[ls_p]);
                arr[arr_p]=ls[ls_p];
                arr[arr_p+1]='#';//数字字符末尾添加“#”
                arr_p+=2;
            }
            else if(ls[ls_p+1]>='0' && ls[ls_p+1]<='9'){
//                printf("%c",ls[ls_p]);
                arr[arr_p]=ls[ls_p];
                arr_p++;
            }
        }
        else if(ls[ls_p]=='('){
            Push(ps,ls[ls_p]);
        }
        else if(ls[ls_p]==')'){
            letter=Pop(ps);
            while(letter!='('){
//                printf("%c",letter);
                arr[arr_p]=letter;
                arr_p++;
                letter=Pop(ps);
            }
        }
        else if(ls[ls_p]=='+'||ls[ls_p]=='-'){
            if(ps->pointer==-1)
                Push(ps,ls[ls_p]);
            else{
                while(ps->pointer!=-1){
                    letter=Pop(ps);
                    if(letter=='(')
                    {
                        Push(ps,'(');
                        break;
                    }
                    else if(letter=='+'||letter=='-'||letter=='*'||letter=='/'){
//                        printf("%c",letter);
                        arr[arr_p]=letter;
                        arr_p++;
                    }
                }
                Push(ps,ls[ls_p]);
            }


        }
        else if(ls[ls_p]=='*'||ls[ls_p]=='/'){
            if(ps->pointer==-1)
                Push(ps,ls[ls_p]);
            else{
                letter=Pop(ps);
                if(letter=='+'|| letter=='-')
                    Push(ps,letter);
                while(letter!='+'&& letter!='-'){
                    if(letter=='(')
                    {
                        Push(ps,letter);//恢复
                        break;
                    }
//                    printf("%c",letter);
                    arr[arr_p]=letter;
                    arr_p++;
                    letter=Pop(ps);
                    if(letter=='+'|| letter=='-')
                        Push(ps,letter);
                }
                Push(ps,ls[ls_p]);
            }

        }
        ls_p++;
    }
    while(ps->pointer!=-1){
        letter=Pop(ps);
//        printf("%c",letter);
        arr[arr_p]=letter;
        arr_p++;
    }
    arr[arr_p] = '\0';
    return arr;
}
int main() {
    char* After = Arr();//后缀表达式
    char* str = malloc(100 * sizeof(char)); // 动态分配内存
    int After_p=0;
    int str_p=0;//字符串指针
     int R;//栈顶数右操作数
     int L;//次栈顶左操作数
    //建栈
    list ps=(list) malloc(sizeof (struct Stack));//栈地址
    ps->pointer=-1;
    printf("%s",After);
    while(After[After_p]!='\0'){
        if(After[After_p]=='#')
        {
            Push(ps, atoi(str));//数字字符串整数化入栈入栈
            free(str);//释放内存
            str = malloc(100 * sizeof(char));//恢复初始数据
            str_p=0;//初始化字符串指针
        }
        if(After[After_p]>='0' && After[After_p]<='9')//在数字范围内
        {
            str[str_p]=After[After_p];//
            str_p++;
        }
        if(After[After_p]=='-')//减
        {
            R= Pop(ps);
            L= Pop(ps);
            Push(ps,L-R);
        }
        else if(After[After_p]=='+')//加
        {
            R= Pop(ps);
            L= Pop(ps);
            Push(ps,L+R);
        }
        else if(After[After_p]=='*')//乘
        {
            R= Pop(ps);
            L= Pop(ps);
            printf("\n");
//            printf("%d",L*R);
            Push(ps,L*R);
        }
        else if(After[After_p]=='/')//除
        {
            R= Pop(ps);
            L=Pop(ps);
            Push(ps,L/R);
        }
        After_p++;
    }
    printf("%d",ps->data[0]);
    free(ps);//释放内存
    return 0;
}