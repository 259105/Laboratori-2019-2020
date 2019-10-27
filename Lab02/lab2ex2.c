//
// Created by s259105 on 12/10/2019.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define maxrighe 1000
#define l_parole 30


typedef struct {
  char codice[l_parole],partenza[l_parole],destinazione[l_parole],data[l_parole],orario_p[l_parole],orario_a[l_parole];
  int ritardo;
}s_tratta;

typedef enum{
    r_date,r_partenza,r_capolinea, r_ritardo,r_ritardo_tot, r_fine,r_err
}comando_e;

void convertiData(char data[]){
    int gg,mm,aa;
    sscanf(data,"%d/%d/%d",&gg,&mm,&aa);
    sprintf(data,"%d/%d/%d",aa,mm,gg);
}

void minuscolo(char parola[]){
    int i,l_parola;
    l_parola=strlen(parola);
    for(i=0;i<l_parola;i++){
        parola[i]=tolower(parola[i]);
    }
}

int caricafile(s_tratta tratta[]){
    FILE *fp;
    int n,i;
    if((fp=fopen("corse.txt","r"))==NULL){
        fprintf(stderr,"Errore lettura file");
        return 0;
    }
    fscanf(fp,"%d",&n);
    for(i=0;i<n;i++){
        fscanf(fp,"%s %s %s %s %s %s %d",tratta[i].codice,tratta[i].partenza,tratta[i].destinazione,tratta[i].data,tratta[i].orario_p,tratta[i].orario_a,&tratta[i].ritardo);
        convertiData(tratta[i].data);//converto la data da gg/mm/aa a aa/mm/gg per fare il confronto con la strcmp
        minuscolo(tratta[i].partenza);
        minuscolo(tratta[i].destinazione);
    }
    return n;
}

void stampacorsa(s_tratta tratta[],int x){
    convertiData(tratta[x].data);
    printf("%s %s %s %s %s %s %d\n",tratta[x].codice,tratta[x].partenza,tratta[x].destinazione,tratta[x].data,tratta[x].orario_p,tratta[x].orario_a,tratta[x].ritardo);
    convertiData(tratta[x].data);
}

comando_e leggicomando(void){
    comando_e c;
    char cmd[l_parole];
    char tabella[r_fine+1][l_parole]={
            "date","partenza","capolinea","ritardo","ritardo_tot","fine"
    };
    printf("Inserire comando tra:\n"
           "-Date <data1> <data2>;(Per elencare tutte le corse partite in un certo intervallo di date)\n"
           "-Partenza <fermata>;(Per elencare tutti le corse partite da una certa fermata)\n"
           "-Capolinea <fermata>;(Per elencare tutti le corse che fanno capolinea in una certa fermata)\n"
           "-Ritardo <data1> <data2>;(Per elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date)\n"
           "-Ritardo_tot <codicetratta>;(Per elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta)\n"
           "-Fine (Termina programma).\n");
    scanf("%s",cmd);
    minuscolo(cmd);
    c=r_date;
    while (c<r_err && strcmp(cmd,tabella[c])!=0){
        c++;
    }
    return c;
}

void date(s_tratta tratta[],int n,char data1[],char data2[]){
    // Prendo in considerazione che la data sia scritta in gg/mm/aa
    //Creo una funzione che mi trasforma la data gg/mm/aa in aa/mm/gg
    // cosi da poterla confrontare con strcmp
    int i;
    convertiData(data1);
    convertiData(data2);
    for(i=0;i<n;i++){
        if(strcmp(data1,tratta[i].data)<=0 && strcmp(tratta[i].data,data2)<=0){ // data1<data<data2
            stampacorsa(tratta,i);
        }
    }
    printf("\n\n");
}

void partenza(s_tratta tratta[],int n,char fermata[]){
    int i;
    for(i=0;i<n;i++){
        if(strcmp(tratta[i].partenza,fermata)==0){
            stampacorsa(tratta,i);
        }
    }
    printf("\n\n");
}

void ritardo(s_tratta tratta[],int n,char data1[],char data2[]){
    int i;
    convertiData(data1);
    convertiData(data2);
    for(i=0;i<n;i++){
        if(tratta[i].ritardo>0 && strcmp(data1,tratta[i].data)<=0 && strcmp(tratta[i].data,data2)<=0){
            stampacorsa(tratta,i);
        }
    }
    printf("\n\n");
}

void ritardotot(s_tratta tratta[],int n,char cod[]){
    int i,tot=0;
    printf("Ritardo totale su quella tratta: ");
    for(i=0;i<n;i++){
        if(strcmp(tratta[i].codice,cod)==0){
            tot+=tratta[i].ritardo;
        }
    }
    printf("%d.\n",tot);
    printf("\n\n");
}

int capolinea(s_tratta tratta[],int n,char fermata[]){
    /*
     * Con capolinea io definisco l'ultima corsa di una determinata linea (codice_tratta), percio se la linea è circolare
     * il programma non identifica un capolinea, diversamente succede se la linea è lineare.
     * Se per esempio usiamo la linea 1(lineare):
     *          Fermata 1 <----> Fermata 2 <----> Fermata 3
     * In questo caso i capolinea sono 1 e 3.
     *
     * Per risolvere questo problema prendo in input la fermata da analizzare, adesso confronto per codice_tratta tutte
     * le partenze fino a trovare la partenza==fermata, adesso parto dal presupposto che è un capolinea e analizzo tutte
     * le destinazioni fino a trovare: destinazione=fermata e che la destinazione della partenza trovata prima deve essere
     * diversa dalla partenza della destinazione trovata ora. Se è vero => non è un capolinea ed esco dal ciclo, se è
     * falso allora è un capolinea: mi salvo l'indice nel vettore e stampo.
     */
    int i,j,capolinea=1,x=0;
    char cod[l_parole];
    for(i=0;i<n;i++){
        if(strcmp(tratta[i].partenza,fermata)==0 && strcmp(cod,tratta[i].codice)!=0){
            capolinea=1;
            strcpy(cod,tratta[i].codice);
            for(j=0;j<n && capolinea;j++){
                if(strcmp(tratta[j].destinazione,fermata)==0 && strcmp(cod,tratta[j].codice)==0
                && strcmp(tratta[i].destinazione,tratta[j].partenza)!=0){
                    printf("%s non e' un capolinea nella linea %s.\n",fermata,cod);
                    capolinea=0;
                }else if(strcmp(tratta[j].destinazione,fermata)==0 && strcmp(cod,tratta[j].codice)==0
                         && strcmp(tratta[i].destinazione,tratta[j].partenza)==0){
                    x=j;
                }
            }
            if(capolinea==1) {
                printf("%s e' un capolinea nella linea %s.\n", fermata, cod);
                stampacorsa(tratta,x);
            }
        }
    }
    return capolinea;
}

int selezionaDati(s_tratta tratta[],int n,comando_e comando){
    char info1[l_parole],info2[l_parole];
    switch (comando){
        case r_date:
            scanf("%s %s",info1,info2);
            minuscolo(info1);
            minuscolo(info2);
            date(tratta,n,info1,info2);
            break;
        case r_partenza:
            scanf("%s",info1);
            minuscolo(info1);
            partenza(tratta,n,info1);
            break;
        case r_capolinea:
            scanf("%s",info1);
            minuscolo(info1);
            capolinea(tratta,n,info1);
            break;
        case r_ritardo:
            scanf("%s %s",info1,info2);
            minuscolo(info1);
            minuscolo(info2);
            ritardo(tratta,n,info1,info2);
            break;
        case r_ritardo_tot:
            scanf("%s",info1);
            minuscolo(info1);
            ritardotot(tratta,n,info1);
            break;
        case r_fine:;
            return 1;
        default:
            fprintf(stderr,"Errore comando inserito\n");
    }
    return 0;
}

int main(){
    s_tratta tratta[maxrighe];
    comando_e comando;
    int continua=0,n;
    if((n=caricafile(tratta))==0){
        return 1;
    }
    while(!continua){
        comando=leggicomando();
        continua=selezionaDati(tratta,n,comando);
    }
    return 0;
}
