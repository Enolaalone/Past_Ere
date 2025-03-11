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
struct Student x;//排序交换中间结构体
int n=0;//结构体计数
int num1=0;//二分左界
int num2=372;//二分右界

void StructLSCreate(char *str) {
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
        else{
            printf("%s",words);
        }
    }
    printf("\n%d\n",n);
    fclose(fp);
}
void Compare1(){//学号排序
    int f;
    for(int i=0;i<372;i++){//比较373-1次
        f=i;
        for(int j=i+1;j<373;j++){//从i+1开始和i比较找到最小的
            if(students[f].st_num>students[j].st_num)
                f=j;
        }
        //交换
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
    printf("\n\n");
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
    printf("\n\n");
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
void AveForward(int l){//向后递归-
    if(students[l-1].average!=students[l].average || l-1<0){//递归边界
        return;
    }
    printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[l-1].num,
           students[l-1].st_num, students[l-1].name, students[l-1].sex, students[l-1].class,
           students[l-1].grade1, students[l-1].grade2, students[l-1].grade3,
           students[l-1].average);

    AveForward(l-1);
}

void AveBack(int l) {//向前递归找平均分相同的
    if (students[l + 1].average != students[l].average || l + 1 > 372) {
        return;
    }
    printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[l + 1].num,
           students[l + 1].st_num, students[l + 1].name, students[l + 1].sex, students[l + 1].class,
           students[l + 1].grade1, students[l + 1].grade2, students[l + 1].grade3,
           students[l + 1].average);
    AveForward(l + 1);
}
int main(){
    char E[100];//键盘获取数据
    char word_0[9][25]={{"序号"},{"学号"},{"姓名"},{"性别"},{"行政班"},{"进制转换"},{"多进制转换"},{"数值表达逻辑代数"},{"平均分"}};//表头
    int k;//学号
    int result;//汉字
    int ag;//平均分
    StructLSCreate("./Grade.txt");//结构体数组
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
            k = atoi(E);//字符串学号转化成整数
            while (1) {
                if (students[(num1 + num2) / 2].st_num == k || students[num1].st_num == k || //找到
                    students[num2].st_num == k) {
                    printf("%-8s%-15s%-11s%-11s%-13s%-13s%-18s%-20s%-12s\n", word_0[0], word_0[1], word_0[2], word_0[3],
                           word_0[4], word_0[5], word_0[6], word_0[7], word_0[8]);
                    if (students[(num1 + num2) / 2].st_num == k) {
                        printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[(num1 + num2) / 2].num,
                               students[(num1 + num2) / 2].st_num, students[(num1 + num2) / 2].name,
                               students[(num1 + num2) / 2].sex, students[(num1 + num2) / 2].class,
                               students[(num1 + num2) / 2].grade1, students[(num1 + num2) / 2].grade2,
                               students[(num1 + num2) / 2].grade3, students[(num1 + num2) / 2].average);
                        break;
                    }
                    if (students[num1].st_num == k) {
                        printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[num1].num,
                               students[num1].st_num, students[num1].name, students[num1].sex, students[num1].class,
                               students[num1].grade1, students[num1].grade2, students[num1].grade3,
                               students[num1].average);
                        break;
                    }
                    if (students[num2].st_num == k) {
                        printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[num2].num,
                               students[num2].st_num, students[num2].name, students[num2].sex, students[num2].class,
                               students[num2].grade1, students[num2].grade2, students[num2].grade3,
                               students[num2].average);
                        break;
                    }


                }
                if (num1 == num2 || num1==num2-1) {//列表找完+
                    printf("没找到,请重试\n");
                    break;
                }
                if (students[(num1 + num2) / 2].st_num > k)
                    num2 =-1+(num1 + num2) / 2;
                if (students[(num1 + num2) / 2].st_num < k)
                    num1 = 1+(num1 + num2) / 2;
            }
        }
        else if (E[0] == '2') {
            Compare2();
            printf("输入姓名查询\n");//界面
            gets(E);//数据输入

            while (1) {
                if (strcoll(students[(num1 + num2) / 2].name,E)==0||strcoll(students[num1].name,E)==0 ||
                    strcoll(students[num2].name,E)==0) {
                    printf("%-8s%-15s%-11s%-11s%-13s%-13s%-18s%-20s%-12s\n", word_0[0], word_0[1], word_0[2], word_0[3],
                           word_0[4], word_0[5], word_0[6], word_0[7], word_0[8]);
                    if (strcoll(students[(num1 + num2) / 2].name,E)==0) {
                        printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[(num1 + num2) / 2].num,
                               students[(num1 + num2) / 2].st_num, students[(num1 + num2) / 2].name,
                               students[(num1 + num2) / 2].sex, students[(num1 + num2) / 2].class,
                               students[(num1 + num2) / 2].grade1, students[(num1 + num2) / 2].grade2,
                               students[(num1 + num2) / 2].grade3, students[(num1 + num2) / 2].average);
                        break;
                    }
                    if (strcoll(students[num1].name,E)==0) {
                        printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[num1].num,
                               students[num1].st_num, students[num1].name, students[num1].sex, students[num1].class,
                               students[num1].grade1, students[num1].grade2, students[num1].grade3,
                               students[num1].average);
                        break;
                    }
                    if (strcoll(students[num2].name,E)==0) {
                        printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[num2].num,
                               students[num2].st_num, students[num2].name, students[num2].sex, students[num2].class,
                               students[num2].grade1, students[num2].grade2, students[num2].grade3,
                               students[num2].average);
                        break;
                    }

                }
                if (num1 == num2 || num1==num2-1) {
                    printf("没找到,请重试\n");
                    break;
                }
                if (strcoll(students[(num1 + num2) / 2].name,E)>0)
                    num2 =-1+(num1 + num2) / 2;
                if (strcoll(students[(num1 + num2) / 2].name,E)<0)
                    num1 = 1+(num1 + num2) / 2;
            }

        }
        else if(E[0] == '3'){
            Compare3();
            printf("输入平均分查询\n");//界面
            gets(E);//数据输入
            k = atoi(E);
            while (1) {
                if (students[(num1 + num2) / 2].average == k || students[num1].average == k ||
                    students[num2].average == k) {
                    printf("%-8s%-15s%-11s%-11s%-13s%-13s%-18s%-20s%-12s\n", word_0[0], word_0[1], word_0[2], word_0[3],
                           word_0[4], word_0[5], word_0[6], word_0[7], word_0[8]);
                    if (students[(num1 + num2) / 2].average == k) {
                        printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[(num1 + num2) / 2].num,
                               students[(num1 + num2) / 2].st_num, students[(num1 + num2) / 2].name,
                               students[(num1 + num2) / 2].sex, students[(num1 + num2) / 2].class,
                               students[(num1 + num2) / 2].grade1, students[(num1 + num2) / 2].grade2,
                               students[(num1 + num2) / 2].grade3, students[(num1 + num2) / 2].average);
                        AveForward((num1 + num2) / 2);
                        AveBack((num1 + num2) / 2);
                        break;

                    }
                    if (students[num1].average == k) {
                        printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[num1].num,
                               students[num1].st_num, students[num1].name, students[num1].sex, students[num1].class,
                               students[num1].grade1, students[num1].grade2, students[num1].grade3,
                               students[num1].average);
                        AveBack(num1);
                        break;
                    }
                    if (students[num2].average == k) {
                        printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[num2].num,
                               students[num2].st_num, students[num2].name, students[num2].sex, students[num2].class,
                               students[num2].grade1, students[num2].grade2, students[num2].grade3,
                               students[num2].average);
                        AveForward(num2);
                        break;
                    }

                }
                if (num1 == num2 || num1==num2-1) {
                    printf("没找到,请重试\n");
                    break;
                }
                if (students[(num1 + num2) / 2].average > k)
                    num2 =-1+(num1 + num2) / 2;
                if (students[(num1 + num2) / 2].average < k)
                    num1 = 1+(num1 + num2) / 2;
            }
        }
        else
            printf("错误从新输入\n");

    }
    return 0;

}