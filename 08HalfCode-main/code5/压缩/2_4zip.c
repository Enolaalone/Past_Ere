#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct zip{
    char ch[5];
    char code[30];
}Zip;


//\n100111011
void consent(Zip zips[]){
    char words[50];
    int n=0;
    FILE *fp= fopen("./code.txt","r");
    strcpy(zips[n].ch,"\n\t");
    strcpy(zips[n].code,"100111011");// 100111011
    n++;
    while(fgets(words,50,fp)!=NULL){
        sscanf(words,"%s %s",zips[n].ch,zips[n].code);
//        printf("%s\t%s\n", zips[n].ch,zips[n].code);
        n++;
    }

}

void BinString(char codes[],FILE*p,char *letter,int *bitCount){//按位录入
    char code[25];
    strcpy(code,codes);
    for (int j = 0; code[j] !='\0'; ++j) {
        *letter<<=1;//向左一位
        if(code[j]=='1') (*letter)|=1;//最低位为一
        (*bitCount)++;

        if(*bitCount==8){//满足八位一字节录入，计数，字节初始化
            fwrite(letter,1,1,p);
            *bitCount=0;
            *letter=0;
        }
    }
}
void clear(char words[],int l){
    for (int i = 0; i < l; ++i) {
        words[i]='\0';
    }
}

void shift_words(char ch2[],char ch3[]){//5 3
    for (int i = 0; i < 2; ++i) {
        ch3[i]=ch2[i];
    }
    ch3[2]='\0';
    for (int i = 0; i <2; ++i) {
        ch2[i]=ch2[2+i];
    }
    ch2[2]='\0';
}

void shift_n(FILE*fp,FILE*pf,char words[],Zip zips[],char*letter,int*bitCount){
    char word_n[3]="\n",word_0[3]="  ";
    if(strcmp(word_n,words)==0){
//        BinString(zips[0].code,pf,letter,bitCount);
//        fgets(words,3,fp);
        words[1]='\t';
        words[2]='\0';
    }
    else if(strcmp(word_0,words)==0) fgets(words,3,fp);
}
void CreateFile(char names[],Zip zips[]){
    char words[3]="\0",words_s[5]="\0",word[3]="\0";
    char letter=0;
    int bitCount=0;
    bool find=false;
    FILE *fp= fopen(names,"r");
    FILE *pf= fopen("sg压3.txt","wb");

    for (int i = 0; i < 2; ++i) {
        fgets(words,3,fp);
        strcat(words_s,words);
    }

    while(fgets(words,3,fp)!=NULL){
        shift_n(fp,pf,words,zips,&letter,&bitCount);
        for (int i = 3998; i < 37345; ++i) {
//            printf("%s\t%s\n",zips[i].ch,words_s);
            if(strcmp(zips[i].ch,words_s)==0){//找到字符
//                printf("%s\t%s\n",zips[i].ch,words_s);
//                printf("%s",words_s);
                BinString(zips[i].code,pf,&letter,&bitCount);
                find=true;
                break;
            }
        }

        if(find){
            find=false;
            clear(words_s,5);

            strcat(words_s,words);
            fgets(words,3,fp);
            shift_n(fp,pf,words,zips,&letter,&bitCount);
            strcat(words_s,words);
            continue;
        }
        shift_words(words_s,word);
        for (int i = 0; i < 3998; ++i) {
//            printf("%s\t%s\n",zips[i].ch,word);
            if(strcmp(zips[i].ch,word)==0){//找到字符
//                printf("%s",word);
//                printf("%s\t%s\n",zips[i].ch,word);
                BinString(zips[i].code,pf,&letter,&bitCount);
                find=true;
                break;
            }
        }

        if(find){
            find=false;
            clear(word,3);
            strcat(words_s,words);
            continue;
        }

    }
    fclose(pf);
    fclose(fp);
}

int main() {
    int n=37345;
    Zip* zips=(Zip*) malloc(n* sizeof(Zip));
    for (int i = 0; i < n; ++i) {
        clear(zips[i].code,30);
        clear(zips[i].ch,5);
    }
    consent(zips);
    CreateFile("./sg改.txt", zips);

    free(zips);
    return 0;
}
