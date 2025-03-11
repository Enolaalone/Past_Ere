#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
struct Student{
    int num;//���
    int st_num;//ѧ��
    char name[20];//����
    char sex[20];//�Ա�
    char class[30];//������
    int grade1;//
    int grade2;//
    int grade3;//
    int average;//ƽ��
};

struct Student students[373];
struct Student x;
int n=0;
int num1=0;
int num2=372;
char word_0[9][25]={{"���"},{"ѧ��"},{"����"},{"�Ա�"},{"������"},{"����ת��"},{"�����ת��"},{"��ֵ����߼�����"},{"ƽ����"}};//��ͷ
char E[100];//���̻�ȡ����
int k;//ѧ��
void Print(int P){//��ӡ
    printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[P].num,
           students[P].st_num, students[P].name, students[P].sex, students[P].class,
           students[P].grade1, students[P].grade2, students[P].grade3,
           students[P].average);
}
void StructLSCreate(char *str) {//��ȡ�ı��ļ���������
    char words[200];//�������ݴ��
    FILE *fp = fopen(str, "r");//���ļ�
    while (fgets(words, 200, fp) != NULL) {//���ж�ȡ
//        printf("%s",words);
        if (sscanf(words, "%d %d %s %s %s %d %d %d %d", &students[n].num, &students[n].st_num,//��ȡ��ʽ������
                   students[n].name, students[n].sex, students[n].class, &students[n].grade1, &students[n].grade2,
                   &students[n].grade3, &students[n].average) == 9) {
//            printf("%d��%d��%s��%s��%s��%d��%d��%d��%d\n",students[n].num,students[n].st_num,students[n].name,students[n].sex,students[n].class,students[n].grade1,students[n].grade2,students[n].grade3,students[n].average);
            n++;
        }
//        else{
//            printf("%s",words);//����Ƿ���δ��ȡ������
//        }
    }
//    printf("\n%d\n",n);
    fclose(fp);
}
void Compare1(){//ѧ������
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
//        printf("%d��%d��%s��%s��%s��%d��%d��%d��%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average);
//    }
}

void Compare2(){//��������
    int f;
    int result;
    setlocale(LC_COLLATE,"zh_CN.GBK");//���ػ��ַ�������
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
//        printf("%d��%d��%s��%s��%s��%d��%d��%d��%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average);
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
//        printf("%d��%d��%s��%s��%s��%d��%d��%d��%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average);
//    }
}
void AveForward(int l){//�ݹ�Ѱ����ͬ��ƽ����
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

void XueD(int n1,int n2){//��ѧ�Ŷ��ֲ���--�ݹ�
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
    if (n1 == n2 || n1==n2-1) {//�б������
        printf("û�ҵ�,������\n");
        return;
    }
    if (students[(n1 + n2) / 2].st_num > k)
        n2 =-1+(n1 + n2) / 2;
    if (students[(n1 + n2) / 2].st_num < k)
        n1 = 1+(n1 + n2) / 2;
    XueD(n1,n2);//------------------------------�ݹ�
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
        printf("û�ҵ�,������\n");
        return;
    }
    if (strcoll(students[(n1 + n2) / 2].name,E)>0)
        n2 =-1+(n1 + n2) / 2;
    if (strcoll(students[(n1 + n2) / 2].name,E)<0)
        n1 = 1+(n1 + n2) / 2;
    NameD(n1,n2);//------------------------------�ݹ�
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
        printf("û�ҵ�,������\n");
        return;
    }
    if (students[(n1 + n2) / 2].average > k)
        n2 =-1+(n1 + n2) / 2;
    if (students[(n1 + n2) / 2].average < k)
        n1 = 1+(n1 + n2) / 2;
    AverageD(n1,n2);//------------------------------�ݹ�

}

//-----------------������
int main(){
    StructLSCreate("./Grade.txt");//�ṹ�����鹹��
    while(1){
        num1=0;
        num2=372;
        printf("1.ѧ�Ų�ѯ 2.������ѯ 3.ƽ���ֲ�ѯor��e�˳�\n");//����
        gets(E);//��������
        if(E[0]=='e')
            break;//�˳�
        else if(E[0]=='1') {
            Compare1();
            printf("����ѧ�Ų�ѯ\n");//����
            gets(E);//��������
            k = atoi(E);//ѧ��תΪ����
            XueD(num1,num2);

        }
        else if(E[0]=='2'){
            Compare2();
            printf("����������ѯ\n");
            gets(E);
            NameD(num1,num2);
        }
        else if(E[0]=='3'){
            Compare3();
            printf("����ƽ����\n");
            gets(E);
            k = atoi(E);
            AverageD(num1,num2);
        }
        else
            printf("�����������\n");

    }
    return 0;

}