#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Student *list;
struct Student{
    int num;//序号
    int st_num;//学号
    char name[20];//姓名
    char sex[20];//性别
    char class[20];//行政班
    int grade1;//
    int grade2;//
    int grade3;//
    int average;//平均
};

struct Student *students[500];//结构体数组
int n=0;

void StructLSCreate(char *str) {
    char words[100];//单行数据存放
    FILE *fp = fopen(str, "r");//打开文件
    while (fgets(words, 100, fp) != NULL) {//单行读取
        students[n] = (struct Student *) malloc(sizeof(struct Student));//开辟内存地址
        if (sscanf(words, "%d，%d，%[^，]，%[^，]，%[^，]，%d，%d，%d，%d\n", &students[n]->num, &students[n]->st_num,//读取格式化数据
                   students[n]->name, students[n]->sex, students[n]->class, &students[n]->grade1, &students[n]->grade2,
                   &students[n]->grade3, &students[n]->average) == 9) {
//            printf("%d，%d，%s，%s，%s，%d，%d，%d，%d\n",students[n]->num,students[n]->st_num,students[n]->name,students[n]->sex,students[n]->class,students[n]->grade1,students[n]->grade2,students[n]->grade3,students[n]->average);
            n++;
        }
    }
    fclose(fp);
}
int main() {
    bool finding=false;//确定是否找到
    char E[25];//键盘获取数据
    char word_0[9][25]={{"序号"},{"学号"},{"姓名"},{"性别"},{"行政班"},{"进制转换"},{"多进制转换"},{"数值表达逻辑代数"},{"平均分"}};//表头
    int num_try=0;//确定是否为学号
    StructLSCreate("./new598854课程.txt");
    StructLSCreate("./new598856课程.txt");
    StructLSCreate("./new598858课程.txt");
    while(1){
        finding=false;//初始化数据
        printf("输入姓名或学号查询or按e退出\n");//界面
        gets(E);//数据输入
        if(E[0]=='e')
            break;//退出
        else{
            for(int i=0;i<n;i++){
                num_try=atoi(E);//字符串转整数
                if(num_try!=0){//确定输入的是字符串
                    if(num_try==students[i]->st_num){//如果是学号且相等
                        finding=true;//标记找到
                        printf("%-8s%-15s%-11s%-11s%-13s%-13s%-18s%-20s%-12s\n",word_0[0],word_0[1],word_0[2],word_0[3],word_0[4],word_0[5],word_0[6],word_0[7],word_0[8]);
                        printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n",students[i]->num,students[i]->st_num,students[i]->name,students[i]->sex,students[i]->class,students[i]->grade1,students[i]->grade2,students[i]->grade3,students[i]->average);
                    }
                       
                }
                else if(strcmp(students[i]->name,E)==0){
                    finding=true;
                    printf("%-8s%-15s%-11s%-11s%-13s%-13s%-18s%-20s%-12s\n",word_0[0],word_0[1],word_0[2],word_0[3],word_0[4],word_0[5],word_0[6],word_0[7],word_0[8]);
                    printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n",students[i]->num,students[i]->st_num,students[i]->name,students[i]->sex,students[i]->class,students[i]->grade1,students[i]->grade2,students[i]->grade3,students[i]->average);
                }
            }
            if(!finding)//否则没找到
                printf("没找到,请重试\n");
        }

    }
    return 0;
}