#include <stdio.h>
#include <string.h>

typedef struct Node{
    char name[10];
    int weight;
    int parent;
    int l_kid;
    int r_kid;
}Node;
char x='/';

//A,3,B,14,C,8,D,7,E,8
int input( int lt_w[],char lt[],int *n){
    int i=0,j=0;
    char words[200];
    fgets(words, sizeof(words), stdin);//读取一行缓冲区内容
    while (words[i] != '\0') {
        if ((words[i] >= 'A' && words[i] <= 'Z') || (words[i] >= 'a' && words[i] <= 'z')) {
            lt[j] = words[i];//读取名称
            i++;
        } else if (words[i] >= '0' && words[i] <= '9') {
            int num = 0;
            while (words[i] >= '0' && words[i] <= '9') {//读取一个完整的整数
                num = 10 * num + (int) (words[i] - '0');
                i++;
            }
            lt_w[j] = num;
            j++;//一对值读完加1
        } else i++;//跳过逗号
    }
    *n=j;
    return *n;

}

void create_list(Node nodes[],int n,const int lt_w[],const char lt[]){
    int k=2*n-1;
    for (int i = 0; i < k ; ++i) {
        if(i<n){
            nodes[i].name[0]=lt[i];//名称
            nodes[i].name[1]='\0';//名称

            nodes[i].weight=lt_w[i];//权重
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

    }
}

void swap(int *s1,int *s2){
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

void connect(Node nodes[],int n){
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
        //=======取名字========
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
    char lt[100],words[5][20]={"名称","权重","父节点位置","左子节点位置","右子节点位置"};
    printf("请输入字母和权重：\n");
    fflush(stdin);
    n=input(lt_w,lt,&n);//输入叶子节点
    printf("%d\n",n);
    //=======数组初始化============
    int k=2*n-1;//节点数2n-1
    Node nodes[k];//节点数组
    create_list(nodes,n,lt_w,lt);

    //======找到最小和次小的数,依次连接=======
    connect(nodes,n);
    //==============打印输出===============
    printf("%-10s\t%-10s\t%-15s\t%-15s\t%-15s\t\n",words[0],words[1],words[2],words[3],words[4]);
    print(nodes[k-1],nodes);


    return 0;
}