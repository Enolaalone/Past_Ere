#include <stdio.h>
#include <malloc.h>//����malloc()������
#define LEN sizeof(struct Student) //ȷ��Student �ṹ�峤��

struct Student//�ṹ��
{
    int num;//���
    unsigned int student_num;//ѧ��
    char name[5];//����
    int grade;//�ɼ�
    struct Student *next;//�ṹ��ָ��
};

int n;
int grades[162]={0};

struct Student* create(){
    FILE *fp;
    char words[35];//35���ȵĵ�Ԫ��װһ�е�����
    struct Student *head,*p1,*p2;// struct Student��ָ��
    n=0;
    fp= fopen("D:\\C�ļ�\\CBasic2\\grade.txt","r");//���ļ�
    fgets(words,35,fp);
    p1=p2=(struct Student*)malloc(LEN);//��̬��������ַ
    head=NULL;
    if( sscanf(words, "%d\t%u\t%7s\t%d", &p1->num, &p1->student_num, p1->name, &p1->grade)==4)
    {
//        sscanf(words, "%d\t%u\t%7s\t%d", &p1->num, &p1->student_num, p1->name, &p1->grade);//name�ַ����鱾����ǵ�ַ����&
        printf("%d\t%u\t%s\t%d\n", p1->num, p1->student_num, p1->name, p1->grade);
        grades[n]=p1->grade;
    }
    do{
        n++;
        if(n==1)head=p1;
        else p2->next=p1;
        p2=p1;
        p1=(struct Student*)malloc(LEN);//�����µĴ�����
        fgets(words,30,fp);
        if( sscanf(words, "%d\t%u\t%7s\t%d", &p1->num, &p1->student_num, p1->name, &p1->grade)==4)
        {
            printf("%d\t%u\t%s\t%d\n", p1->num, p1->student_num, p1->name, p1->grade);
            grades[n]=p1->grade;
        }
    }while(p2->num!=162);
    p2->next=NULL;
    fclose(fp);//�ر��ļ�
    return (head);

};
void print2(struct Student *head)
{
    struct Student *p1;
    unsigned int sum=0;
    p1=head;
    if (p1!=NULL)
    {
        do{
            sum+=p1->grade;
            if(p1->grade==grades[0])
            {
                printf("��߷֣�ѧ�ţ�%u\n\t������%s\n\t�ɼ���%d", p1->student_num, p1->name, p1->grade);
                printf("\n");
            }
            if(p1->grade==grades[161])
            {
                printf("��ͷ֣�ѧ�ţ�%u\n\t������%s\n\t�ɼ���%d", p1->student_num, p1->name, p1->grade);
                printf("\n");
            }
            p1=p1->next;
        }while(p1!=NULL);
        printf("ƽ���֣�%.2f",(float)sum/162);
        printf("\n");
    }
};

int compare(int ls[])
{
    int length = 0;
    int i,j,x1,x2,s=0;
    length = 162;
    for(i=0;i<length-1;i++)//7��
    {
        for(j=0;j<length-1-i;j++)//ÿ�δӵ�һ�ʼ
        {
            if(ls[j]<ls[j+1])//���ǰһ��Ⱥ�һ��С
            {
                x2=x2+1;
                x1=ls[j];
                ls[j]=ls[j+1];
                ls[j+1]=x1;
            }
        }

    }
//    for(s=0;s<length;s++)//��ӡ����
//    {
//        printf("%d,",ls[s]);
//    }
    return 0;
};
int main() {
    struct Student *pt;
    pt=create();//��һ����ĵ�ַ
    compare(grades);
    print2(pt);
}