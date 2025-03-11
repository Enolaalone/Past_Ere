#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
struct Student{
    int num;//序号
    int st_num;//学号
    char name[20];//姓名
    char sex[20];//性别
    char class[30];//行政班
    int grade1;//
    int grade2;//
    int grade3;//
    int average;//平均
};

struct Student students[373];
struct Student x;
int n=0;
int num1=0;
int num2=372;
char word_0[9][25]={{"序号"},{"学号"},{"姓名"},{"性别"},{"行政班"},{"进制转换"},{"多进制转换"},{"数值表达逻辑代数"},{"平均分"}};//表头
char E[100];//键盘获取数据
int k;//学号
void Print(int P){//打印
    printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[P].num,
           students[P].st_num, students[P].name, students[P].sex, students[P].class,
           students[P].grade1, students[P].grade2, students[P].grade3,
           students[P].average);
}
void StructLSCreate(char *str) {//读取文本文件构建数组
    char words[200];//单行数据存放
    FILE *fp = fopen(str, "r");//打开文件
    while (fgets(words, 200, fp) != NULL) {//单行读取
//        printf("%s",words);
        if (sscanf(words, "%d %d %s %s %s %d %d %d %d", &students[n].num, &students[n].st_num,//读取格式化数据
                   students[n].name, students[n].sex, students[n].class, &students[n].grade1, &students[n].grade2,
                   &students[n].grade3, &students[n].average) == 9) {
//            printf("%d，%d，%s，%s，%s，%d，%d，%d，%d\n",students[n].num,students[n].st_num,students[n].name,students[n].sex,students[n].class,students[n].grade1,students[n].grade2,students[n].grade3,students[n].average);
            n++;
        }
//        else{
//            printf("%s",words);//检测是否有未读取的数据
//        }
    }
//    printf("\n%d\n",n);
    fclose(fp);
}
void Compare1(){//学号排序
    int f;
    printf("\n");
    for(int i=0;i<372;i++){
        f=i;
        for(int j=i+1;j<373;j++){
            if(students[f].st_num>students[j].st_num)
                f=j;
        }
        x=students[i];
        students[i]=students[f];
        students[f]=x;
    }
//    for(int i=0;i<373;i++){
//        printf("%d，%d，%s，%s，%s，%d，%d，%d，%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average);
//    }
}

void Compare2(){//姓名排序
    int f;
    int result;
    setlocale(LC_COLLATE,"zh_CN.GBK");//本地化字符串排序
    printf("\n");
    for(int i=0;i<372;i++){
        f=i;
        for(int j=i+1;j<373;j++){
            result= strcoll(students[f].name,students[j].name);
            if(result>0)//students[f].name>students[j].name
                f=j;
        }
        x=students[i];
        students[i]=students[f];
        students[f]=x;
    }
//    for(int i=0;i<373;i++){
//        printf("%d，%d，%s，%s，%s，%d，%d，%d，%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average);
//    }
}
void Compare3(){
    int f;
    printf("\n");
    for(int i=0;i<372;i++){
        f=i;
        for(int j=i+1;j<373;j++){
            if(students[f].average>students[j].average)
                f=j;
        }
        x=students[i];
        students[i]=students[f];
        students[f]=x;
    }
//    for(int i=0;i<373;i++){
//        printf("%d，%d，%s，%s，%s，%d，%d，%d，%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average);
//    }
}
void AveForward(int l){//递归寻找相同的平均分
    if(students[l-1].average!=students[l].average || l-1<0){
        return;
    }
    Print(l-1);
    AveForward(l-1);
}

void AveBack(int l) {
    if (students[l + 1].average != students[l].average || l + 1 > 372) {
        return;
    }
    Print(l+1);
    AveBack(l + 1);
}

void XueD(int n1,int n2){//按学号二分查找--递归
    if (students[(n1 + n2) / 2].st_num == k || students[n1].st_num == k ||
        students[n2].st_num == k) {
        printf("%-8s%-15s%-11s%-11s%-13s%-13s%-18s%-20s%-12s\n", word_0[0], word_0[1], word_0[2], word_0[3],
               word_0[4], word_0[5], word_0[6], word_0[7], word_0[8]);
        if (students[(n1 + n2) / 2].st_num == k) {
            Print((n1 + n2) / 2);
            return;
        }
        if (students[n1].st_num == k) {
            Print(n1);
            return;
        }
        if (students[n2].st_num == k) {
            Print(n2);
            return;
        }

    }
    if (n1 == n2 || n1==n2-1) {//列表查找完
        printf("没找到,请重试\n");
        return;
    }
    if (students[(n1 + n2) / 2].st_num > k)
        n2 =-1+(n1 + n2) / 2;
    if (students[(n1 + n2) / 2].st_num < k)
        n1 = 1+(n1 + n2) / 2;
    XueD(n1,n2);//------------------------------递归
}

void NameD(int n1,int n2){
    if (strcoll(students[(n1 + n2) / 2].name,E)==0||strcoll(students[n1].name,E)==0 ||
        strcoll(students[n2].name,E)==0) {
        printf("%-8s%-15s%-11s%-11s%-13s%-13s%-18s%-20s%-12s\n", word_0[0], word_0[1], word_0[2], word_0[3],
               word_0[4], word_0[5], word_0[6], word_0[7], word_0[8]);
        if (strcoll(students[(n1 + n2) / 2].name,E)==0) {
            Print((n1 + n2) / 2);
            return;
        }
        if (strcoll(students[n1].name,E)==0) {
            Print(n1);
            return;
        }
        if (strcoll(students[n2].name,E)==0) {
            Print(n2);
            return;
        }

    }
    if (n1 == n2 || n1==n2-1) {
        printf("没找到,请重试\n");
        return;
    }
    if (strcoll(students[(n1 + n2) / 2].name,E)>0)
        n2 =-1+(n1 + n2) / 2;
    if (strcoll(students[(n1 + n2) / 2].name,E)<0)
        n1 = 1+(n1 + n2) / 2;
    NameD(n1,n2);//------------------------------递归
}

void AverageD(int n1,int n2){
    if (students[(n1 + n2) / 2].average == k || students[n1].average == k ||
        students[n2].average == k) {
        printf("%-8s%-15s%-11s%-11s%-13s%-13s%-18s%-20s%-12s\n", word_0[0], word_0[1], word_0[2], word_0[3],
               word_0[4], word_0[5], word_0[6], word_0[7], word_0[8]);
        if (students[(n1 + n2) / 2].average == k) {
            Print((n1 + n2) / 2);
            AveForward((n1 + n2) / 2);
            AveBack((n1 + n2) / 2);
            return;
        }
        if (students[n1].average == k) {
            Print(n1);
            AveBack(n1);
            return;
        }
        if (students[n2].average == k) {
            Print(n2);
            AveForward(n2);
            return;
        }

    }
    if (n1 == n2 || n1==n2-1) {
        printf("没找到,请重试\n");
        return;
    }
    if (students[(n1 + n2) / 2].average > k)
        n2 =-1+(n1 + n2) / 2;
    if (students[(n1 + n2) / 2].average < k)
        n1 = 1+(n1 + n2) / 2;
    AverageD(n1,n2);//------------------------------递归

}

//-----------------主函数
int main(){
    StructLSCreate("./Grade.txt");//结构体数组构建
    while(1){
        num1=0;
        num2=372;
        printf("1.学号查询 2.姓名查询 3.平均分查询or按e退出\n");//界面
        gets(E);//数据输入
        if(E[0]=='e')
            break;//退出
        else if(E[0]=='1') {
            Compare1();
            printf("输入学号查询\n");//界面
            gets(E);//数据输入
            k = atoi(E);//学号转为整数
            XueD(num1,num2);

        }
        else if(E[0]=='2'){
            Compare2();
            printf("输入姓名查询\n");
            gets(E);
            NameD(num1,num2);
        }
        else if(E[0]=='3'){
            Compare3();
            printf("输入平均分\n");
            gets(E);
            k = atoi(E);
            AverageD(num1,num2);
        }
        else
            printf("错误从新输入\n");

    }
    return 0;

}