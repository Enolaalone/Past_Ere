#include <stdio.h>
#include <string.h>

typedef struct zip{
    char ch[3];//�ַ�
    char code[25];//����
}Zip;


//\n111010111
void consent(Zip zips[]){
    char words[50];
    int n=0;
    FILE *fp= fopen("./code.txt","r");//�����ļ�
    while(fgets(words,50,fp)!=NULL){
        sscanf(words,"%s\t%s",zips[n].ch,zips[n].code);
//        printf("%d%s\n",zips[n].code,zips[n].ch);
        n++;
    }
    strcpy(zips[n].ch,"\n");
    strcpy(zips[n].code,"111001110");
}

void BinString(char codes[],FILE*p,char *letter,int *bitCount){//��λ¼��
    char code[25];
    strcpy(code,codes);
    for (int j = 0; code[j] !='\0'; ++j) {
        *letter<<=1;//����һλ
        if(code[j]=='1') *letter|=1;//���λΪһ
        (*bitCount)++;

        if(*bitCount==8){//�����λһ�ֽ�¼�룬�������ֽڳ�ʼ��
            fwrite(letter,1,1,p);
            *bitCount=0;
            *letter=0;
        }
    }
}

void CreateFile(char names[],Zip zips[]){
    int bitCount=0;//�ֽڼ���
    char words[3];//��ȡ������
    char letter=0;//�ֽ�
    FILE *fp= fopen(names,"r");
    FILE *pf= fopen("sgѹ2.txt","wb");
    while(fgets(words,3,fp)!=NULL){
        for (int i = 0; i < 4003; ++i) {
            if(strcmp(zips[i].ch,words)==0){//�ҵ��ַ�
                BinString(zips[i].code,pf,&letter,&bitCount);
                break;
            }
        }
    }
    if (bitCount > 0) {//ʣ�²����λ���㲹λ
        letter <<= (8 - bitCount); // ��ʣ���λ����
        fwrite(&letter, 1, 1, pf);
    }
    fclose(pf);
    fclose(fp);
}

int main() {
    Zip zips[4003];
    consent(zips);
    CreateFile("./sg��.txt",zips);
    return 0;
}