#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define M 100
bool is[256];
//Hash数据结构
typedef struct aList{//链
    int num;//数组位置
    struct aList*next;//下一链接地址
}*L;//指针名称

typedef struct AOVList{
    int num;//序号
    char name[25];//项目名称
    L next;//链
}AL,*ALP;

void Read(char *word,AL p[]){//解析数组，入度
    int i=1,k,in_num=0;//从第一个开始检测
    k=(int)(word[0]-'A');
    if(word[0]>='A' && word[0]<='Z' ){//命名
        if( !is[word[0]]){
            p[k].name[0]=word[0];//名称
            p[k].name[1]='\0';//结束
            is[word[0]]=true;
        }
    } else return;//非字符结束

    while(word[i]!='\0'){
        if(word[i]>='A' && word[i]<='Z'){
            in_num++;
            k=(int)(word[i]-'A');
            if(!is[word[i]]){//命名
                p[k].name[0]=word[i];//名称
                p[k].name[1]='\0';//结束
                is[word[i]]=true;
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
        i++;
    }
    p[(int)(word[0]-'A')].num=in_num;
}


int main() {
    int i=0;//数组长度
    char word[30];
    ALP p=(ALP) malloc(M*sizeof (AL));//分配内存
    for (int j = 0; j < M; ++j) {
        p[j].next=NULL;
    }
    FILE *fp= fopen("./p01.txt","r");
    while(fgets(word,sizeof (word),fp)!=NULL){
        Read(word,p);
    }

    //------------------打印--------------------
    printf("序号\t可入度\t名称\t后续项目\n");
    while(p[i].name[0]>='A'&& p[i].name[0]<='Z'){
        printf("%d\t%d\t%s\t",i,p[i].num,p[i].name);
        for (L j =p[i].next; j !=NULL ; j=j->next) {
            printf("->%d",j->num);
        }
        printf("\n");
        i++;
    }
    printf("数量：%d",i);

    fclose(fp);
    free(p);
    return 0;
}