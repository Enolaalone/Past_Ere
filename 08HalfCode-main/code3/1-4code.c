#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char x='/';
//int q=0;
typedef struct Stack{//栈
    int point;
    int data[200];
}Stack;

void push(Stack* p,int s){//入栈
    p->point++;
    p->data[p->point]=s;
}
int pop(Stack* p){//出栈
    if(p->point==-1)return -1;
    else{
        p->point--;
        return p->data[p->point+1];
    }
}

typedef struct Node{//树结构体
    char name[3];//单个字读取
    int weight;
    int parent;
    int l_kid;
    int r_kid;
    int num;
}Node;

//\n 1520
int reading(Node nodes[],char names[],int n){//数组 读取文件 长度
    char words[20];
    FILE *fp= fopen(names,"r");
    while (fgets(words,20,fp)!=NULL){
        sscanf(words,"%s\t%d",nodes[n].name,&nodes[n].weight);
        n++;
    }
    strcpy(nodes[n].name,"\n");
    nodes[n].weight=1521;
    n++;
    return n;
}

void create_list(Node nodes[],int n){//构建树
    int k=2*n-1;
    for (int i = 0; i < k ; ++i) {
        if(i<n){
            nodes[i].parent=-1;//父节点在数组的位置
            nodes[i].l_kid=-1;//子节点指向数组外的位置
            nodes[i].r_kid=-1;
        }else{
            strcpy(nodes[i].name,"\0");
            nodes[i].weight=0;//权重
            nodes[i].parent=-1;//父节点指向数组外位置
            nodes[i].l_kid=-1;//子节点指向数组外的位置
            nodes[i].r_kid=-1;
        }
        nodes[i].num=i;
    }
}

void swap(int *s1,int *s2){//交换
    int t;
    t=*s1;
    *s1=*s2;
    *s2=t;
}

void compare(Node nodes[],int s[],int k){//寻找最小和次小
    for (int i = 0; i < k; ++i) {
        if(nodes[i].parent==-1){
            s[0]=nodes[i].weight;//s[0]为权重
            s[1]=i;//位置
            for (int j = i+1; j < k; ++j) {
                if(nodes[j].parent==-1){
                    s[2]=nodes[j].weight;//次小权重
                    s[3]=j;//位置
                    break;
                }
            }
            break;
        }
    }
    if(s[0]>s[2]){//如果最小大于次小，交换位置
        swap(&s[1],&s[3]);
        swap(&s[0],&s[2]);
    }

    for (int i = 0; i < k; ++i) {
        if(nodes[i].parent==-1 && i!=s[1] && i!=s[3]){
            if(nodes[i].weight<s[0]){//小于最小提换最小，最小移到次小上
                s[2]=s[0];s[3]=s[1];
                s[0]=nodes[i].weight;s[1]=i;
            }
            else if(nodes[i].weight>=s[0] && nodes[i].weight<s[2]){//大于最小，小于次小，这个数给次小
                s[2]=nodes[i].weight;s[3]=i;
            }
        }
    }
}
void connect(Node nodes[],int n){//连接
    int k=2*n-1;//节点数2n-1
    for (int i = 0; i < k-n; ++i) {
        int s[4];
        compare(nodes,s,n+i);

        nodes[n+i].weight=s[0]+s[2];//s[0] s[2]为子节点权重
        //========位置确定========
        nodes[n+i].l_kid=s[1];
        nodes[n+i].r_kid=s[3];
        nodes[s[1]].parent=n+i;
        nodes[s[3]].parent=n+i;
    }
}

void stack_code(Node nodes[],int n){
    Stack *ps=(Stack*) malloc(sizeof (Stack));//建栈
    ps->point=-1;

    FILE *pf= fopen("code.txt","w");//创建文件
    for (int i = 0; i < n; ++i) {
        Node y=nodes[i];
        while(y.parent!=-1){
            if(nodes[y.parent].l_kid==y.num){
                push(ps,0);
            } else push(ps,1);
            y=nodes[y.parent];
        }
        fprintf(pf,"%s\t",nodes[i].name);//打印名字
        while (ps->point!=-1) {
            fprintf(pf,"%d", pop(ps));//打印编码
        }
        fprintf(pf,"\n");
    }
    free(ps);
}
//========主程序==============
int main() {
    int n=0,k=4003*2-1;
    Node nodes[k];
    char names[]="s1.txt";//权重文件名称
    n=reading(nodes,names,n);
    create_list(nodes,n);
    connect(nodes,n);
    stack_code(nodes,n);
    return 0;
}