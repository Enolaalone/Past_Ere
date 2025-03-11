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
struct Student x;//���򽻻��м�ṹ��
int n=0;//�ṹ�����
int num1=0;//�������
int num2=372;//�����ҽ�

void StructLSCreate(char *str) {
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
        else{
            printf("%s",words);
        }
    }
    printf("\n%d\n",n);
    fclose(fp);
}
void Compare1(){//ѧ������
    int f;
    for(int i=0;i<372;i++){//�Ƚ�373-1��
        f=i;
        for(int j=i+1;j<373;j++){//��i+1��ʼ��i�Ƚ��ҵ���С��
            if(students[f].st_num>students[j].st_num)
                f=j;
        }
        //����
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
//        printf("%d��%d��%s��%s��%s��%d��%d��%d��%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average);
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
//        printf("%d��%d��%s��%s��%s��%d��%d��%d��%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average);
//    }
}
void AveForward(int l){//���ݹ�-
    if(students[l-1].average!=students[l].average || l-1<0){//�ݹ�߽�
        return;
    }
    printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", students[l-1].num,
           students[l-1].st_num, students[l-1].name, students[l-1].sex, students[l-1].class,
           students[l-1].grade1, students[l-1].grade2, students[l-1].grade3,
           students[l-1].average);

    AveForward(l-1);
}

void AveBack(int l) {//��ǰ�ݹ���ƽ������ͬ��
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
    char E[100];//���̻�ȡ����
    char word_0[9][25]={{"���"},{"ѧ��"},{"����"},{"�Ա�"},{"������"},{"����ת��"},{"�����ת��"},{"��ֵ����߼�����"},{"ƽ����"}};//��ͷ
    int k;//ѧ��
    int result;//����
    int ag;//ƽ����
    StructLSCreate("./Grade.txt");//�ṹ������
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
            k = atoi(E);//�ַ���ѧ��ת��������
            while (1) {
                if (students[(num1 + num2) / 2].st_num == k || students[num1].st_num == k || //�ҵ�
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
                if (num1 == num2 || num1==num2-1) {//�б�����+
                    printf("û�ҵ�,������\n");
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
            printf("����������ѯ\n");//����
            gets(E);//��������

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
                    printf("û�ҵ�,������\n");
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
            printf("����ƽ���ֲ�ѯ\n");//����
            gets(E);//��������
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
                    printf("û�ҵ�,������\n");
                    break;
                }
                if (students[(num1 + num2) / 2].average > k)
                    num2 =-1+(num1 + num2) / 2;
                if (students[(num1 + num2) / 2].average < k)
                    num1 = 1+(num1 + num2) / 2;
            }
        }
        else
            printf("�����������\n");

    }
    return 0;

}