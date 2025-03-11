#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student{
    int num;//???
    int st_num;//???
    char name[20];//????
    char sex[20];//???
    char class[20];//??????
    int grade1;//
    int grade2;//
    int grade3;//
    int average;//???
};

char* exchange(char* buf)
{
    char *ret = strstr(buf, "\t");//??????\t"????
    while (ret != NULL)
    {
        memset(ret, '0', strlen("\t")); // ?I
        ret = strstr(buf, "\t");//????????
    }
//    printf("%s\n", buf);
    return buf;
}
void FileCreate(char *str,char *new_name){
    char word_0[200]="??????????????????????????????????????????????????????????????\n";
    char words[100];
    char* word;
    int n=0;
    struct Student *students[150];//???????????

    FILE *fp=fopen(str,"r");//???????
    while(fgets(words,100,fp)!=NULL){//???????
        students[n] = (struct Student *)malloc(sizeof(struct Student));//??????????????
        word= exchange(words);//???\t????0
        if(sscanf(word,"%d??%d??%[^??]??%[^??]??%[^??]??%d??%d??%d\n",&students[n]->num,&students[n]->st_num,
        students[n]->name,students[n]->sex,students[n]->class,&students[n]->grade1,&students[n]->grade2,&students[n]->grade3)==8){
            students[n]->average=(int)((students[n]->grade1)+(students[n]->grade2)+(students[n]->grade3))/3;//??????
//          printf("%d??%d??%s??%s??%s??%d??%d??%d??%d\n",p->num,p->st_num,p->name,p->sex,p->class,p->grade1,p->grade2,p->grade3,p->average);
            n++;//????1
        }
    }
    fclose(fp);

    //§Õ?????
    FILE *pf=fopen(new_name,"w");
//    printf("%s",word_0);
    fprintf(pf,"%s",word_0);
    for(int i=0;i<n;i++){
//        printf("%d??%d??%s??%s??%s??%d??%d??%d??%d\n",students[i]->num,students[i]->st_num,students[i]->name,students[i]->sex,students[i]->class,students[i]->grade1,students[i]->grade2,students[i]->grade3,students[i]->average);
        fprintf(pf,"%d??%d??%s??%s??%s??%d??%d??%d??%d\n",students[i]->num,students[i]->st_num,students[i]->name,students[i]->sex,students[i]->class,students[i]->grade1,students[i]->grade2,students[i]->grade3,students[i]->average);
    }
    fclose(pf);
}
int main() {
    char filename_1[]="./598854?¦Ã?.txt";//???????????¦Ë???//debug//exe
    char file_new_name_1[]="new598854?¦Ã?.txt";
    char filename_2[]="./598856?¦Ã?.txt";
    char file_new_name_2[]="new598856?¦Ã?.txt";
    char filename_3[]="./598858?¦Ã?.txt";
    char file_new_name_3[]="new598858?¦Ã?.txt";
    FileCreate(filename_1,file_new_name_1);
    FileCreate(filename_2,file_new_name_2);
    FileCreate(filename_3,file_new_name_3);
    return 0;
}