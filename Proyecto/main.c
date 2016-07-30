#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void compiler();
FILE *archivo;
char comando[200];

typedef struct mkdiskc{
    char auxnombre[25];
    char auxpath[100];
    int tamanio;
    char unidad[1];
}mkdiskc;


int main()
{
    compiler();
    return 0;
}

void compiler(){
    int a=0;

    bool mkdisk=false;
mkdiskc *  nuevo=malloc(sizeof(mkdiskc));

    char unidad;
    bool size=false;
    bool pat = false;
    bool name = false;
    bool unitb=false;
    while(a==0){
        fgets(comando,200,stdin);


        char* token;
        token  = strtok(comando," ");
        while(token!=NULL){

            if(strcasecmp(token,"mkdisk")==0){
                printf("Comando: mkdisk\n");
                mkdisk=true;
            }

            //si  mkdisk es true reconocer los sigientes comandos
            if(mkdisk==true){


                //validar atributos
                //atributo tamaño
                if(strcasecmp(token,"-size")==0){
                    size = true;
                }else if(size==true){
                    nuevo->tamanio=atoi(token);
                    size=false;
                }
                //atributo nombre
                if(strcasecmp(token,"-name")==0){
                    name = true;
                }else if(name==true){
                    strcpy(nuevo->auxnombre,token);
                    //strtok(nuevo->auxnombre,"");
                    name=false;
                }
                //atributo path
                if(strcasecmp(token,"-path")==0){
                    pat = true;
                }else if(pat==true){
                    strcpy(nuevo->auxpath,token);

                    pat=false;
                }
                //atributo unit
                if(strcasecmp(token,"+unit")==0){
                    unitb = true;
                    strcpy(nuevo->unidad,"m");
                }else if(unitb==true){
                    strcpy(nuevo->unidad,token);
                    unitb=false;
                }

            }

            //termina comando mkdisk
            //printf("%s\n",token);
            token = strtok(NULL," ::");

        }

        if(mkdisk==true&&nuevo->auxnombre!=""&&nuevo->auxpath!=""&&nuevo->tamanio>0){
            if(strcasecmp(nuevo->unidad,"k")==0){
                nuevo->tamanio=nuevo->tamanio*1024;
        }
    else if(strcasecmp(nuevo->unidad,"m")==0){
            nuevo->tamanio=nuevo->tamanio*1024*1024;
        }
            printf("atributos listos:\n %s,%s,%d",nuevo->auxnombre,nuevo->auxpath,nuevo->tamanio);

        int i=1;
        archivo = fopen (strcat(nuevo->auxpath,nuevo->auxnombre), "wb+");
        //mkdisk -name::archivo.bin -size::10 +unit::k -path::/home/javier/Desktop/
        //mkdisk -name::archivo.bin -size::5 -path::/home/javier/Desktop/
         //fprintf(archivo,"\%d",i);

           //fclose(archivo);

        char pribin[3]="\0";
        //tamaño del disco
        for(i;i<=nuevo->tamanio;i++){
        fwrite(pribin,1,sizeof(pribin),archivo);
        fseek(archivo,i,SEEK_SET);
        }
        fclose(archivo);
        mkdisk=false;
free(nuevo);

        }else{
            printf("error");
        }




    }
}


