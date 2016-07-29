#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void compiler();
FILE *archivo;
char comando[200];
int main()
{
compiler();
return 0;
}

void compiler(){
int a=0;

bool mkdisk=false;
char auxnombre[25]="";
int tamanio=-1;
char auxpath[100]="";
bool size=false;
bool pat = false;
bool name = false;
while(a==0){
fgets(comando,200,stdin);


char* token;
token  = strtok(comando," ");
while(token!=NULL){
if(strcasecmp(token,"mkdisk")==0){
printf("se encontro mkdisk\n");
mkdisk=true;
}

//si  mkdisk es true reconocer los sigientes comandos
if(mkdisk==true){
    //validar comandos
    if(strcasecmp(token,"-size")==0){
        size = true;
    }else if(size==true){
        tamanio=atoi(token);
        printf("el tamnio del disco es %d\n",tamanio);
        size=false;
    }
    //comando nombre
    if(strcasecmp(token,"-name")==0){
        name = true;
    }else if(name==true){

     strcpy(auxnombre,token);

        printf("el nombre del disco es %s\n",auxnombre);
        name=false;
    }
        //comando path
    if(strcasecmp(token,"-path")==0){
        pat = true;
    }else if(pat==true){

strcpy(auxpath,token);
//token=strtok(NULL,"\"");
        printf("el path del disco es %s\n",auxpath);
        pat=false;
//auxpath=strtok(NULL,"\"");
    }

if(mkdisk==true&&auxnombre!=""&&auxpath!=""&&tamanio!=-1){
strcat(auxpath,"/");
strcat(auxpath,auxnombre);
strcat(auxpath,".bin");
printf(auxpath);

int i=1;
//archivo=fopen(auxpath,"w+b");
/*
char pribin[3]="\0";
for(i;i<=tamanio;i++){
fwrite(pribin,1,sizeof(pribin),archivo);
fseek(archivo,i,SEEK_SET);
}
*/
//fclose(archivo);


}
}

//printf("%s\n",token);
token = strtok(NULL," ::");

}
}
}


