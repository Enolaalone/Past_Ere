#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack{//ջ
    int point;
    int data[200];
}Stack;

void push(Stack* p,int s){//��ջ
    p->point++;
    p->data[p->point]=s;
}
int pop(Stack* p){//��ջ
    if(p->point==-1)return -1;
    else{
        p->point--;
        return p->data[p->point+1];
    }
}

typedef struct Node{
    char name[10];
    int weight;
    int parent;
    int l_kid;
    int r_kid;
    int num;
}Node;
char x='/';

//A,3,B,14,C,8,D,7,E,8
int input( int lt_w[],char lt[],int *n){
    int i=0,j=0;
    char words[200];
    fgets(words, sizeof(words), stdin);//��ȡһ�л���������
    while (words[i] != '\0') {
        if ((words[i] >= 'A' && words[i] <= 'Z') || (words[i] >= 'a' && words[i] <= 'z')) {
            lt[j] = words[i];//��ȡ����
            i++;
        } else if (words[i] >= '0' && words[i] <= '9') {
            int num = 0;
            while (words[i] >= '0' && words[i] <= '9') {//��ȡһ������������
                num = 10 * num + (int) (words[i] - '0');
                i++;
            }
            lt_w[j] = num;
            j++;//һ��ֵ�����1
        } else i++;//��������
    }
    *n=j;
    return *n;

}

void create_list(Node nodes[],int n,const int lt_w[],const char lt[]){
    int k=2*n-1;
    for (int i = 0; i < k ; ++i) {
        if(i<n){
            nodes[i].name[0]=lt[i];//����
            nodes[i].name[1]='\0';//����

            nodes[i].weight=lt_w[i];//Ȩ��
            nodes[i].parent=-1;//���ڵ��������λ��
            nodes[i].l_kid=-1;//�ӽڵ�ָ���������λ��
            nodes[i].r_kid=-1;
        }else{
            strcpy(nodes[i].name,"\0");
            nodes[i].weight=0;//Ȩ��
            nodes[i].parent=-1;//���ڵ�ָ��������λ��
            nodes[i].l_kid=-1;//�ӽڵ�ָ���������λ��
            nodes[i].r_kid=-1;
        }
        nodes[i].num=i;

    }
}

void swap(int *s1,int *s2){
    int t;
    t=*s1;
    *s1=*s2;
    *s2=t;
}

void compare(Node nodes[],int s[],int k){//Ѱ����С�ʹ�С
    for (int i = 0; i < k; ++i) {
        if(nodes[i].parent==-1){
            s[0]=nodes[i].weight;//s[0]ΪȨ��
            s[1]=i;//λ��
            for (int j = i+1; j < k; ++j) {
                if(nodes[j].parent==-1){
                    s[2]=nodes[j].weight;//��СȨ��
                    s[3]=j;//λ��
                    break;
                }
            }
            break;
        }
    }
    if(s[0]>s[2]){//�����С���ڴ�С������λ��
        swap(&s[1],&s[3]);
        swap(&s[0],&s[2]);
    }

    for (int i = 0; i < k; ++i) {
        if(nodes[i].parent==-1 && i!=s[1] && i!=s[3]){
            if(nodes[i].weight<s[0]){//С����С�ỻ��С����С�Ƶ���С��
                s[2]=s[0];s[3]=s[1];
                s[0]=nodes[i].weight;s[1]=i;
            }
            else if(nodes[i].weight>=s[0] && nodes[i].weight<s[2]){//������С��С�ڴ�С�����������С
                s[2]=nodes[i].weight;s[3]=i;
            }
        }
    }
}

void connect(Node nodes[],int n){
    int k=2*n-1;//�ڵ���2n-1
    for (int i = 0; i < k-n; ++i) {
        int s[4];
        compare(nodes,s,n+i);

        nodes[n+i].weight=s[0]+s[2];//s[0] s[2]Ϊ�ӽڵ�Ȩ��
        //========λ��ȷ��========
        nodes[n+i].l_kid=s[1];
        nodes[n+i].r_kid=s[3];
        nodes[s[1]].parent=n+i;
        nodes[s[3]].parent=n+i;
        //=======ȡ����========
        strcpy(nodes[n+i].name,nodes[s[1]].name);
        strcat(nodes[n+i].name,nodes[s[3]].name);

//        printf("%d %d\n",nodes[s[1]].parent, nodes[s[3]].parent);
//        printf("%s,%d,%d,%d,%d\n",nodes[n+i].name,nodes[n+i].weight,nodes[n+i].parent,nodes[n+i].l_kid,nodes[n+i].r_kid);
    }

}
void print(Node node,Node nodes[]){
    printf("%-10s\t%-10d\t",node.name,node.weight);
    if(node.parent==-1)printf("%-15c\t",x);
    else printf("%-15d\t",node.parent);

    if(node.r_kid==-1 && node.l_kid==-1)printf("%-15c\t%-15c\t\n",x,x);
    else printf("%-15d\t%-15d\t\n",node.l_kid,node.r_kid);

    if(node.l_kid==-1 || node.r_kid==-1) return;
    print(nodes[node.l_kid],nodes);
    print(nodes[node.r_kid],nodes);
}


int main() {
    int lt_w[100],n=0;
    char lt[100],words[5][20]={"����","Ȩ��","���ڵ�λ��","���ӽڵ�λ��","���ӽڵ�λ��"};
    printf("��������ĸ��Ȩ�أ�\n");
    fflush(stdin);
    n=input(lt_w,lt,&n);//����Ҷ�ӽڵ�
    printf("%d\n",n);
    //=======�����ʼ��============
    int k=2*n-1;//�ڵ���2n-1
    Node nodes[k];//�ڵ�����
    create_list(nodes,n,lt_w,lt);

    //======�ҵ���С�ʹ�С����,��������=======
    connect(nodes,n);
    //==============��ӡ���===============
    printf("%-10s\t%-10s\t%-15s\t%-15s\t%-15s\t\n",words[0],words[1],words[2],words[3],words[4]);
    print(nodes[k-1],nodes);


    Stack *ps=(Stack*) malloc(sizeof (Stack));//��ջ
    ps->point=-1;
    for (int i = 0; i < n; ++i) {
        Node y=nodes[i];
        while(y.parent!=-1){
            if(nodes[y.parent].l_kid==y.num){
                push(ps,0);
            } else push(ps,1);
            y=nodes[y.parent];
        }
        printf("%s",nodes[i].name);//��ӡ����
        while (ps->point!=-1) {
            printf("%d", pop(ps));//��ӡ����
        }
        printf("\n");
    }
    free(ps);


    return 0;
}
