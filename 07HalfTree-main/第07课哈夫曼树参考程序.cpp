//����1�������⡰�������塱�ĵ���Ȩ���ļ��Ĺ��������� 
//˼·�� ��ȡȨ���ļ�������֣��浽�������棨�൱�ڴ���Ȩ�����飩
//�����ṹ������ΪȨ�ء�����㡢���ӡ��Һ��� 
//�Թ���������ʼ��������2*n-1���ṹ�壬��ַ��ps���ٸ������������ʼ��
//Ȼ���ȡ���ֵ��Сֵ���±꣬�����������Ĺ������� 
//���ݹ��������������� 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>//�������isdigit���� 

//�����ṹ�� 
typedef struct Node
{
	char name[3];
	int weight;//���Ȩ�� 
	int parent;//������ 
	int lchild;//���Ӻ� 
	int rchild;//�Һ��Ӻ� 
}*stack;//ͬʱ������һ���ṹ�����͵�ָ�� 


//
int open(int leaf_weight[],FILE *fp1,FILE*fp2,char hanzi[][3])
{
	char ch; 
	int number=0,i=0;
	if (NULL==fp1) //�Է���ֵfp1�ж��Ƿ�򿪳ɹ������ΪNULL��ʾʧ��
	{
	    printf ("Failed to open the file1 !\n");
	    exit (0) ; //��ֹ����stdlib .hͷ�ļ���
	}
	if(NULL==fp2)
	{
	    printf ("Failed to open the file2 !\n");
	    exit (0);//��ֹ����stdlib .hͷ�ļ���
	}
	while(!feof(fp1))//�ļ����������ط�0ֵ���ļ�δ����������0ֵ
	{
		ch=fgetc(fp1);//��ȡһ���ַ�
		if(ch<0 || ch==92 || ch==39)//�������ֺͻ��кͿո� 
		{
			hanzi[i][0]=ch; 
			hanzi[i][1]=fgetc(fp1);
			hanzi[i][2]='\0';
//			printf("%s\n",hanzi[i]);
//			ch=fgetc(fp1);//��ȡһ���ַ�
		}
		else if(ch==34 || ch==45)//�����Ӣ�ĵĵ����Ż����Ƕ̺�
		{
			hanzi[i][0]=ch; 
			hanzi[i][1]='\0';
		} 
		else 
		{
			if(isdigit(ch))
			{
				while(isdigit(ch))
				{
					number=number*10+ch-'0';//�õ�һ���ַ���Ȩ�� 
					ch=fgetc(fp1);
				}
			}
		}
		if(number!=0)
		{
			leaf_weight[i]=number;
			i++;
			number=0;//���ζ�ȡ��Ϻ��0 
		}
	}
	return i;//�õ�Ȩ�����������Ԫ�ظ��� 
}






//Ѱ����Сֵ�ʹ�Сֵ���±꺯�� 
void compare(int *s1,int *s2,stack ps,int n)
{
	int min1=9999999,min2=9999999,i;//���Ȱ���������ֵһ���Ƚϴ����ֵ����������ıȽ�,����һ��Ҫ������Ϊ��Ļ�����ô�� 
	
	//��ȡ��Сֵ���±� 
	for(i=0;i<2*n-1;i++)
	{
		if((ps+i)->weight!=0 && (ps+i)->parent==-1)//�����ǰȨ�ز�ΪNULL�����Ҹ����ΪNULL�����ǹ½��
		{
		 	if(min1>(ps+i)->weight)
		 	{
		 		*s1=i;//��ȡ�±� 
		 		min1=(ps+i)->weight;//ÿ�αȽϺ��ȡ��Сֵ��������һ�αȽ�  
			}
		} 
	}
	//��ȡ��Сֵ���±� 
	for(i=0;i<2*n-1;i++)
	{
		if((ps+i)->weight!=0 && (ps+i)->parent==-1)//�����ǰȨ�ز�ΪNULL�����Ҹ����ΪNULL�����ǹ½��
		{
		 	if(min2>(ps+i)->weight && i!=*s1)
		 	{
		 		*s2=i;//��ȡ�±� 
		 		min2=(ps+i)->weight;//ÿ�αȽϺ��ȡ��Сֵ��������һ�αȽ�  
			}
		} 
	}
//	printf("�˴���С���������±�Ϊ��%d,%d\n", *s1,*s2);
}




//��������������ʼ������� 
stack create(int leaf_weight[],char hanzi[][3],int n,stack ps,int *s1,int *s2)
{
	int i;
	ps = (stack)malloc((2*n-1) * sizeof(struct Node));//����2*n-1����� 
	//�Թ����������г�ʼ�� 
	for(i=0;i<2*n-1;i++)
	{
		ps[i].parent=ps[i].lchild=ps[i].rchild=-1;//��ʼ��Ϊ-1 
		if(i<n)//С��nʱ�͸�ֵ���Ȩ�� 
		{
			ps[i].weight=leaf_weight[i];//�ѽ��Ȩ�ض��浽������
			ps[i].zifu[0]=hanzi[i][0]; 
			ps[i].zifu[1]=hanzi[i][1];
			ps[i].zifu[2]=hanzi[i][2];
//			printf("ps[i].zifu:%s\n",ps[i].zifu);
		}
		else//����0�Ķ���ʼ��Ϊ0 
		{
			ps[i].weight=0;
		}		
	}
	for(i=n;i<2*n-1;i++)
	{
		compare(s1,s2,ps,n);
		(ps+i)->weight=(ps+*s1)->weight+(ps+*s2)->weight;//�ýڵ��Ȩ��=�������ӵ�Ȩ��֮�� 
		ps[*s2].parent=ps[*s1].parent=i;//���ӵĸ�����Ǹýڵ� 
		ps[i].lchild=*s1;//�����*s1 
		ps[i].rchild=*s2;//�Ҷ���*s2 
	}
//	for(i=0;i<2*n-1;i++)
//	{
//		printf("��%d�����Ȩ�ء������š����Ӻš��Һ��Ӻ�:\t%d\t%d\t%d\t%d\n",i,ps[i].weight,ps[i].parent,ps[i].lchild,ps[i].rchild);
//	}
	return ps;
}


//��������������
char ** coding(char **HufCode,int n,stack ps)
{
	int i,flag,c,pp;
	char *tmp = (char *)malloc(n * sizeof(char));	//������ǰ����Ĺ����ռ�,�ڵ�ı��������ᳬ��������� 
	HufCode=(char **)malloc( n * sizeof(char *));
	tmp[n-1] = '\0';//����������λ��ű��룬���ȴ�ű��������
	for(i = 0; i < n; i++)		//��n��Ҷ�ӽ���Ӧ�Ĺ���������
    {
        flag =  n - 1;		//��ʼ������λָ�롣ÿ���һ������λ���������tmp[flag]��
        //��Ҷ�ӵ�����������
		for(c = i, pp = ps[i].parent; pp != -1; c =pp, pp= ps[pp].parent)
        {
            if( ps[pp].lchild == c)
				tmp[--flag] = '0';  //���֧��0 ,���ҵ����˳�������������
            else
                tmp[--flag] = '1';  //�ҷ�֧��1
        }
        
        HufCode[i] = (char *)malloc((n - flag) * sizeof(char));//Ϊ��i�����봴���ռ�
        strcpy(HufCode[i], &tmp[flag]);//������ôʹ�õĲ�̫���� 
//        printf("��ǰȨ��Ϊ��%s,����ı���Ϊ��%s\n",ps[i].zifu,HufCode[i]);
    }
	free(tmp);
	return HufCode;		//�ͷ���ʱ�ռ�
}	

void display(char **HufCode,stack ps,FILE *fp2,int n)  //�������ļ�д��ȥ 
{ 
	int i;
	for(i=0;i<n;i++)
	{ 
		fprintf(fp2,"%s\t%s\n",(ps+i)->zifu,HufCode[i]);//д������
	} 
} 
 
int main()
{
	int n,i,s1,s2;
	stack ps;
	char **HufCode;		//���ָ��ָ��һ��ָ�����飨Ԫ�ظ���=Ҷ�Ӹ�������
	//�����е�ÿ��Ԫ��ָ��һ����̬�ַ����ռ䣨װ�����Ĺ��������룩
	int leaf_weight[4008];//Ҷ�ӽ��Ȩ������,һ��ʼ�������С������һ��ʱ��ͱ�����
	char hanzi[4008][3]; 
	FILE *fp1,*fp2;//���������ļ�ָ�����fp1��fp2
	fp1=fopen("Ȩ��.txt","r"); //��ֻ��ģʽ���ļ�
	fp2=fopen ("�����������������.txt","w"); //��д���ģʽ���ļ�f2 .txt
	n=open(leaf_weight,fp1,fp2,hanzi);//��ȡ��������������鱾����ǵ�ַ�����÷���
	ps=create(leaf_weight,hanzi,n,ps,&s1,&s2);
	HufCode=coding(HufCode,n,ps);
	display(HufCode,ps,fp2,n);  //�������ļ�д��ȥ
	
//	printf("n:%d\n",n);
//	n=sizeof(leaf_weight)/sizeof(leaf_weight[0]);//�������Ԫ�ظ���
//	ps=operate(n,ps,&s1,&s2,leaf_weight);
//	coding(HufCode,n,ps);//��������������ĺ���
	free(ps);//�ͷſռ� 
	return 0;
}

