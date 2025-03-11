#include <stdio.h>
#include <string.h>

typedef struct zip{
    char ch[3];//字符
    char code[25];//编码
}Zip;


//\n111010111
void consent(Zip zips[]){
    char words[50];
    int n=0;
    FILE *fp= fopen("./code.txt","r");//编码文件
    while(fgets(words,50,fp)!=NULL){
        sscanf(words,"%s\t%s",zips[n].ch,zips[n].code);
//        printf("%d%s\n",zips[n].code,zips[n].ch);
        n++;
    }
    strcpy(zips[n].ch,"\n");
    strcpy(zips[n].code,"111001110");
}

void BinString(char codes[],FILE*p,char *letter,int *bitCount){//按位录入
    char code[25];
    strcpy(code,codes);
    for (int j = 0; code[j] !='\0'; ++j) {
        *letter<<=1;//向左一位
        if(code[j]=='1') *letter|=1;//最低位为一
        (*bitCount)++;

        if(*bitCount==8){//满足八位一字节录入，计数，字节初始化
            fwrite(letter,1,1,p);
            *bitCount=0;
            *letter=0;
        }
    }
}

void CreateFile(char names[],Zip zips[]){
    int bitCount=0;//字节计数
    char words[3];//读取单个字
    char letter=0;//字节
    FILE *fp= fopen(names,"r");
    FILE *pf= fopen("sg压2.txt","wb");
    while(fgets(words,3,fp)!=NULL){
        for (int i = 0; i < 4003; ++i) {
            if(strcmp(zips[i].ch,words)==0){//找到字符
                BinString(zips[i].code,pf,&letter,&bitCount);
                break;
            }
        }
    }
    if (bitCount > 0) {//剩下不足八位添零补位
        letter <<= (8 - bitCount); // 将剩余的位左移
        fwrite(&letter, 1, 1, pf);
    }
    fclose(pf);
    fclose(fp);
}

int main() {
    Zip zips[4003];
    consent(zips);
    CreateFile("./sg改.txt",zips);
    return 0;
}