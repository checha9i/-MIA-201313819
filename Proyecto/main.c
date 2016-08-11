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
    char auxnombre[16];
    char anadir[25];
}fdiskc;

typedef struct partition{
    char part_status;
    char part_type;
    char part_fit[3];
    unsigned int part_start;
    unsigned int part_size;
    char part_name[16];
}partition;

typedef struct Mbrdisk{
    int mbr_tamano;
    char mbr_fecha_creacion[17];
    int mbr_disk_signature;
    partition mbr_partition[4];
}Mbrdisk;

typedef struct Mount{
    char auxpath[100];
    char auxnombre[25];
}Mount;

typedef struct mountpart{
    char nombreDisco[25];
    char pathDisco[100];
    char nombrepart[16];
    char id[10];
}mountpart;
/*termina definicion de structs*/

/* main*/
int main()
{
    srand(getpid());
    printf("*******************Fase1******************************\n");
    compiler();
    return 0;
}

/*funcion unica*/
void compiler(){
    int a=0;
    time_t t;
    mkdiskc   nuevo;
    rmdiskc   removernodo;
    Mbrdisk  mbr;
    Mount montar;
    fdiskc  disk;
    char unidad;
    mountpart particionesmontadas[27][100];
    int letras=0;
    for(letras;letras<=27;letras++){
        int numero=0;
        for(numero;numero<=100;numero++){
            strcpy(particionesmontadas[letras][numero].id,"");

        }
    }
    char abecedario[27];
    /*lleno vector abecedario*/
    abecedario[0]='a';
    abecedario[1]='b';
    abecedario[2]='c';
    abecedario[3]='d';
    abecedario[4]='e';
    abecedario[5]='f';
    abecedario[6]='g';
    abecedario[7]='h';
    abecedario[8]='i';
    abecedario[9]='j';
    abecedario[10]='k';
    abecedario[11]='l';
    abecedario[12]='m';
    abecedario[13]='n';
    abecedario[14]='ñ';
    abecedario[15]='o';
    abecedario[16]='p';
    abecedario[17]='q';
    abecedario[18]='r';
    abecedario[19]='s';
    abecedario[20]='t';
    abecedario[21]='u';
    abecedario[22]='v';
    abecedario[23]='w';
    abecedario[24]='x';
    abecedario[25]='y';
    abecedario[26]='z';
    /*banderas comandos*/
    bool mkdisk=false;
    bool rmdisk=false;
    bool fdisk=false;
    bool mount=false;
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
    bool errormkdisk=false;
    bool errorrmdisk=false;
    bool errorfdisk=false;
    bool esize=false;
    bool epat=false;
    bool ename=false;
    bool eunit=false;
    bool etype=false;
    bool efit=false;
    bool edelete=false;
    bool eadd=false;
    bool extend=false;


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
                    }else
            if(strcasecmp(token,"mount")==0){
                printf("***************************************\n");
                printf("        -Comando: mount-\n");
                printf("***************************************\n");
                mount=true;
            }

            //si  mkdisk es true reconocer los sigientes comandos
            if(mkdisk==true){


                //validar atributos
                //atributo tamaño
                if(strcasecmp(token,"-size")==0){
                    size = true;
                }else if(size==true){
                    nuevo.tamanio=atoi(token);
                    nuevo.tamanio=nuevo.tamanio*1024*1024;
                    size=false;
                }
                //atributo nombre
                if(strcasecmp(token,"-name")==0){
                    name = true;
                }else if(name==true){


                    strcpy(nuevo.auxnombre,token);
                    strcat(nuevo.auxnombre,"\0");
                    //strtok(nuevo.auxnombre,"");
                    name=false;
                }
                //atributo path
                if(strcasecmp(token,"-path")==0){
                    pat = true;
                }else if(pat==true){
                    strcpy(nuevo.auxpath,token);
                    strcat(nuevo.auxpath,"\0");
                    pat=false;
                }
                //atributo unit
                if(strcasecmp(token,"+unit")==0){
                    unitb = true;
                    strcpy(nuevo.unidad,"m");
                }else if(unitb==true){
                    strcpy(nuevo.unidad,token);
                    if(nuevo.unidad!="m"||nuevo.unidad!="k"){error=true;
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
                    strcpy(removernodo.auxpath,token);
                    pat=false;
                }

            }
            /*termina comando rmdisk*/
/*mount*/
            if(mount==true){
                if(strcasecmp(token,"-path")==0){
                    pat = true;
                }else if(pat==true){
                    strcpy(montar.auxpath,token);
                    pat=false;
                }

                if(strcasecmp(token,"-name")==0){
                      name = true;
                }else if(name==true){
                    strcpy(montar.auxnombre,token);
                    name=false;
                }
            }

            /*fdisk*/
            if(fdisk==true){
                /*parametros fdisk*/
                //atributo tamaño
                if(strncasecmp(token,"-size",5)==0){
                    fsize = true;
                }else if(fsize==true){
                    disk.tamanio=atoi(token);
                    disk.tamanio=disk.tamanio*1024;
                    printf("***************************************\n");
                    printf("Tamaño de particion: %d\n",disk.tamanio);
                    if(disk.tamanio<=0){
                        error=true;
                        esize=true;
                    }
                    fsize=false;
                }
                //atributo nombre
                if(strcasecmp(token,"-name")==0){
                    name = true;
                }else if(name==true){
                    strcpy(disk.auxnombre,token);
                    strcat(disk.auxnombre,"\0");
                    printf("Nombre: %s\n",disk.auxnombre);

                    name=false;
                }
                //atributo path
                if(strcasecmp(token,"-path")==0){
                    pat = true;
                }else if(pat==true){
                    strcpy(disk.auxpath,token);
                    strcat(disk.auxpath,"\0");
                    printf("Path: %s\n",disk.auxpath);
                    pat=false;
                }
                //atributo unit
                if(strcasecmp(token,"+unit")==0){
                    unitb = true;
                    strcpy(disk.unidad,"K");
                }else if(unitb==true){
                    strcpy(disk.unidad,token);

                    if(strcasecmp(disk.unidad,"M")==0||strcasecmp(disk.unidad,"K")==0||strcasecmp(disk.unidad,"B")==0){
                        error=true;
                        eunit=true;
                    }
                    unitb=false;
                }
                //atributo type
                if(strcasecmp(token,"+type")==0){
                    type = true;
                }else if(type==true){
                    strcpy(disk.tipo,token);
                    if(strcasecmp(disk.tipo,"P")==0||strcasecmp(disk.tipo,"E")==0||strcasecmp(disk.tipo,"L")==0){
                        error=true;
                        etype=true;
                    }
                    type=false;
                }
                //atributo fit
                if(strcasecmp(token,"+fit")==0){
                    fit = true;
                    strcpy(disk.fit,"WF");
                }else if(fit==true){
                    strcpy(disk.fit,token);
                    if(strcasecmp(disk.fit,"BF")!=0||strcasecmp(disk.fit,"FF")!=0||strcasecmp(disk.fit,"WF")!=0){
                        error=true;
                        efit=true;
                    }
                    fit=false;
                }
                //atributo delete
                if(strcasecmp(token,"+delete")==0){
                    deletee = true;
                }else if(deletee==true){
                    strcpy(disk.borrar,token);
                    if(strcasecmp(disk.borrar,"fast")!=0||strcasecmp(disk.borrar,"full")!=0){
                        error=true;
                        edelete=true;
                    }
                    deletee=false;
                }
                //atributo add
                if(strcasecmp(token,"+add")==0){
                    addd = true;
                }else if(addd==true){
                    strcpy(disk.anadir,token);
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
            }
            token = strtok(NULL," ::");
        }/*termina recorrido de token*/


        /*ejecutamos comando rmdisk*/
        if(rmdisk==true){
            char comand[4];
            strcpy(comand,"rm ");
            system(strcat(comand,removernodo.auxpath));
            printf("***************************************\n");
            printf("            -Disco Eliminado- \n");
            printf("***************************************\n");

            rmdisk=false;

        }

        /*ejecutamos comando mkdisk*/
        if(mkdisk==true&&nuevo.auxnombre!=""&&nuevo.auxpath!=""&&nuevo.tamanio>10485759&&nuevo.unidad!=""){



            if(strcasecmp(nuevo.unidad,"k")==0){
                nuevo.tamanio=nuevo.tamanio/1024;
            }
            int i=0;
            archivo=fopen (strncat(nuevo.auxpath,nuevo.auxnombre,100), "wb+");
            if(archivo==NULL){
                fclose(archivo);
                char comao[100];
                strcpy(comao,"mkdir -p ");
                system(strcat(comao,strncat(nuevo.auxpath,nuevo.auxnombre,100)));
                archivo=fopen (nuevo.auxpath, "wb+");
            }

            char pribin[3]="\0";
            //tamaño del disco
            /*escritura de disco*/
            printf("Por favor espere...\n");
            for(i;i<=nuevo.tamanio;i++){
                fwrite(pribin,1,sizeof(pribin),archivo);
                fseek(archivo,i,SEEK_SET);
            }
            /*llenar el mbr*/

            /*tiempo del sistema*/
            time_t tiempo;
            struct tm *info;
            time(&tiempo);
            info=localtime(&tiempo);
            //mbr->mbr_fecha_creacion=time(NULL);
            strftime(mbr.mbr_fecha_creacion,17,"%x - %I:%M\0",info);


            /*termina funcion time*/
            mbr.mbr_disk_signature=rand()%100+1;
            mbr.mbr_tamano=nuevo.tamanio;
            int id=0;
            for(id;id<4;id++){
                strcpy(mbr.mbr_partition[id].part_fit,"");
                mbr.mbr_partition[id].part_size=0;
                mbr.mbr_partition[id].part_start=0;
                mbr.mbr_partition[id].part_status='0';
                mbr.mbr_partition[id].part_type='0';
                strcpy(mbr.mbr_partition[id].part_name,"");


            }
            /*escribimos el mbr en el disco*/
            fseek(archivo,0L,SEEK_SET);
            //            printf("%d",sizeof(mbr));
            fwrite(&mbr,sizeof(mbr),1,archivo);
            fclose(archivo);
            /*cerramos el archivo*/

            printf("***************************************\n");
            printf("         -Disco %s Creado- \n",nuevo.auxnombre);
            if(strcasecmp(nuevo.unidad,"k")==0){
                printf("         -Tamaño:%d Kilobytes- \n",nuevo.tamanio/1024);
            }else{
                printf("         -Tamaño:%d Megabytes- \n",nuevo.tamanio/(1024*1024));

            }

            printf("***************************************\n");
            /*Limpiamos variables y struct usados*/

            /*prueba
            printf("%s",nuevo.auxpath);
            FILE *prueba=fopen(nuevo.auxpath,"r+");


            Mbrdisk *temp;
            fseek(prueba,0L,SEEK_SET);
            fread(&temp,sizeof(Mbrdisk),1,prueba);
            printf("%d,",temp->mbr_tamano);
            printf("%d\n",temp->mbr_disk_signature);
            fclose(prueba);
            fin de prueba*/

            mkdisk=false;
            //free(mbr);



        }

        /*empieza fdisk*/
        if(fdisk==true&&disk.tamanio>0&&disk.auxpath!=""&&disk.auxnombre!=""){

            if(strcasecmp(disk.unidad,"m")==0){
                disk.tamanio=disk.tamanio*1024;
            }
            else if(strcasecmp(disk.unidad,"b")==0){
                disk.tamanio=disk.tamanio/1024;
            }
            archivo=fopen(disk.auxpath,"r+");

            if(archivo!=NULL){

                Mbrdisk temp;
                fseek(archivo,0L,SEEK_SET);
                fread(&temp,sizeof(Mbrdisk),1,archivo);
                printf("fecha: %s\n",temp.mbr_fecha_creacion);
                printf("signature %d\n",temp.mbr_disk_signature);
                printf("tamaño: %d\n",temp.mbr_tamano);
                int tamanodisco;
                tamanodisco=temp.mbr_tamano-sizeof(Mbrdisk);
                if(disk.tamanio<=tamanodisco){

                    /*llenamos el mbr_partition*/


                    /*tipo*/
                    bool correcto=false;
                    int init=0;
                    for(init;init<4;init++){
                        /*tamaño particion*/
                        if(temp.mbr_partition[init].part_size==0){
                            /*type*/
                            if(disk.tipo=='p'){
                                temp.mbr_partition[init].part_type='p';
                            }
                            else if(disk.tipo=='e'){
                                temp.mbr_partition[init].part_type='e';
                            }
                            else if(disk.tipo=='l'){
                                temp.mbr_partition[init].part_type='l';
                            }

                            /*fit*/
                            if(strcasecmp(disk.fit,"BF")==0){
                                strcpy(temp.mbr_partition[init].part_fit,"BF");
                            }
                            else if(strcasecmp(disk.fit,"FF")==0){
                                strcpy(temp.mbr_partition[init].part_fit,"FF");
                            }
                            else if(strcasecmp(disk.fit,"WF")==0){
                                strcpy(temp.mbr_partition[init].part_fit,"WF");
                            }

                            /*unidad y tamaño*/

                                temp.mbr_partition[init].part_size=disk.tamanio;


                            /*start*/
                            if(init==0){
                                temp.mbr_partition[init].part_start=sizeof(Mbrdisk)+1;
                            }else if(init==1){
                                temp.mbr_partition[init].part_start=temp.mbr_partition[init-1].part_start+temp.mbr_partition[init-1].part_size+1;
                            }
                            else if(init==2){
                                temp.mbr_partition[init].part_start=temp.mbr_partition[init-1].part_start+temp.mbr_partition[init-1].part_size+1;
                            }
                            else if(init==3){
                                temp.mbr_partition[init].part_start=temp.mbr_partition[init-1].part_start+temp.mbr_partition[init-1].part_size+1;
                            }

                            strcpy(temp.mbr_partition[init].part_name,disk.auxnombre);
                            printf("Nombre: %s\n",temp.mbr_partition[init].part_name);
                            temp.mbr_partition[init].part_status='1';
                            temp.mbr_partition[init].part_size=disk.tamanio;
                            correcto=true;
                            break;
                        }else{
                            /*revisar si es extendida*/
                            if(temp.mbr_partition[init].part_type=='e'){
                                extend=true;
                            }
                        }
                    }
                    if(correcto=false&&init==3){
                        printf("***************************************\n");
                        printf("     -Ninguna Particion Disponible-");
                        printf("***************************************\n");
                    }else{
                        printf("         -Nuevo MBR-\n");
                        init=0;
                        for(init;init<=3;init++){
                            printf("***************************************\n");
                            printf("Nombre: %s\n",temp.mbr_partition[init].part_name);
                            printf("Tamaño: %d\n",temp.mbr_partition[init].part_size);
                            printf("Inicio: %d\n",temp.mbr_partition[init].part_start);
                            printf("Estado: %c\n",temp.mbr_partition[init].part_status);
                            printf("fit: %s\n",temp.mbr_partition[init].part_fit);
                            printf("Tipo: %c\n",temp.mbr_partition[init].part_type);

                        }

                        fseek(archivo,0L,SEEK_SET);

                        fwrite(&temp,sizeof(temp),1,archivo);
                        fclose(archivo);
                        correcto=false;
                        init=0;
                    }
                    /*lleno el mbr temp*/

                }else{
                    error=true;
                    printf("***************************************\n");
                    printf("                Error:\n");
                    printf("        No hay suficiente espacio:\n");
                    printf("***************************************\n");

                }


            }/*Termina archivo!=NULL*/else{

                error=true;
            }

            fdisk=false;


        }/*termina fdisk*/

        if(montar.auxnombre!=""&&montar.auxpath!=""&&mount==true){
            int letras1=0;
            for(letras1;letras1<=27;letras1++){
                int numero1=0;
                for(numero1;numero1<=100;numero1++){
                    if(particionesmontadas[letras1][numero1].id==""){
                        strcpy(particionesmontadas[letras1][numero1].id,"vd");
                        strcat(particionesmontadas[letras1][numero1].id,abecedario[letras1]);
                        strcat(particionesmontadas[letras1][numero1].id,numero1);
                    }
                }
            }
            mount=false;
        }else if(mount==true){

            mount=false;
        }

    }
}


//mkdisk -name::archivo2.dsk -size::1024 +unit::k -path::"/home/javier/Desktop/p ruebacarpeta/"
//rmDisk -path::/home/javier/Desktop/archivo.bin
//mkdisk -name::archivo.dsk -path::/home/javier/Desktop/pruebacarpeta/ -size::10
//fdisk -path::/home/javier/Desktop/pruebacarpeta/archivo.dsk -name::Particion2 -size::150 -type::e
