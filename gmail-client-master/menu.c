#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

int main(){
        char inputOpt[3] = "0\n";
        char UID[1024] = {0};
        char PWD[1024] = {0};
        char FROM[1024] = {0};
        char TO[1024] = {0};
        char MAIL_HEADER_FROM[1024] = {0};
        char MAIL_HEADER_TO[1024] = {0};
        char name[1024] ={0};
        char *mailMess = (char*)calloc(1024,sizeof(char));
  do{
    if(!strcmp(inputOpt,"0\n")){
        printf("\n==========================\n");
        printf("Login\n");
        printf("==========================\n");
        printf("Your name : \n");
        fgets(name,1000,stdin);
        name[strlen(name)-1] = 0;
        printf("Gmail : \n");
        //Set UID
        fgets(UID,1000,stdin);
        UID[strlen(UID)-1] = 0;
        printf("Password : \n");
        //Set PWD
        fgets(PWD,1000,stdin);
        PWD[strlen(PWD)-1] = 0;
        printf("%s#%s#\n",UID,PWD);
        //Set FROM
        sprintf(FROM,"<%s>",UID);
        //Set MAIL_HEADER_FROM
        sprintf(MAIL_HEADER_FROM,"%s<%s>",name,UID);
        inputOpt[0] = '1';
        // printf("%d",!strcmp(inputOpt,"0\n"));
        continue;
    }else{
        printf("==========================\n");
        printf("1. Write mail's message.\n");
        printf("2. Attach file.\n");
        printf("3. Send and exit\n");
        printf("==========================\n");
        fgets(inputOpt,100,stdin);
        // printf("%s#",inputOpt);
        char option = inputOpt[0];
        switch (option)
        {
        case '1' :{
            printf("Enter receiver's name :\n>");
            fgets(name,1000,stdin);
            name[strlen(name)-1]=0;
            char input[500] = {0};
            printf("Enter receiver's email address:\n>");
            fgets(input,1000,stdin);
            input[strlen(input)-1] = 0;
            sprintf(TO,"<%s>",input);
            sprintf(MAIL_HEADER_TO,"%s<%s>",name,TO);
            printf("Enter message (Type \"\\n::q\" to exit): \n>");
            char line[1024] = {0};
            do{
                fgets(line,1024,stdin);
                if(!strcmp(line,"::q\n"))
                {
                  break;
                }else{
                  strcpy(line+strlen(line)-1,"\r\n");
                  sprintf(mailMess+strlen(mailMess),"%s",line);
                }
                // mailMess = (char*)realloc(mailMess,sizeof(line)*2);
            }while(0 == 0);;
            // strcpy(mailMess+strlen(mailMess)-4,"\r\n");
            printf("Message :\n%s#####\n",mailMess);
            printf("FROM : %s##\n",FROM);
            printf("TO : %s##\n",TO);
            printf("MAIL_HEADER_FROM : %s##\n",MAIL_HEADER_FROM);
            printf("MAIL_HEADER_TO : %s##\n",MAIL_HEADER_TO);
            printf("UID : %s##\n",UID);
            printf("PWD : %s##\n",PWD);
            break;
        }
        case '2' :{
            printf("Choose type of attachment.\n");
            printf("1. Image");
            printf("2. Audio");
            printf("3. Video");
            break;
        }
        default:
            sprintf(inputOpt,"0\n");
        }
    }
  }while(strcmp(inputOpt,"0\n"));
    return 0;
}