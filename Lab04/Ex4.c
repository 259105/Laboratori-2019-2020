//
// Created by s259105 on 03/11/2019.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define l_max_nomi 30
#define l_date 11
#define l_orari 6
#define l_cod 5
#define MAX_CORSE 1000

typedef struct corse CORSE_S;
struct corse {
    char cod[l_cod],part[l_max_nomi],dest[l_max_nomi],data[l_date],ora_p[l_orari],ora_a[l_orari];
    int ritardo;
};

typedef enum{
    data,cod,part,dest,file,video,ricerca,fine,err
}comando_e;

int confronta_data(char *data1,char *data2){
    int aa1,gg1,mm1,gg2,aa2,mm2;
    int n1,n2;
    sscanf(data1,"%d/%d/%d",&gg1,&mm1,&aa1);
    sscanf(data2,"%d/%d/%d",&gg2,&mm2,&aa2);
    n1=gg1+mm1*100+aa1*1000;
    n2=gg2+mm2*100+aa2*1000;
    return n1-n2;
}

void minuscolo(char *s){
    int i=0;
    for(i=0;i<(int)strlen(s);i++)
        s[i]=tolower(s[i]);
}

int confronta(char *str1,char *str2){
    char *stri1=str1,*stri2=str2;//Creo questo 2 nuove stringhe per non modificare i caratteri nella struct
    minuscolo(stri1);
    minuscolo(stri2);
    return strcmp(stri1,stri2);
}
int confrontaItem(CORSE_S *elenco,CORSE_S *x,comando_e cmd){
    switch(cmd){
        case data:
            return confronta_data(elenco->data,x->data);
        case cod:
            return confronta(elenco->cod,x->cod);
        case part:
            return confronta(elenco->part,x->part);
        case dest:
            return  confronta(elenco->dest,x->dest);
        default:
            printf("errore");
            return -1;
    }
}

void swap(CORSE_S **elenco,int i,int j){
    CORSE_S *temp=elenco[i];
    elenco[i]=elenco[j];
    elenco[j]=temp;
}

int partition(CORSE_S **elenco,int l,int r,comando_e cmd){
    int i=l-1,j=r;
    CORSE_S *x=elenco[r]; //elemento pivot
    for(; ;){
        while(confrontaItem(elenco[++i],x,cmd)<0);
        while(confrontaItem(elenco[--j],x,cmd)>0)
            if(j==l)
                break;
        if(i>=j)
            break;
        swap(elenco,i,j);
    }
    swap(elenco,i,r);
    return i;
}

void ordinaRef(CORSE_S **elenco,int l,int r,comando_e cmd){
    //uso QuickSort per ordinare per prima chiave
    int q;
    if(r<=l)
        return;
    q=partition(elenco,l,r,cmd);
    ordinaRef(elenco,l,q-1,cmd);
    ordinaRef(elenco,q+1,r,cmd);
    return;
}

void ordinaRefOra(CORSE_S **elenco,int l,int r){
    //Ordinamento per Insertion Sort
    int i,j;
    CORSE_S *x;
    for(i=l+1;i<r;i++){
        x=elenco[i];
        j=i-1;
        while (j>=l && confronta(elenco[j]->ora_p,x->ora_p)>0){
            elenco[j+1]=elenco[j];
            j--;
        }
        elenco[j+1]=x;
    }
}

int ricercaLineare(CORSE_S **elenco,char *chiave,int n){
    int i;
    for(i=0;i<n;i++)
        if(confronta(elenco[i]->part,chiave)==0)
            return i;
    return -1;
}

int ricercaDicotomica_R(CORSE_S **elenco,char *chiave,int l,int r){
    int q=(l+r)/2;
    if(l>r)
        return -1;
    if (l==r)
        return q;
    if(confronta(elenco[q]->part,chiave)==0)
        return q;
    if(confronta(elenco[q]->part,chiave)>0)
        return ricercaDicotomica_R(elenco,chiave,l,q-1);
    return ricercaDicotomica_R(elenco,chiave,q+1,r);
}

int ricercaDicotomica(CORSE_S **elenco,char *chiave,int n){
    return ricercaDicotomica_R(elenco,chiave,0,n-1);
}

void ordinaRef_wrapper(CORSE_S **elenco,int n,comando_e cmd){
    ordinaRef(elenco,0,n-1,cmd);
}

void ordinaRefOra_wrapper(CORSE_S **S,int n){
    ordinaRefOra(S,0,n-1);
}

void printlog(CORSE_S **elenco,int n,char *file,comando_e cmd){
    int i;
    FILE *fo=fopen(file,"w");
    for(i=0;i<n;i++)
            fprintf(cmd==video?stdout:fo,"%s %s %s %s %s %s %d\n",elenco[i]->cod,elenco[i]->part,elenco[i]->dest,elenco[i]->data,elenco[i]->ora_p,elenco[i]->ora_a,elenco[i]->ritardo);
    fclose(fo);
}

void printcorsa(CORSE_S *elenco){
    printf("%s %s %s %s %s %s %d\n",elenco->cod,elenco->part,elenco->dest,elenco->data,elenco->ora_p,elenco->ora_a,elenco->ritardo);
}

comando_e leggicomando(){
    comando_e c;
    char cmd[8],cmd1[9],tabella[][10]={
            "data","codice","partenza","arrivo","file","video","fine"
    };
    printf("Elenco comandi:\nStampa <File/Video>;\nOrdina <Data/Codice/Partenza/Arrivo>;\nRicerca <Partenza>;\nFine.\nINSERISCI COMANDO:");
    scanf("%s",cmd);
    minuscolo(cmd);
    if(strcmp(cmd,"stampa")==0) {
        scanf("%s",cmd1);
        minuscolo(cmd1);
        for (c = file; c <= err && strcmp(cmd1, tabella[c])!=0; c++);
        printf("Stampa su %s...\n",cmd1);
        return c;
    }else if(strcmp(cmd,"ordina")==0){
        scanf("%s",cmd1);
        for(c=data;c<=err && strcmp(cmd1,tabella[c])!=0;c++);
        printf("Ordinamento per %s...",cmd1);
        return c;
    }else if(strcmp(cmd,"ricerca")==0){
        return ricerca;
    }else if(strcmp(cmd,"fine")==0){
        return fine;
    }else{
        return err;
    }
}

int main(void){
    CORSE_S corse[MAX_CORSE],*corsexdata[MAX_CORSE],*corsexcod[MAX_CORSE],*corsexpart[MAX_CORSE],*corsexdest[MAX_CORSE];
    CORSE_S **V[]={corsexdata,corsexcod,corsexpart,corsexdest};//Vettore di puntatori a puntatori di corse
    FILE *fp;
    comando_e cmd;
    int ord[4]={0}; //Vettore creato di lunghezza uguale agli ordinamenti possibili, è settato su 0 o 1 cosi da poter
                    //memorizzare se il vettore è stato già ordinato o meno.
                    // Se ==0 non ordinato , se ==1 è ordinato
    char info[l_max_nomi];
    int n=0,i,stato=0,found;

    if((fp=fopen("corse.txt","r"))==NULL){
        fprintf(stderr,"Errore apertura file");
        return 1;
    }
    //lettura file e scrittura su struct
    while((fscanf(fp,"%s%s%s%s%s%s%d",corse[n].cod,corse[n].part,corse[n].dest,corse[n].data,corse[n].ora_p,corse[n].ora_a,&corse[n].ritardo))!=EOF)
        n++;
    for(i=0;i<n;i++)
        corsexpart[i]=corsexdest[i]=corsexcod[i]=corsexdata[i]=&corse[i];
    cmd=leggicomando();
    do{
        if(cmd>=data && cmd<=dest) {
            stato=cmd;
            if(!ord[cmd]){
                ordinaRef_wrapper(V[stato],n,cmd);
                if (cmd==data)
                    ordinaRefOra_wrapper(corsexdata,n); //correggere ricerca non ordina l'ultimo bho
                ord[cmd]=1;
            }
            printf("completato\n");
        }
        else if(cmd==video || cmd==file){
            if(cmd==file){
                printf("Inserisci nome file txt da creare:");
                scanf("%s",info);
            }
            printlog(V[stato],n,info,cmd);
            printf("completata\n");
        }
        else if(cmd==ricerca) {
            scanf("%s", info);
            if(ord[part]==1)
                found=ricercaDicotomica(V[part],info,n);
            else
                found=ricercaLineare(V[stato],info,n);

            if(found==-1)
                fprintf(stderr,"Errore, ricerca senza successo, stazione di partenza non trovata.\n");
            else
                printcorsa(V[stato][found]);
        }else
            fprintf(stderr,"Errore comando inserito non valido");
        cmd=leggicomando();
    }while(cmd!=fine);
}
