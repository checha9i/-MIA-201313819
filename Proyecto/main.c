#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
void compiler();
FILE *archivo;
char comando[200];
/* Definicion de Structs*/
typedef struct mkdiskc{
    char auxnombre[25];
    char auxpath[100];
    unsigned int tamanio;
    char unidad[1];
}mkdiskc;

typedef struct rmdiskc{
    char auxpath[100];
}rmdiskc;

typedef struct fdiskc{
    int tamanio;
    char unidad[3];
    char auxpath[100];
    char tipo[5];
    char fit[3];
    char borrar[7];
    char auxnombre[25];
    char anadir[25];
}fdiskc;
typedef struct partition{
    char part_status;
    char part_type;
    char *part_fit;
    unsigned int part_start;
    unsigned int part_size;
    char part_name[16];
}partition;

typedef struct Mbrdisk{
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    partition mbr_partition[3];
}Mbrdisk;
/*termina definicion de structs*/

/* main*/
int main()
{
    printf("*******************Fase1******************************\n");
    compiler();
    return 0;
}
/*funcion unica*/
void compiler(){
    int a=0;
    mkdiskc *  nuevo=malloc(sizeof(mkdiskc));
    rmdiskc *  removernodo=malloc(sizeof(rmdiskc));
    Mbrdisk * mbr=malloc(sizeof(Mbrdisk));
    fdiskc * disk=malloc(sizeof(fdiskc));
    char unidad;
    /*banderas comandos*/
    bool mkdisk=false;
    bool rmdisk=false;
    bool fdisk=false;
    /*banderas parametros*/
    bool size=false;
    bool pat = false;
    bool name = false;
    bool unitb=false;
    bool type=false;
    bool fit=false;
    bool deletee=false;
    bool addd=false;
    bool error=false;
    bool fsize=false;
    /*banderas errores*/
    bool errormkdisk;
    bool errorrmdisk;
    bool errorfdisk;
    bool esize;
    bool epat;
    bool ename;
    bool eunit;
    bool etype;
    bool efit;
    bool edelete;
    bool eadd;

    /* loop del programa*/
    while(a==0){
        fgets(comando,200,stdin);
        char* token;
        token  = strtok(comando," ");
        /*ya teniendo el token lo recorremos*/
        while(token!=NULL){
            if(strcasecmp(token,"mkdisk")==0){
                printf("***************************************\n");
                printf("        -Comando: mkdisk-\n");
                printf("***************************************\n");
                mkdisk=true;
            }else
                if(strcasecmp(token,"rmDisk")==0){
                    printf("***************************************\n");
                    printf("        -Comando: rmDisk-\n");
                    printf("***************************************\n");
                    rmdisk=true;
                }else
                    if(strcasecmp(token,"fdisk")==0){
                        printf("***************************************\n");
                        printf("        -Comando: fdisk-\n");
                        printf("***************************************\n");
                        fdisk=true;
                    }

            //si  mkdisk es true reconocer los sigientes comandos
            if(mkdisk==true){


                //validar atributos
                //atributo tamaño
                if(strcasecmp(token,"-size")==0){
                    size = true;
                }else if(size==true){
                    nuevo->tamanio=atoi(token);
           nuevo->tamanio=nuevo->tamanio*1024*1024;
                    size=false;
                }
                //atributo nombre
                if(strcasecmp(token,"-name")==0){
                    name = true;
                }else if(name==true){


                    strcpy(nuevo->auxnombre,token);
strcat(nuevo->auxnombre,"\0");
                    //strtok(nuevo->auxnombre,"");
                    name=false;
                }
                //atributo path
                if(strcasecmp(token,"-path")==0){
                    pat = true;
                }else if(pat==true){
                    strcpy(nuevo->auxpath,token);
                    strcat(nuevo->auxpath,"\0");
                    pat=false;
                }
                //atributo unit
                if(strcasecmp(token,"+unit")==0){
                    unitb = true;
                    strcpy(nuevo->unidad,"m");
                }else if(unitb==true){
                    strcpy(nuevo->unidad,token);
if(nuevo->unidad!="m"||nuevo->unidad!="k"){error=true;
eunit=true;}
                    unitb=false;
                }

            }
            /*termina comando mkdisk*/

            //comando rmdisk

            if(rmdisk==true){
                if(strcasecmp(token,"-path")==0){
                    pat = true;
                }else if(pat==true){
                    strcpy(removernodo->auxpath,token);
                    pat=false;
                }

            }
            /*termina comando rmdisk*/

            if(fdisk==true){
                /*parametros fdisk*/
                //atributo tamaño
                if(strncasecmp(token,"-size",5)==0){
                    fsize = true;
                }else if(fsize==true){
                    disk->tamanio=atoi(token);

                    if(disk->tamanio<=0){
                        error=true;
                        esize=true;
                    }
                    fsize=false;
                }
                //atributo nombre
                if(strcasecmp(token,"-name")==0){
                    name = true;
                }else if(name==true){
                    strcpy(disk->auxnombre,token);
                    name=false;
                }
                //atributo path
                if(strcasecmp(token,"-path")==0){
                    pat = true;
                }else if(pat==true){
                    strcpy(disk->auxpath,token);
                    pat=false;
                }
                //atributo unit
                if(strcasecmp(token,"+unit")==0){
                    unitb = true;
                    strcpy(disk->unidad,"K");
                }else if(unitb==true){
                    strcpy(disk->unidad,token);
                    if(strcasecmp(disk->unidad,"M")==0||strcasecmp(disk->unidad,"K")==0||strcasecmp(disk->unidad,"B")==0){
                        error=true;
                        eunit=true;
                    }
                    unitb=false;
                }
                //atributo type
                if(strcasecmp(token,"+type")==0){
                    type = true;
                }else if(type==true){
                    strcpy(disk->tipo,token);
                    if(strcasecmp(disk->tipo,"P")==0||strcasecmp(disk->tipo,"E")==0||strcasecmp(disk->tipo,"L")==0){
                        error=true;
                        etype=true;
                    }
                    type=false;
                }
                //atributo fit
                if(strcasecmp(token,"+fit")==0){
                    fit = true;
                }else if(fit==true){
                    strcpy(disk->fit,token);
                    if(strcasecmp(disk->fit,"BF")!=0||strcasecmp(disk->fit,"FF")!=0||strcasecmp(disk->fit,"WF")!=0){
                        error=true;
                        efit=true;
                    }
                    fit=false;
                }
                //atributo delete
                if(strcasecmp(token,"+delete")==0){
                    deletee = true;
                }else if(deletee==true){
                    strcpy(disk->borrar,token);
                    if(disk->borrar!="fast"||disk->borrar!="full"){
                        error=true;
                        edelete=true;
                    }
                    deletee=false;
                }
                //atributo add
                if(strcasecmp(token,"+add")==0){
                    addd = true;
                }else if(addd==true){
                    strcpy(disk->anadir,token);
                    addd=false;
                }


            }
            /*termina comando fdisk*/

            /*parseamos los dos puntos*/


            if(error==true){
                printf("***************************************\n");
                printf("     -Error Parametro-\n");
                if(edelete==true){
                    printf(" -Error en delete-\n");
                    edelete=false;
                }
                if(efit==true){
                    printf(" -Error en fit-\n");
                    efit=false;
                }
                if(ename==true){
                    printf(" -Error en name-\n");
                    ename=false;
                }
                if(epat==true){
                    printf(" -Error en path-\n");
                    epat=false;
                }
                if(esize==true){
                    printf(" -Error en size-\n");
                    esize=false;
                }
                if(etype==true){
                    printf(" -Error en type-\n");
                    etype=false;
                }
                if(eunit==true){
                    printf(" -Error en unit-\n");
                    eunit=false;
                }
                printf("***************************************\n");
                mkdisk=false;
                rmdisk=false;
                fdisk=false;
                error=false;
                free(nuevo);
                free(mbr);
                free(removernodo);
                free(disk);
                disk=malloc(sizeof(fdiskc));
                removernodo=malloc(sizeof(rmdiskc));
                mbr=malloc(sizeof(Mbrdisk));
                nuevo=malloc(sizeof(mkdiskc));
            }
        token = strtok(NULL," ::");
        }/*termina recorrido de token*/


        /*ejecutamos comando rmdisk*/
        if(rmdisk==true){
            char comand[4];
            strcpy(comand,"rm ");
            system(strcat(comand,removernodo->auxpath));
            printf("***************************************\n");
            printf("            -Disco Eliminado- \n");
            printf("***************************************\n");
            free(removernodo);
            rmdisk=false;

        }

        /*ejecutamos comando mkdisk*/
        if(mkdisk==true&&nuevo->auxnombre!=""&&nuevo->auxpath!=""&&nuevo->tamanio>10485759&&nuevo->unidad!=""){



            if(strcasecmp(nuevo->unidad,"k")==0){
                nuevo->tamanio=nuevo->tamanio/1024;
            }
            int i=0;
            archivo=fopen (strncat(nuevo->auxpath,nuevo->auxnombre,100), "wb+");
            if(archivo==NULL){
                fclose(archivo);
                char comao[100];
                strcpy(comao,"mkdir -p ");
                system(strcat(comao,strncat(nuevo->auxpath,nuevo->auxnombre,100)));
                archivo=fopen (nuevo->auxpath, "wb+");
            }

            char pribin[3]="\0";
            //tamaño del disco
            /*escritura de disco*/
            printf("Por favor espere...\n");
            for(i;i<=nuevo->tamanio;i++){
                fwrite(pribin,1,sizeof(pribin),archivo);
                fseek(archivo,i,SEEK_SET);
            }
            /*llenar el mbr*/
            mbr->mbr_disk_signature=rand()%100+1;
            /*tiempo del sistema*/
            time_t tiempo;
            struct tm *info;
            time(&tiempo);
            info=localtime(&tiempo);
            mbr->mbr_fecha_creacion=time(NULL);
            //strftime(mbr->mbr_fecha_creacion,17,"%x - %I:%M%p",info);
            /*termina funcion time*/
            mbr->mbr_tamano=nuevo->tamanio;
            int id=0;
            for(id;id<=3;id++){
            mbr->mbr_partition[id].part_fit=NULL;
            mbr->mbr_partition[id].part_size=0;
            mbr->mbr_partition[id].part_start=0;
            mbr->mbr_partition[id].part_status=NULL;
            mbr->mbr_partition[id].part_type=NULL;
            }
            /*escribimos el mbr en el disco*/
            fseek(archivo,0L,SEEK_SET);
            fwrite(&mbr,sizeof(mbr),1,archivo);
            fclose(archivo);
            /*cerramos el archivo*/

            printf("***************************************\n");
            printf("         -Disco %s Creado- \n",nuevo->auxnombre);
            if(strcasecmp(nuevo->unidad,"k")==0){
                printf("         -Tamaño:%d Kilobytes- \n",nuevo->tamanio/1024);
            }else{
                printf("         -Tamaño:%d Megabytes- \n",nuevo->tamanio/(1024*1024));
            }

            printf("***************************************\n");
            /*Limpiamos variables y struct usados*/

            /*prueba
            printf("%s",nuevo->auxpath);
            FILE *prueba=fopen(nuevo->auxpath,"r+");


            Mbrdisk *temp;
            fseek(prueba,0L,SEEK_SET);
            fread(&temp,sizeof(Mbrdisk),1,prueba);
            printf("%d,",temp->mbr_tamano);
            printf("%d\n",temp->mbr_disk_signature);
            fclose(prueba);
            fin de prueba*/

            mkdisk=false;
            //free(mbr);
            free(nuevo);
            nuevo=malloc(sizeof(mkdiskc));
            mbr=malloc(sizeof(Mbrdisk));
        }
        if(fdisk==true&&disk->tamanio>0&&disk->auxpath!=""&&disk->auxnombre!=""){

            archivo=fopen(disk->auxpath,"r+");
            if(archivo){
                printf("leyendo archivo");
                Mbrdisk *temp;
                fseek(archivo,0L,SEEK_SET);
                fread(&temp,sizeof(Mbrdisk),1,archivo);
int tamanodisco;
tamanodisco=temp->mbr_tamano-sizeof(Mbrdisk);
if(disk->tamanio<=tamanodisco){

    /*llenamos el mbr_partition*/

    printf("si tiene algo");
    /*tipo*/
    bool correcto=false;
    int init=0;
    for(init;init<=3;init++){
        if(temp->mbr_partition[init].part_size==0){
    if(strcasecmp(disk->tipo,"p")==0){
        strcpy(temp->mbr_partition[init].part_type,"p");
    }
    else if(strcasecmp(disk->tipo,"e")==0){
        strcpy(temp->mbr_partition[init].part_type,"e");
    }
    else if(strcasecmp(disk->tipo,"l")==0){
        strcpy(temp->mbr_partition[init].part_type,"l");
    }

    /*fit*/
    if(strcasecmp(disk->fit,"BF")==0){
        strcpy(temp->mbr_partition[init].part_fit,"BF");
    }
    else if(strcasecmp(disk->fit,"FF")==0){
        strcpy(temp->mbr_partition[init].part_fit,"FF");
    }
    else if(strcasecmp(disk->fit,"WF")==0){
        strcpy(temp->mbr_partition[init].part_fit,"WF");
    }

    /*unidad y tamaño*/
    if(strcasecmp(disk->unidad,"B")==0){
        temp->mbr_partition[init].part_size=disk->tamanio;
    } else if(strcasecmp(disk->unidad,"K")==0){
        temp->mbr_partition[init].part_size=disk->tamanio*1024;
    } else if(strcasecmp(disk->unidad,"M")==0){
                temp->mbr_partition[init].part_size=disk->tamanio*1024*1024;
    }
    /**/


}

    printf("***************************************\n");
    printf("     -Ninguna Particion Disponible-");
    printf("***************************************\n");

}
}else{
error=true;
}

               fclose(archivo);
            }else{

               error=true;
            }
            if(error=true){}
        }



    }
}


//mkdisk -name::archivo2.dsk -size::1024 +unit::k -path::/home/javier/Desktop/pruebacarpeta/
//rmDisk -path::/home/javier/Desktop/archivo.bin
//mkdisk -name::archivo.dsk -path::/home/javier/Desktop/pruebacarpeta/ -size::3
//fdisk –size::300 –path::/home/javier/Desktop/pruebacarpeta/archivo.dsk –name::Particion1
