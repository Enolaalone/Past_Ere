#include <stdio.h>
#include <stdlib.h>//malloc，free
#include <stdbool.h>//bool
#include <string.h>//strlen
bool inStack[256];//确认数是否在栈中 ,初始值全设为0 false
int counts[256]={0};//字符出现次数
typedef struct Stack *list;//将栈结构的指针命名为list
struct Stack{//栈
    int pointer;//栈指针
    char data[100];//栈单元
};

void Push(list s,char c)//入栈
{
    s->pointer++;
    s->data[s->pointer]=c;
}
char Pop(list s)//出栈
{
    if(s->pointer==-1)
        return 0;
    s->pointer--;
    return s->data[(s->pointer)+1];
}
void LetterCount(char *str,int count[]){//char *str表示字符串组char str[]
    for(int i=0;i!= strlen(str);i++){
        count[(int)str[i]]++;//将字符串中对应字符str[i]转为ASCII值，对应序号的数组单元加1
    }
}
int main() {
    char letter[1000]="\0";//给予100的内存空间防止冲出
    char k;//栈顶字符
    int ls_p=0;//letter序号
    //键栈------------------------------------
    list ps=(list)malloc(sizeof(struct Stack));//栈结构体指针
    ps->pointer=-1;

    gets(letter);//键盘上获取一个值
    LetterCount(letter,counts);//字母索引确定字母出现次数
    while(letter[ls_p]!='\0'){//字符串末尾会加有‘\0’
        if(!inStack[(int)letter[ls_p]]){//不在栈中
            k= ps->data[ps->pointer];//栈顶字符
            while((int)k>(int)letter[ls_p] && counts[k]>0){//如果栈顶字符ASCII大于当前字符，并且后续还会出现
                Pop(ps);//弹出栈顶字符，使字典序最小
                inStack[(int)k]=false;//标记弹出字符已经不在栈中
                k= ps->data[ps->pointer];//继续处理栈顶字符和当前字符比较
            }
            Push(ps,letter[ls_p]);//当前字符入栈
            inStack[(int)letter[ls_p]]=true;//字母已入
            counts[letter[ls_p]]-=1;//所剩字符减一
        }
        ls_p++;
    }
    for(int i=0;i<=ps->pointer;i++)//处理结束后从栈底到栈顶即为
    {
        printf("%c",ps->data[i]);
    }
    free(ps);//释放内存
    return 0;
}