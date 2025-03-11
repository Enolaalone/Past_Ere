#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>//INT_MAX
#define M 100
bool is[256];//记录拓扑

//Hash数据结构
typedef struct aList{//链
    int num;//数组位置
    struct aList*next;//下一链接地址
}*L;//指针名称

typedef struct AOVList{
    int num;//可入度
    char name[5];//项目名称
    int pass;//是否遍历--------------------------------------------------------
    int weight;//时间----------------------------------------------------------------------------------------------------
    L next;//链
}AL,*ALP;
//----------------栈-------------------
typedef struct Stack{
    int pointer;//指针
    ALP data[50];//数据
}Stack,*list;

void push(list s,ALP c){//地址入栈
    s->pointer++;
    s->data[s->pointer]=c;
}

ALP pop(list s){//返回地址
    if(s->pointer==-1) return NULL;
    else{
        s->pointer--;
        return s->data[s->pointer+1];
    }
}
//--------------------------------------------
void Read(char *word,AL p[]){//解析数组，入度
    int i=1,k,in_num=0;//从第一个开始检测
    k=(int)(word[0]-'A');
    if(word[0]>='A' && word[0]<='Z' ){//命名
        if( !is[word[0]]){
            p[k].name[0]=word[0];//名称
            p[k].name[1]='\0';//结束
            is[word[0]]=true;//建立了相应邻接表
        }
    } else return;//非字符结束

    while(word[i]!='\0'){
        if(word[i]>='A' && word[i]<='Z'){
            in_num++;
            k=(int)(word[i]-'A');
            if(!is[word[i]]){//命名
                p[k].name[0]=word[i];//名称
                p[k].name[1]='\0';//结束
                is[word[i]]=true;//建立了相应邻接表
            }
            if(p[k].next==NULL) {
                p[k].next=(L) malloc(sizeof (struct aList));//分配内存
                p[k].next->num=(int)(word[0]-'A');//链地址
                p[k].next->next=NULL;
            } else {
                L L_p=p[k].next;
                while(1)  {
                    if(L_p->next!=NULL){
                        L_p=L_p->next;
                        continue;
                    } else{
                        L_p->next=(L) malloc(sizeof (struct aList));
                        L_p->next->num=(int)(word[0]-'A');
                        L_p->next->next=NULL;
                        break;
                    }
                }
            }
        }
        else if(word[i]>='0' && word[i]<='9'){//------------------------------------------------------------------------
            p[(int)(word[0]-'A')].weight=10*p[(int)(word[0]-'A')].weight+(int)(word[i]-'0');
        }//-------------------------------------------------------------------------------------------------------------
        i++;
    }
    p[(int)(word[0]-'A')].num=in_num;
}

void print(AL p[],int *i){
    //------------------打印--------------------
    printf("序号\t可入度\t名称\t时间权重\t后续项目\n");
    while(p[*i].name[0]>='A'&& p[*i].name[0]<='Z'){
        printf("%d\t%d\t%s\t%d\t",*i,p[*i].num,p[*i].name,p[*i].weight);//----------------------------------------------------
        for (L j =p[*i].next; j !=NULL ; j=j->next) {
            printf("->%d",j->num);
        }
        printf("^\n");
        (*i)++;
    }
    printf("顶点数量：%d\n",*i);
    //---------------------------------------
}
bool Compare(AL p[],int i){//排序数组 返回闭环位置
    //-----------------排序-----------------
    ALP ap0,ap1;//单个表单的地址
    int put_l=0;//输出长度
    list ps=(list) malloc(sizeof (Stack));//建栈
    ps->pointer=-1;//初始化栈指针
    printf("排序结果：\n");
    for (int j = 0; j < i; ++j) {
        if(p[j].num==0) push(ps,&p[j]);//入栈
    }
    ap0= pop(ps);
    while (ap0!=NULL) {
        printf("%s\t",ap0->name);
        is[ap0->name[0]]= false;//节点已经输出----------------------------
        put_l++;
        for (L j = ap0->next; j != NULL; j = j->next) {
            p[j->num].num--;//可入度-1
            if (p[j->num].num == 0) push(ps, &p[j->num]);//可入度为0 入栈
        }
        ap1=ap0;//当有闭环时候确定位置
        ap0= pop(ps);
    }
    //--------------闭环处理---------------------
    if(put_l<i){
        printf("有闭环\n");
        return false;
    } else return true;
    //-----------------------------------------
}

ALP Circle(int num,AL p[]){
    L ql;
    p[num].pass=1;//正在访问
    if(p[num].next==NULL) {//如果无邻接链
        p[num].pass=-1;//结束访问
        return NULL;
    }
    ql=p[num].next;
    do{
        if(p[ql->num].pass==1) return &p[ql->num];//环，邻接节点访问过
        if(p[ql->num].pass==0 && Circle(ql->num,p)!=NULL) return &p[ql->num];//环，邻接节点未访问过，递归过程发现访问过的节点

        ql=ql->next;//跳转邻接节点
    }while(ql!=NULL);
    p[num].pass=-1;//结束访问
    return NULL;

}

void JudgeCircle(int i,AL p[]){
    printf("发现环：");
    for (int j = 0; j < i; ++j) {
        ALP CL=Circle(j,p);
        if(CL!=NULL && is[CL->name[0]]){//打印没有输出的部分
            is[CL->name[0]]=false;//相当环已经输出
            printf("%s\t",CL->name);
        }
    }


}

void dijkstra(AL p[],int pre[],int dtc[],int source,int i){
    bool visited[i];//是否访问
    for (int j = 0; j < i; ++j) {//初始化
        visited[j]=false;
        pre[j]=-1;
        dtc[j]=INT_MAX;//无穷大
    }
    dtc[source]=0;//A到本身距离为0
    int n;//到原点距离最小数组序号
    for (int j = 0; j < i-1; ++j) {//遍历i-1次
        int min=INT_MAX;
        for (int k = 0; k < i; ++k) {//遍历dtc找到路径最短
            if(!visited[k]&&dtc[k]<min){
                min=dtc[k];
                n=k;
            }
        }
        visited[n]=true;//节点找到

        // 更新当前最短路径和前驱顶点
        // 即，更新"未获取最短路径的顶点的最短路径和前驱顶点"。

        L ql=p[n].next;//相邻节点链接
        while(ql){
            if(!visited[ql->num]&&p[n].weight+dtc[n]<dtc[ql->num]&&dtc[n]!=INT_MAX){
                dtc[ql->num]=p[n].weight+dtc[n];//更新相邻节点路长
                pre[ql->num]=n;//ql->num的前驱节点为n
            }
            ql=ql->next;
        }
    }
}

void PrintWay(int pre[],AL p[],int n){
    if(pre[n]==-1){
        printf("%s",p[n].name);
        return;
    }
    PrintWay(pre,p,pre[n]);
    printf("->%s",p[n].name);
}

int main() {
    int i=0;//数组长度
    char word[30],input_name[30];
    printf("输入文件名：");
    fflush(stdin);
    gets(input_name);
    ALP p=(ALP) malloc(M*sizeof (AL));//分配内存
    for (int j = 0; j < M; ++j) {//初始化
        p[j].next=NULL;
        p[j].pass=0;
    }
    FILE *fp= fopen(input_name,"r");//----------------------------------文本
    while(fgets(word,sizeof (word),fp)!=NULL){
        Read(word,p);
    }
    fclose(fp);
    //---------打印输出-------------------
    print(p,&i);
    //----------排序-----闭环-------------
    if(!Compare(p,i))JudgeCircle(i,p);
    //---------最短序列----------------
    else{
        printf("无环路\n");
        int dtc[i];//距离
        int pre[i];//前节点
        int source=0;//A节点
        dijkstra(p,pre,dtc,source,i);
        for (int j = 1; j < i; ++j) {
            printf("A To %s: ",p[j].name);
            PrintWay(pre,p,j);
            printf("\n");
        }
    }
    gets(input_name);
    free(p);//释放内存
    return 0;
}