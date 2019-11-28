//
// Created by s259105 on 19/11/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max 50

typedef struct{
    int gg;
    int mm;
    int aa;
}Data;
typedef struct {
  char codice[6];
  char *nome;
  char *cognome;
  Data data;
  char *via;
  char *citta;
  int cap;
  int nonvuoto;//indica se l'elemento è vuoto o non è vuoto
}Item;
typedef struct node *link;
struct node{
    Item val;
    link next;
};
typedef enum{
    inserimento,ricerca,cancellazione,stampa,fine,err,tast,fil,canc_elem,canc_dat,err1
}comand;

void minuscolo(char *s){
    int i=0;
    for(i=0;i<(int)strlen(s);i++)
        s[i]=tolower(s[i]);
}
int confronta_stringhe(char *s1,char *s2){
    char stri1[max],stri2[max];//Creo questo 2 nuove stringhe per non modificare i caratteri nella struct
    strcpy(stri1,s1);
    strcpy(stri2,s2);
    minuscolo(stri1);
    minuscolo(stri2);
    return strcmp(stri1,stri2);
}
int confrontadate(Data data1,Data data2){
    char data_1[11];
    sprintf(data_1,"%4d/%2d/%2d",data1.aa,data1.mm,data1.gg);
    char data_2[11];
    sprintf(data_2,"%4d/%2d/%2d",data2.aa,data2.mm,data2.gg);
    return strcmp(data_1,data_2);
}
link newnode(Item val,link next){
    link x=malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    x->val=val;
    x->next=next;
    return x;
}
link sortlistins(link h,Item val){
    link x,p;
    if(h==NULL || confrontadate(h->val.data,val.data)<0){
        return newnode(val,h);
    }
    for(x=h->next,p=h;x!=NULL && confrontadate(x->val.data,val.data)>0;p=x,x=x->next);
    p->next=newnode(val,x);
    return h;
}
void printR(link h,FILE *fp){
    if(h==NULL)
        return;
    fprintf(fp,"%s %s %s %d/%d/%d %s %s %d\n",h->val.codice,h->val.nome,h->val.cognome,h->val.data.gg,h->val.data.mm,
            h->val.data.aa,h->val.via,h->val.citta,h->val.cap);
    //stampo anche a video per vedere meglio i miei dati
    fprintf(stdout,"%s %s %s %d/%d/%d %s %s %d\n",h->val.codice,h->val.nome,h->val.cognome,h->val.data.gg,h->val.data.mm,
            h->val.data.aa,h->val.via,h->val.citta,h->val.cap);
    printR(h->next,fp);
}
void printwR(link h){
    char info[max];
    FILE *fp=NULL;
    printf("Inserisci nome file da creare:\n");
    scanf("%s",info);
    fp=fopen(info,"w");
    printR(h,fp);//inizio la ricorsione
    fclose(fp);
}
void printpersona(Item persona){
    fprintf(stdout,"%s %s %s %d/%d/%d %s %s %d\n",persona.codice,persona.nome,persona.cognome,persona.data.gg,persona.data.mm,
            persona.data.aa,persona.via,persona.citta,persona.cap);
}
void fzinserimento(link *h,int t){
    Item temp;
    FILE *fp=NULL;
    char nome[max],cognome[max],via[max],citta[max];
    char file[max];
    int ok;
    if(t){//se da tastiera
        printf("Inserisci <Codice> <Nome> <Cognome> <Data_di_nascita> <Via> <Citta'> <CAP>.\n"
               "Il codice deve essere nel formato AXXXX dove C è una cifra tra 0-9.\n"
               "La data di nascita nel formato gg/mm/aaaa.\n"
               "Il resto dei campi hanno dimensione massima 50 char.\n");
        fscanf(stdin,"%s%s%s%2d/%2d/%4d%s%s%d",temp.codice,nome,cognome,&temp.data.gg,&temp.data.mm,&temp.data.aa,via,citta,&temp.cap);
        temp.nome=strdup(nome);
        temp.cognome=strdup(cognome);
        temp.via=strdup(via);
        temp.citta=strdup(citta);
        temp.nonvuoto=1;
        *h=sortlistins(*h,temp);
    }else{//se da file
        do{
            ok=1;
            printf("Inserisci nome file da caricare:\n");
            scanf("%s",file);
            if((fp=fopen(file,"r"))==NULL){
                fprintf(stderr,"Errore apertura file");
                ok=0;
            }
        }while(!ok);

        while(!feof(fp)){
            fscanf(fp,"%s%s%s%2d/%2d/%4d%s%s%d",temp.codice,nome,cognome,&temp.data.gg,&temp.data.mm,&temp.data.aa,via,citta,&temp.cap);
            temp.nome=strdup(nome);
            temp.cognome=strdup(cognome);
            temp.via=strdup(via);
            temp.citta=strdup(citta);
            temp.nonvuoto=1;
            *h=sortlistins(*h,temp);
        }
    }
    fclose(fp);
    printf("Inserimento completato");
}
void freenode(link node){
    free(node->val.citta);
    free(node->val.cognome);
    free(node->val.nome);
    free(node->val.via);
    free(node);
}
link ricercacodR(link h,char *key){
    if(h==NULL)
        return NULL;
    if(strcmp(h->val.codice,key)==0)
        return h;
    return ricercacodR(h->next,key) ;
}
Item ricercacodwR(link h){
    char info[6];
    Item temp;
    temp.nonvuoto=0;
    printf("Inserisci codice di ricerca:\n"
           "(Il codice deve essere nel formato AXXXX dove C e' una cifra tra 0-9).\n");
    scanf("%s",info);
    temp=ricercacodR(h,info)->val;
    return temp;
}
Item cancelemcod(link *h){
    link *xp,t=NULL;
    Item temp;
    temp.nonvuoto=0;
    char info[6];
    printf("Inserisci codice di ricerca:\n"
           "(Il codice deve essere nel formato AXXXX dove C e' una cifra tra 0-9).\n");
    scanf("%s",info);
    for(xp=h; (*xp)!=NULL; xp=&((*xp)->next)){
        if(strcmp(info,((*xp)->val.codice))==0){
            t=*xp;
            (*xp)=(*xp)->next;
            temp=t->val;
            freenode(t);
            break;
        }
    }
    return temp;
}
Item cancelemdata(link *h,Data data1,Data data2){
    link *xp,t=NULL;
    Item temp;
    temp.nonvuoto=0;
    for(xp=h; (*xp)!=NULL; xp=&((*xp)->next)){
        if(confrontadate(data1,((*xp)->val.data))<=0 && confrontadate(((*xp)->val.data),data2)<=0){
            t=*xp;
            (*xp)=(*xp)->next;
            temp=t->val;
            freenode(t);
            break;
        }
    }
    return temp;
}
comand leggicomando(){
    char s_cmd[14];
    comand cmd;
    char tabella[10][14]={
            "Inserimento","Ricerca","Cancellazione","Stampa","Fine","Err","Tastiera","File","Elemento","Date"
    };
    printf("\nInserisci comando:\n"
           "-Inserimento (inserisce un nuovo elemento da tastiera o nuovi elementi da file);\n"
           "-Ricerca (ricerca per codice di un elemento);\n"
           "-Cancellazione (cancella un dato o piu' dati);\n"
           "-Stampa (Stampa su file);\n"
           "-Fine.\n");
    scanf("%s",s_cmd);
    for(cmd=0;confronta_stringhe(s_cmd,tabella[cmd])!=0 && cmd<=err;cmd++);
    switch(cmd){
        case inserimento:
            printf("Inserire da: Tastiera o File:");
            scanf("%s",s_cmd);
            for(cmd=tast;confronta_stringhe(s_cmd,tabella[cmd]) && cmd<=canc_elem;cmd++);
            if(cmd==canc_elem) return err;
            else if(cmd==tast) return tast;
            else return fil;
        case ricerca:
            return ricerca;
        case cancellazione:
            printf("Eliminazione di: Elemento o Date:");
            scanf("%s",s_cmd);
            for(cmd=canc_elem;confronta_stringhe(s_cmd,tabella[cmd]) && cmd<=err1;cmd++);
            if(cmd==err1) return err;
            else if(cmd==canc_elem) return canc_elem;
            else return canc_dat;
        case stampa:
            return stampa;
        case fine:
            return fine;
        default:
            return err;
    }
}
int selezionacomando(comand cmd,link *h){
    Item temp;
    Data data1,data2;
    switch (cmd){
        case tast:
            fzinserimento(h,1);
            printf("Inserimento compleato\n");
            break;
        case fil:
            fzinserimento(h,0);
            break;
        case ricerca:
            temp=ricercacodwR(*h);
            if(temp.nonvuoto==0)
                fprintf(stderr,"Non ho trovato niente.\n");
            else
                printpersona(temp);
            break;
        case canc_elem:
            temp=cancelemcod(h);
            if(temp.nonvuoto==0)
                fprintf(stderr,"Non ho trovato niente.\n");
            else{
                printf("Ho eleminato:\n");
                printpersona(temp);
            }
            printf("Cancellazione completata.\n");
            break;
        case canc_dat:
            printf("Inserisci intervallo di date: <gg/mm/aaaa> <gg/mm/aaaa>\n");
            scanf("%2d/%2d/%d%2d/%2d/%d",&data1.gg,&data1.mm,&data1.aa,&data2.gg,&data2.mm,&data2.aa);
            temp=cancelemdata(h,data1,data2);//la prima la faccio separatamente
            while (temp.nonvuoto==1){
                printf("Ho eleminato: ");
                printpersona(temp);
                temp=cancelemdata(h,data1,data2);
            }
            printf("Cancellazione completata.\n");
            break;
        case stampa:
            printwR(*h);
            printf("Stampa completata.\n");
            break;
        case fine:
            return 0;
        default:
            fprintf(stderr,"Errore comando inserito non valido\n");
            break;
    }
    return 1;
}

int main(void){
    link h=NULL;
    comand cmd=0;
    int continua=1;

    while (continua) {
        cmd = leggicomando();
        continua = selezionacomando(cmd, &h);
    }
    return 0;
}
