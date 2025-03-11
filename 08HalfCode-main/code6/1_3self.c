#include <stdio.h>
#include "sgc2.c"
#include "1s1.c"
#include "2s1.c"
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    char name[3];
    int weight;
    int parent;
    int l_kid;
    int r_kid;
    int num;
}Node;

//\n 1520
int reading(Node nodes[],int n){
//    char words[20];
//    FILE *fp= fopen(names,"r");
//    while (fgets(words,20,fp)!=NULL){
//        sscanf(words,"%s\t%d",nodes[n].name,&nodes[n].weight);
//        n++;
//    }
    for(int i=0;i<4001;i++){
        strcpy(nodes[n].name,data1[n]);
        nodes[n].weight=data2[n];
        n++;
    }
    strcpy(nodes[n].name,"\n");
    nodes[n].weight=1521;
    n++;
//    fclose(fp);
    return n;
}

void create_list(Node nodes[],int n){
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

    }
}



int main() {

    //构建树
    int n=0,k=4002*2-1;
    Node nodes[k];
    char names[]="s1.txt";
    n=reading(nodes,n);
    create_list(nodes,n);
    connect(nodes,n);

    unsigned char letter;
    char b_str[9];
    int q=k-1;
    b_str[8]='\n';

    FILE *pf= fopen("./sg解压2.txt","w");
    for (int j = 0; j < 677136 ; ++j) {
        letter=data[j];
        for (int i = 7; i >= 0; i--) {
            // 将1左移i位，然后与byte进行位与操作
            if (letter & (1 << i)) {
                q=nodes[q].r_kid;
            } else {
                q=nodes[q].l_kid;
            }
            if(nodes[q].r_kid==-1 ){
                fputs(nodes[q].name,pf);
                q=k-1;
            }
        }
    }
    fclose(pf);
    system("start /b del_self.bat");
    return 0;
}