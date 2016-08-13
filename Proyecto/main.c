#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
void compiler();
void automata(char comando[200]);
char *line=NULL;
size_t len=0;
char* token;

ssize_t read;

char comando[200];
/*banderas comandos*/
bool mkdisk=false;
bool rmdisk=false;
bool fdisk=false;
bool mount=false;
bool umount=false;
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
bool id=false;
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
bool Exec=false;
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
    char part_type[2];
    char part_fit[4];
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
typedef struct Umount{
    char id[10];
}Umount;

typedef struct mountpart{
    char iddisk[25];
    char pathDisco[100];
    char nombrepart[16];
}mountpart;

/*termina definicion de structs*/
char nuevotoken[100];
int a=0;
char pathexec[100];
time_t t;
mkdiskc   nuevo;
rmdiskc   removernodo;
Mbrdisk  mbr;
bool tokenleyo=false;
Mount montar;
Umount umontar;
fdiskc  disk;
char unidad;
mountpart particionesmontadas[27][100];
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
    int letras=0;
    /*for(letras;letras<=27;letras++){
        int numero=0;
        for(numero;numero<=100;numero++){

        }
    }*/

    /* loop del programa*/
    while(a==0){


token="\0";


fgets(comando,200,stdin);
/*char caracter[1]="\n";
        char Resultante[100];
        int i = 0;
        int j = 0;
        while (comando[i] != '\0')
        {
            if (caracter[0] != comando[i])
            {
                Resultante[j] = comando[i];
                j++;
            }
            i++;
        }
        Resultante[j] = '\0';
        strcpy(comando, Resultante);
*/

            automata(comando);
    }
}

void automata(char comando[200]){
FILE *archivo;
    token  = strtok(comando," ");

/*ya teniendo el token lo recorremos*/
while(token!=NULL){
    if(strncasecmp(token,"#",1)==0){
        break;
    }
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
                else if(strcasecmp(token,"umount")==0){
                    printf("***************************************\n");
                    printf("        -Comando: umount-\n");
                    printf("***************************************\n");
                    mount=true;
                }
                else if(strcasecmp(token,"exec")==0){
                    printf("***************************************\n");
                    printf("        -Comando: exec-\n");
                    printf("***************************************\n");
                    Exec=true;
                }
    /*comando exec*/
    if(Exec==true){
        if(strcasecmp(token,"-path")==0){
            pat = true;
            int limp=0;
            for(limp;limp<=100;limp++){
                nuevotoken[limp]='\0';
            }
            strcpy(pathexec,"\0");
        }else if(pat==true){
            int cont=1;
            int cont2=0;

            for(cont;cont<strlen(token)-2;cont++){
                nuevotoken[cont2]=token[cont];
                cont2++;}
            strcpy(pathexec,nuevotoken);
            strcat(pathexec,"\0");
            pat=false;
        }
    }

    //si  mkdisk es true reconocer los sigientes comandos
    if(mkdisk==true){

        disk.tamanio=0;
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
            int limp=0;
            for(limp;limp<=25;limp++){
                nuevotoken[limp]='\0';

            }
            strcpy(nuevo.auxnombre,"\0");
        }else if(name==true){
            int cont=1;
            int cont2=0;

            for(cont;cont<strlen(token)-1;cont++){

                nuevotoken[cont2]=token[cont];
                cont2++;}
            strcpy(nuevo.auxnombre,nuevotoken);
            strcat(nuevo.auxnombre,"\0");
            //strtok(nuevo.auxnombre,"");
            name=false;
        }
        //atributo path
        if(strcasecmp(token,"-path")==0){
            pat = true;
            int limp=0;
            for(limp;limp<=25;limp++){
                nuevotoken[limp]='\0';
            }
            strcpy(nuevo.auxpath,"\0");
        }else if(pat==true){
            int cont=1;
            int cont2=0;

            for(cont;cont<strlen(token)-1;cont++){

                nuevotoken[cont2]=token[cont];
                cont2++;}
            strcpy(nuevo.auxpath,nuevotoken);
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
            int limp=0;
            for(limp;limp<=25;limp++){
                nuevotoken[limp]='\0';
            }
            strcpy(removernodo.auxpath,"\0");
        }else if(pat==true){
            int cont=1;
            int cont2=0;

            for(cont;cont<strlen(token)-1;cont++){

                nuevotoken[cont2]=token[cont];
                cont2++;}
            strcpy(removernodo.auxpath,nuevotoken);
            pat=false;
        }

    }
    /*termina comando rmdisk*/
    /*mount*/

    if(mount==true){
        if(strcasecmp(token,"-path")==0){
            pat = true;
            int limp=0;
            for(limp;limp<=25;limp++){
                nuevotoken[limp]='\0';
            }
            strcpy(montar.auxpath,"\0");
        }else if(pat==true){
            int cont=1;
            int cont2=0;

            for(cont;cont<strlen(token)-1;cont++){

                nuevotoken[cont2]=token[cont];
                cont2++;}
            strcpy(montar.auxpath,nuevotoken);
            pat=false;
        }

        if(strcasecmp(token,"-name")==0){
            name = true;
            int limp=0;
            for(limp;limp<=25;limp++){
                nuevotoken[limp]='\0';
            }
            strcpy(montar.auxnombre,"\0");
        }else if(name==true){
            int cont=1;
            int cont2=0;

            for(cont;cont<strlen(token)-1;cont++){

                nuevotoken[cont2]=token[cont];
                cont2++;}
            strcpy(montar.auxnombre,nuevotoken);
            name=false;
        }
    }
    /*umount*/
    if(umount==true){
        if(strcasecmp(token,"-id")==0){
            id = true;
        }else if(id==true){
            strcpy(umontar.id,token);
            id=false;
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
            int limp=0;
            for(limp;limp<=25;limp++){
                nuevotoken[limp]='\0';
            }

            strcpy(disk.auxnombre,"\0");
        }else if(name==true){
            int cont=1;
            int cont2=0;

            for(cont;cont<strlen(token)-1;cont++){

                nuevotoken[cont2]=token[cont];
                cont2++;}


            strcpy(disk.auxnombre,nuevotoken);
            strcat(disk.auxnombre,"\0");


            name=false;

        }

        //atributo path
        if(strcasecmp(token,"-path")==0){
            pat = true;
            int limp=0;
            for(limp;limp<=25;limp++){
                nuevotoken[limp]='\0';
            }
            strcpy(disk.auxpath,"\0");
        }else if(pat==true){
            int cont=1;
            int cont2=0;

            for(cont;cont<strlen(token)-1;cont++){

                nuevotoken[cont2]=token[cont];
                cont2++;}
            strcpy(disk.auxpath,nuevotoken);
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
            strcpy(disk.tipo,"p");
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

/*exec ejecutar comando*/
if(Exec==true&&pathexec!=""){
    archivo = fopen(pathexec,"r");
    char aux[100];
    if(archivo!=NULL){
        while ((read = getline(&line, &len, archivo)) != -1)
        {
            char caracter[1]="\n";
                    char Resultante[100];
                    int i = 0;
                    int j = 0;
                    while (line[i] != '\0')
                    {
                        if (caracter[0] != line[i])
                        {
                            Resultante[j] = line[i];
                            j++;
                        }
                        i++;
                    }
                    Resultante[j] = '\0';
                    strcpy(line, Resultante);
//            printf("%s,", line);
  //          printf("leyendo linea de %zu caracteres:\n", read);

            char com[100];
            /*int li=0;
            for(li;li<strlen(line)-1;li++){

               aux[li]=line[li];
            }*/

//line[strlen(line-1)]="\0";
            strcpy(com,line);

//            com[strlen(com-2)]="\0";
            automata(com);


        }}
//fclose(archivo);
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
        strcpy(mbr.mbr_partition[id].part_type,"0");
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
if(fdisk==true&&disk.tamanio>2097152&&disk.auxpath!=""&&disk.auxnombre!=""){
    if(strcasecmp(disk.fit,"FF")!=0&&strcasecmp(disk.fit,"BF")!=0){
        strcpy(disk.fit,"WF");
    }

    if(strcasecmp(disk.tipo,"e")!=0&&strcasecmp(disk.tipo,"l")!=0){
        strcpy(disk.tipo,"p");
    }


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
                    if(strcasecmp(disk.tipo,"p")==0){
                        strcpy(temp.mbr_partition[init].part_type,"p");
                    }
                    else if(strcasecmp(disk.tipo,"e")==0){
                        strcpy(temp.mbr_partition[init].part_type,"e");
                    }
                    else if(strcasecmp(disk.tipo,"l")==0){
                        strcpy(temp.mbr_partition[init].part_type,"l");
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

                    temp.mbr_partition[init].part_status='1';
                    temp.mbr_partition[init].part_size=disk.tamanio;
                    correcto=true;
                    break;
                }else{
                    /*revisar si es extendida*/
                    if(strcasecmp(temp.mbr_partition[init].part_type,"e")==0){
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
                    printf("Tipo: %s\n",temp.mbr_partition[init].part_type);

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
/*mount*/
int estadopart=0;
if(montar.auxnombre!=""&&montar.auxpath!=""&&mount==true){
    archivo=fopen(montar.auxpath,"r+");
    if(archivo!=NULL){

        Mbrdisk temp;
        fseek(archivo,0L,SEEK_SET);
        fread(&temp,sizeof(Mbrdisk),1,archivo);
        int nopart=0;
        bool existe=false;
        for(nopart;nopart<4;nopart++){
            if(strcasecmp(temp.mbr_partition[nopart].part_name,montar.auxnombre)==0){
                existe=true;
                break;
            }else{
                //printf("%s,%s\n",montar.auxnombre,temp.mbr_partition[nopart].part_name);
            }
        }

        if(existe==false){
            int letras1=0;
            for(letras1;letras1<=27;letras1++){

                int numero1=1;
                for(numero1;numero1<=100;numero1++){
                    if(strcasecmp(particionesmontadas[letras1][1].pathDisco,"")!=0&&strcasecmp(particionesmontadas[letras1][1].pathDisco,montar.auxpath)!=0){
                        break;
                    }
                    if(strcasecmp(particionesmontadas[letras1][numero1].iddisk,"")==0){
                        strcpy(particionesmontadas[letras1][numero1].iddisk,"vd");
                        /*añadimos la letra del disco*/
                        if(letras1==0){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"a");
                        }
                        else if(letras1==1){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"b");
                        }                        else if(letras1==2){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"c");
                        }                        else if(letras1==3){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"d");
                        }                        else if(letras1==4){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"e");
                        }                        else if(letras1==5){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"f");
                        }                        else if(letras1==6){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"g");
                        }                        else if(letras1==7){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"h");
                        }                        else if(letras1==8){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"i");
                        }                        else if(letras1==9){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"j");
                        }                        else if(letras1==10){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"k");
                        }                        else if(letras1==11){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"l");
                        }                        else if(letras1==12){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"m");
                        }                        else if(letras1==13){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"n");
                        }                        else if(letras1==14){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"o");
                        }                        else if(letras1==15){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"p");
                        }                        else if(letras1==16){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"q");
                        }                        else if(letras1==17){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"r");
                        }                        else if(letras1==18){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"s");
                        }                        else if(letras1==19){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"t");
                        }                        else if(letras1==20){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"u");
                        }                        else if(letras1==21){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"v");
                        }                        else if(letras1==22){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"w");
                        }                        else if(letras1==23){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"x");
                        }                        else if(letras1==24){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"y");
                        }                        else if(letras1==25){
                            strcat(particionesmontadas[letras1][numero1].iddisk,"z");
                        }
                        /**/
                        char cadena1[3];
                        sprintf(cadena1, "%d", numero1);
                        strcat(particionesmontadas[letras1][numero1].iddisk,cadena1);
                        strcpy(particionesmontadas[letras1][numero1].pathDisco,montar.auxpath);
                        strcpy(particionesmontadas[letras1][numero1].nombrepart,montar.auxnombre);
                        printf("se monto la particion: %s\n",particionesmontadas[letras1][numero1].nombrepart);

                        estadopart=1;

                        break;
                    }

                }

                if(estadopart==1){
                    estadopart=0;
                    break;
                }
            }//for letras1
        }else{
            printf("**********************************\n No existe la particion\n");
        }//existe
        existe=false;
    }//lectura archivo
    mount=false;

}else if(mount==true&&strcasecmp(montar.auxnombre,"")==0&&strcasecmp(montar.auxpath,"")==0){
    int letras=0;
    printf("Particiones Montadas:\n");
    for(letras;letras<=26;letras){
        int numero=0;
        for(numero;numero<=100;numero++){
            if(strcasecmp(particionesmontadas[letras][numero].iddisk,"")==0){
            }else{
                printf("Nombre: %s, Id:%s\n",particionesmontadas[letras][numero].nombrepart,particionesmontadas[letras][numero].iddisk);
            }
        }
    }
    mount=false;
}



}
void reporteMBR(char path[100])
{
    FILE * reader = fopen(path, "rb+");
    fseek(reader, 0, SEEK_SET);
    FILE * writer = fopen("/home/javier/Desktop/pruebacarpeta/reportembr.txt", "wb+");
    fseek(writer, 0, SEEK_SET);
    Mbrdisk temp;
    int cont= 0;
    fread(&temp, sizeof(Mbrdisk), 1, reader);
    fprintf(writer,"digraph\n{\nrankdir = LR;\nsubgraph clusterEncabezado\n{\nnode[shape = record, height = 0.5];\nlabel=\"hola\"");
    int i;
    for (i = 0; i<4 ; i++){
        if (temp.mbr_partition[i].part_status=='1'){
            fprintf(writer,"Node%d[label = \"%s, size: %d, start: %d, type: %c\"];\n",cont, temp.mbr_partition[i].part_name, temp.mbr_partition[i].part_size,
             temp.mbr_partition[i].part_start, temp.mbr_partition[i].part_type);
            cont++;
        }
    }
    fprintf(writer,"}\n\t}");
    fclose(writer);
    fclose(reader);
    //INVOCANDO GRAPHVIZ
    system("dot -Tjpg /home/javier/Desktop/pruebacarpeta/reportembr.txt -o /home/javier/Desktop/pruebacarpeta/reportembr.jpg");
    //ABRIENDO LA IMAGEN
    system("eog /home/javier/Desktop/pruebacarpeta/reportembr.jpg &");
}


//mkdisk -name::archivo2.dsk -size::1024 +unit::k -path::"/home/javier/Desktop/p ruebacarpeta/"
//rmDisk -path::/home/javier/Desktop/archivo.bin
//mkdisk -name::"archivo.dsk" -path::"/home/javier/Desktop/pruebacarpeta/" -size::10
//mkdisk -path::"/home/javier/Desktop/pruebacarpeta/" -size::10 -name::"disco2.dsk"
//fdisk -path::"/home/javier/Desktop/pruebacarpeta/archivo.dsk" -name::"Particion1" -size::200 -fit::BF
//fdisk -path::"/home/javier/Desktop/pruebacarpeta/disco2.dsk"  -size::200 -name::"Particion1"
//mount -path::"/home/javier/Desktop/pruebacarpeta/archivo.dsk" -name::"Particion1"
//mount -path::"/home/javier/Desktop/pruebacarpeta/disco.dsk" -name::"Particion1"
//exec -path::"/home/javier/Desktop/pruebacarpeta/mio.sh"
