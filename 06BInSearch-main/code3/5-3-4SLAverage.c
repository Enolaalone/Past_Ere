#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
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
    int leval;//�����ȼ�

};
struct Sp_student{//��
    struct Student st;
    struct Sp_student* p[];
};


bool SL[373];//�Ƿ�����ڴ�
bool print=false;//��ͷ��ӡ
struct Student students[373];//����������
struct Student x;
struct Sp_student *sp_students[373];//ָ�����鹹��������
int n=0;

char word_0[9][25]={{"���"},{"ѧ��"},{"����"},{"�Ա�"},{"������"},{"����ת��"},{"�����ת��"},{"��ֵ����߼�����"},{"ƽ����"}};//��ͷ
char E[100];//���̻�ȡ����
int k;//ѧ��

int sl[6]={1,5,10,20,40,80};//����ּ�
void SL_0(int s){//��ʼ��
    for(int i=0;i<s;i++){
        SL[i]=false;
    }
}
void SL_Leval(int s){//ȷ��ÿ�ű�������㼶
    for(int i=0;i<s;i++){
        students[i].leval=0;
        for(int y=0;y<6;y++) {
            if (i % sl[y] == 0) {
                students[i].leval += 1;
            }
        }
    }
}

void Malloc(int j){//�����ڴ����
    if(!SL[j]){
        sp_students[j]= (struct Sp_student*)malloc(sizeof (struct Sp_student)+students[j].leval*sizeof (struct Student*));
        sp_students[j]->st=students[j];
        SL[j]=true;//�Ѿ������ڴ�
    }
    else{
        return;
    }
}

void Print(struct Sp_student*p) {//��ӡ���
    if(!print){//��ͷֻ��ӡһ��
        printf("%-8s%-15s%-11s%-11s%-13s%-13s%-18s%-20s%-12s\n", word_0[0], word_0[1], word_0[2], word_0[3],
               word_0[4], word_0[5], word_0[6], word_0[7], word_0[8]);
        print=true;
    }
    printf("%-8d%-15d%-11s%-11s%-13s%-13d%-18d%-20d%-12d\n", p->st.num,
           p->st.st_num, p->st.name, p->st.sex, p->st.class,
           p->st.grade1, p->st.grade2, p->st.grade3,
           p->st.average);
}
void StructLSCreate(char *str) {//��ȡ�ı���������
    char words[200];//�������ݴ��
    FILE *fp = fopen(str, "r");//���ļ�
    while (fgets(words, 200, fp) != NULL) {//���ж�ȡ
//        printf("%s",words);
        if (sscanf(words, "%d %d %s %s %s %d %d %d %d", &students[n].num, &students[n].st_num,//��ȡ��ʽ������
                   students[n].name, students[n].sex, students[n].class, &students[n].grade1, &students[n].grade2,
                   &students[n].grade3, &students[n].average) == 9) {
            students[n].leval=0;
//            printf("%d��%d��%s��%s��%s��%d��%d��%d��%d\n",students[n].num,students[n].st_num,students[n].name,students[n].sex,students[n].class,students[n].grade1,students[n].grade2,students[n].grade3,students[n].average);
            n++;
        }
//        else{
//            printf("%s",words);
//        }
    }
//    printf("\n%d\n",n);
    fclose(fp);
}
void Compare1(int l) {//���鰴ѧ������
    int f;
    for (int i = 0; i < l; i++) {//l=372
        f = i;
        for (int j = i + 1; j < l+1; j++) {//l+1=373
            if (students[f].st_num > students[j].st_num)
                f = j;
        }
        x = students[i];
        students[i] = students[f];
        students[f] = x;
    }
    SL_Leval(l);
//    for(int i=0;i<373;i++){
//        printf("%d��%d��%s��%s��%s��%d��%d��%d��%d��%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average,students[i].leval);
//    }
}

void Compare2(int l){//��������
    int f;
    int result;
    setlocale(LC_COLLATE,"zh_CN.GBK");//���ػ��ַ�������
    for(int i=0;i<l;i++){
        f=i;
        for(int j=i+1;j<l+1;j++){
            result= strcoll(students[f].name,students[j].name);
            if(result>0)//students[f].name>students[j].name
                f=j;
        }
        x=students[i];
        students[i]=students[f];
        students[f]=x;
    }
    SL_Leval(l);
//    for(int i=0;i<373;i++){
//        printf("%d��%d��%s��%s��%s��%d��%d��%d��%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average);
//    }
}

void Compare3(int l){//ƽ��������
    int f;
    for(int i=0;i<l;i++){
        f=i;
        for(int j=i+1;j<l+1;j++){
            if(students[f].average>students[j].average)
                f=j;
        }
        x=students[i];
        students[i]=students[f];
        students[f]=x;
        students[i].num=i;
    }
    students[l].num=l;
    SL_Leval(l);
//    for(int i=0;i<373;i++){
//        printf("%d��%d��%s��%s��%s��%d��%d��%d��%d\n",students[i].num,students[i].st_num,students[i].name,students[i].sex,students[i].class,students[i].grade1,students[i].grade2,students[i].grade3,students[i].average);
//    }
}

struct Sp_student* CreateList(int l){//����������������
    for(int i=0;i<6;i++){
        for(int j=0;j<l;j++){//l=372
            if(j%sl[i]==0){
                if(j+sl[i]>l){
                    Malloc(j);//�������㼶�����ڴ�
                    Malloc(l);
                    sp_students[j]->p[i]=sp_students[l];//�������ֽӵ����һ�ű�

                }
                else{
                    Malloc(j);
                    Malloc(j+sl[i]);
                    sp_students[j]->p[i]=sp_students[j+sl[i]];
                }
            }
        }
    }
//    for(int i=0;i<6;i++){
//        printf("%s\n",sp_students[0]->p[i]->st.name);
//    }
    return sp_students[0];
}

void FindXue(struct Sp_student*head,struct Sp_student*tail){//����ѧ������
    struct Sp_student*p=head;
    if(k<head->st.st_num || k>tail->st.st_num){//��������ͷβ��Χ
        printf("û�ҵ�\n");
        return;
    }
    else{
        for(int i=0;i<6;i++){//��������
            while (1){
                if(p->st.st_num==k){//�ҵ�
                    print=false;
                    Print(p);
                    return;
                }
                if(p->p[5-i]->st.st_num>k){//��һλ���ڣ���������
                    break;
                }
                if(p->p[5-i]->st.st_num<=k){//С�ڵ����е���һλ
                    p=p->p[5-i];
                }
            }
        }
        printf("û�ҵ�\n");
        return;
    }
}

void FindName(struct Sp_student*head,struct Sp_student*tail){//����
    struct Sp_student*p=head;
    if(strcoll(E,head->st.name)<0|| strcoll(E,tail->st.name)>0){
        printf("û�ҵ�~~~\n");
        return;
    }
    else{
        for(int i=0;i<6;i++){
            while (1){
                if(strcoll(p->st.name,E)==0){
                    print=false;
                    Print(p);
                    return;
                }
                if(strcoll((p->p[5-i])->st.name,E)>0){
                    break;
                }

                if(strcoll((p->p[5-i])->st.name,E)<=0){
                    p=p->p[5-i];
                }

            }
        }
        printf("��û�ҵ�\n");
        return;
    }

}

void AveForward(int l){//�����ҵ���һ��ƽ���֣��ݹ��ѯƽ������ͬ��
    if(students[l-1].average!=students[l].average || l-1<=0){
        return;
    }
    Print(sp_students[l-2]->p[0]);
    AveForward(l-1);
}

void AveBack(int l) {//�ݹ��ѯƽ������ͬ��
    if (students[l + 1].average != students[l].average || l >= 372) {
        return;
    }
    Print(sp_students[l]->p[0]);
    AveBack(l + 1);
}

void FindAverage(struct Sp_student*head,struct Sp_student*tail){//�����ѯƽ����
    struct Sp_student*p=head;
    if(k<head->st.average || k>tail->st.average){
        printf("û�ҵ�\n");
        return;
    }
    else{
        for(int i=0;i<6;i++){
            while (1){
                if(p->st.average==k){
                    print=false;
                    Print(p);
                    AveForward(p->st.num);
                    AveBack(p->st.num);
                    return;
                }
                if(p->p[5-i]->st.average>k){
                    break;
                }

                if(p->p[5-i]->st.average<=k){
                    p=p->p[5-i];
                }

            }
        }
        printf("û�ҵ�\n");
        return;
    }

}


int main() {
    int r=372;
    struct Sp_student*k1,*k2,*k3,*k4,*k5,*k6;
    StructLSCreate("./Grade.txt");//�ṹ������
    //-----------------ѧ�Ų��ҳ�ʼ��
    Compare1(r);
    SL_0(r+1);
    k1=CreateList(r);
    k4=sp_students[r];
    //----------------�������ҳ�ʼ��
    Compare2(r);
    SL_0(r+1);
    k2= CreateList(r);
    k5=sp_students[r];
    //---------------ƽ���ֲ��ҳ�ʼ��
    Compare3(r);
    SL_0(r+1);
    k3= CreateList(r);
    k6=sp_students[r];

    while(1){
        printf("1.ѧ�Ų�ѯ 2.������ѯ 3.ƽ���ֲ�ѯor��e�˳�\n");//����
        gets(E);//��������
        if(E[0]=='e')
            break;//�˳�
        else if(E[0]=='1') {
            printf("����ѧ�Ų�ѯ\n");//����
            gets(E);//��������
            k = atoi(E);
            FindXue(k1,k4);
        }
        else if(E[0]=='2'){
            printf("����������ѯ\n");
            gets(E);
            FindName(k2,k5);
        }
        else if(E[0]=='3'){
            printf("����ƽ���ֲ�ѯ\n");
            gets(E);
            k= atoi(E);
            FindAverage(k3,k6);
        }

        else
            printf("�����������\n");
    }

    return 0;
}