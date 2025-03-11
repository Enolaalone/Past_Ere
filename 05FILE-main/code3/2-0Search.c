#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Student *list;
struct Student{
    int num;//���
    int st_num;//ѧ��
    char name[20];//����
    char sex[20];//�Ա�
    char class[20];//������
    int grade1;//
    int grade2;//
    int grade3;//
    int average;//ƽ��
};

struct Student *students[500];//�ṹ������
int n=0;

void StructLSCreate(char *str) {
    char words[100];//�������ݴ��
    FILE *fp = fopen(str, "r");//���ļ�
    while (fgets(words, 100, fp) != NULL) {//���ж�ȡ
        students[n] = (struct Student *) malloc(sizeof(struct Student));//�����ڴ��ַ
        if (sscanf(words, "%d��%d��%[^��]��%[^��]��%[^��]��%d��%d��%d��%d\n", &students[n]->num, &students[n]->st_num,//��ȡ��ʽ������
                   students[n]->name, students[n]->sex, students[n]->class, &students[n]->grade1, &students[n]->grade2,
                   &students[n]->grade3, &students[n]->average) == 9) {
//            printf("%d��%d��%s��%s��%s��%d��%d��%d��%d\n",students[n]->num,students[n]->st_num,students[n]->name,students[n]->sex,students[n]->class,students[n]->grade1,students[n]->grade2,students[n]->grade3,students[n]->average);
            n++;
        }
    }
    fclose(fp);
}
int main() {
    bool finding=false;//ȷ���Ƿ��ҵ�
    char E[25];//���̻�ȡ����
    char word_0[9][25]={{"���"},{"ѧ��"},{"����"},{"�Ա�"},{"������"},{"����ת��"},{"�����ת��"},{"��ֵ����߼�����"},{"ƽ����"}};//��ͷ
    int num_try=0;//ȷ���Ƿ�Ϊѧ��
    StructLSCreate("./new598854�γ�.txt");
    StructLSCreate("./new598856�γ�.txt");
    StructLSCreate("./new598858�γ�.txt");
    while(1){
        finding=false;//��ʼ������
        printf("����������ѧ�Ų�ѯor��e�˳�\n");//����
        gets(E);//��������
        if(E[0]=='e')
            break;//�˳�
        else{
            for(int i=0;i<n;i++){
                num_try=atoi(E);//�ַ���ת����
                if(num_try!=0){//ȷ����������ַ���
                    if(num_try==students[i]->st_num){//�����ѧ�������
                        finding=true;//����ҵ�
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
            if(!finding)//����û�ҵ�
                printf("û�ҵ�,������\n");
        }

    }
    return 0;
}