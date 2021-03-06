//
// Created by s259105 on 06/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define l_max_nomi 30
#define l_date 11
#define l_orari 6
#define l_cod 10
#define l_cmd 12
#define inizio_file "corse.txt"

typedef struct corse {
    char *cod,*part,*dest,*data,*ora_p,*ora_a;
    int ritardo;
} CORSE_S;
//Creo una strutta che contiene gli ordinamenti possibili
typedef struct ordin{
    CORSE_S **ord;
    int fatto;//fatto indica se è stato ordinato
}ORDINAMENTI_S;
typedef enum{
    data,cod,part,dest,file,video,list_date,list_part,list_capol,list_rit,list_rit_tot,ricerca,carica,fine,err
}comando_e;

int n=0,stato;    //stato indica lo stato attuale della macchina, ovvero che ordinamento è stato fatto per ultimo
comando_e cmd;          //n indica il numero di struct presenti, dim indica l'ultima aggiunta di struct

CORSE_S* caricafile(CORSE_S *precedente,char *file,int t){
    FILE *fp;
    CORSE_S *elenco;
    char cod[l_cod],part[l_max_nomi],dest[l_max_nomi],data[l_date],ora_p[l_date],ora_a[l_date];
    int ritardo;
    int i;
    if((fp=fopen(file,"r"))==NULL){
        fprintf(stderr,"Errore lettura file");
        return NULL;
    }
    fscanf(fp,"%d",&n);
    if(!t)//se è 0 vul dire che è la prima volta che si chiama la funzione, ovvero all'avvio del programma
        elenco=(CORSE_S*)malloc(n * sizeof(CORSE_S));
    else
        elenco=(CORSE_S*)realloc(precedente,n* sizeof(CORSE_S));
    for(i=0;i<n;i++){
        fscanf(fp,"%s%s%s%s%s%s%d",cod,part,dest,data,ora_p,ora_a,&ritardo);
        elenco[i].cod=strdup(cod); //con questa funzione si alloca e si copia automaticamente
        elenco[i].part=strdup(part);
        elenco[i].dest=strdup(dest);
        elenco[i].data=strdup(data);
        elenco[i].ora_p=strdup(ora_p);
        elenco[i].ora_a=strdup(ora_a);
        elenco[i].ritardo=ritardo;
    }
    fclose(fp);
    /*for(i=0;i<n;i++){
        printf("%s %s %s %s %s %s %d\n",elenco[i].cod,elenco[i].part,elenco[i].dest,elenco[i].data,elenco[i].ora_p,elenco[i].ora_a,elenco[i].ritardo);
    }*/
    return elenco;
}

ORDINAMENTI_S* creaOrdinamenti(CORSE_S *elenco,ORDINAMENTI_S *precedente,int t){
    int i,j;
    if(t){
        for(i=0;i<4;i++)
            precedente[i].ord=(CORSE_S **)realloc(precedente[i].ord,n* sizeof(CORSE_S*));
    }else{
        precedente=malloc(4* sizeof(ORDINAMENTI_S));
        for(i=0;i<4;i++)
            precedente[i].ord=(CORSE_S **)malloc(n* sizeof(CORSE_S*));
    }

    for(i=0;i<4;i++){
        for(j=0;j<n;j++)
            precedente[i].ord[j]=&elenco[j];
        precedente[i].fatto=0;
    }
    return precedente;
}

void minuscolo(char *s){
    int i=0;
    for(i=0;i<(int)strlen(s);i++)
        s[i]=tolower(s[i]);
}
void printcorsa(CORSE_S *elenco){
    printf("%s %s %s %s %s %s %d\n",elenco->cod,elenco->part,elenco->dest,elenco->data,elenco->ora_p,elenco->ora_a,elenco->ritardo);
}
void printlog(CORSE_S **elenco,char *file){
    int i;
    FILE *fo=fopen(file,"w");
    for(i=0;i<n;i++)
        fprintf(cmd==video?stdout:fo,"%s %s %s %s %s %s %d\n",elenco[i]->cod,elenco[i]->part,elenco[i]->dest,elenco[i]->data,elenco[i]->ora_p,elenco[i]->ora_a,elenco[i]->ritardo);
    fclose(fo);
}
int confronta_stringhe(char *s1,char *s2){
    char stri1[l_max_nomi],stri2[l_max_nomi];//Creo questo 2 nuove stringhe per non modificare i caratteri nella struct
    strcpy(stri1,s1);
    strcpy(stri2,s2);
    minuscolo(stri1);
    minuscolo(stri2);
    return strcmp(stri1,stri2);
}
int confronta_stringhe_parziali(char *s1,char *s2){
    char stri1[l_max_nomi],stri2[l_max_nomi];//Creo questo 2 nuove stringhe per non modificare i caratteri nella struct
    //questa funzione ha come chiave di ricerca s2
    strcpy(stri1,s1);
    strcpy(stri2,s2);
    minuscolo(stri1);
    minuscolo(stri2);
    return strncmp(stri1,stri2,strlen(s2));
}
int confronta_data(char *data1,char *data2){
    //vale se le date sono nel fomato gg/mm/aaaa
    int aa1,gg1,mm1,gg2,aa2,mm2;
    int n1,n2;
    sscanf(data1,"%d/%d/%d",&gg1,&mm1,&aa1);
    sscanf(data2,"%d/%d/%d",&gg2,&mm2,&aa2);
    n1=gg1+mm1*100+aa1*10000;
    n2=gg2+mm2*100+aa2*10000;
    return n1-n2;
}
int confrontaItem(CORSE_S *elenco,CORSE_S *x){
    switch(cmd){
        case data:
            return strcmp(elenco->ora_p,x->ora_p);
        case cod:
            return confronta_stringhe(elenco->cod,x->cod);
        case part:
            return confronta_stringhe(elenco->part,x->part);
        case dest:
            return confronta_stringhe(elenco->dest,x->dest);
        default: //è stato messo (anche se non capiterà mai) perche sennò non avrebbe chiuso lo switch
            printf("errore");
            return -1;
    }
}
void ordinaRef(CORSE_S **elenco,int l,int r){
    //Ordinamento per Insertion Sort
    int i,j;
    CORSE_S *x;
    for(i=l+1;i<=r;i++){
        x=elenco[i];
        j=i-1;
        while (j>=l && confrontaItem(elenco[j],x)>0){
            elenco[j+1]=elenco[j];
            j--;
        }
        elenco[j+1]=x;
    }
    if(cmd==data){//Doppio ordinamanto con chiave consecutiva
        for(i=l+1;i<=r;i++){
            x=elenco[i];
            j=i-1;
            while (j>=l && confronta_data(elenco[j]->data,x->data)>0){
                elenco[j+1]=elenco[j];
                j--;
            }
            elenco[j+1]=x;
        }
    }
}
void ordinaRef_wrapper(CORSE_S **S){
    ordinaRef(S,0,n-1);
}
int ricercaDicotomica_R(CORSE_S **elenco,char *chiave,int l,int r){
    // la ricerca dicotomica restituisce l'indice della partenza trovata
    int q=(l+r)/2;
    if(l>r)
        return -1;
    if (l==r)
        return q;
    if(confronta_stringhe_parziali(elenco[q]->part,chiave)==0)
        return q;
    if(confronta_stringhe_parziali(elenco[q]->part,chiave)>0)
        return ricercaDicotomica_R(elenco,chiave,l,q-1);
    return ricercaDicotomica_R(elenco,chiave,q+1,r);
}
void ricercalineareAdiacenti(CORSE_S **elenco,char *chiave,int q){
    int l=q,r=q,i;
    while (confronta_stringhe_parziali(elenco[l]->part,chiave)==0 && l-1>=0)
        l--;
    while (confronta_stringhe_parziali(elenco[r]->part,chiave)==0 && r+1<=n)
        r++;
    //se il ciclo è terminato a causa della fine del vettore allora l e r sono giusti, senno bisogna aumentare o
    //o decrementare rispettivamente gli indici l e r
    if(l-1>=0)
        l++;
    if(r+1<=n)
        r--;
    for(i=l;i<=r;i++)
        printcorsa(elenco[i]);
}
int ricercaDicotomicastampa(CORSE_S **elenco,char *chiave){
    int q;
    q=ricercaDicotomica_R(elenco,chiave,0,n-1);
    if(q!=-1)
        ricercalineareAdiacenti(elenco,chiave,q);
    else
        return -1;
    return 1;
}
int ricercaLinearestampa(CORSE_S **elenco,char *chiave){
    int i,trovato=-1;
    for(i=0;i<n;i++)
        if(confronta_stringhe_parziali(elenco[i]->part,chiave)==0){
            printcorsa(elenco[i]);
            trovato=1;
        }
    return trovato;
}
void date(CORSE_S **elenco_corse,char *data1,char *data2){
    int i;
    for(i=0;i<n;i++){
        if(confronta_data(data1,elenco_corse[i]->data)<=0 && confronta_data(elenco_corse[i]->data,data2)<=0){ // data1<data<data2
            printcorsa(elenco_corse[i]);
        }
    }
    printf("\n\n");
}
void partenza(CORSE_S **elenco_corse,char *fermata){
    int i;
    for(i=0;i<n;i++){
        if(confronta_stringhe(elenco_corse[i]->part,fermata)==0){
            printcorsa(elenco_corse[i]);
        }
    }
    printf("\n\n");
}
int capolinea(CORSE_S **elenco_corse,char *fermata){
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
    char cod[l_max_nomi];
    for(i=0;i<n;i++){
        if(confronta_stringhe(elenco_corse[i]->part,fermata)==0 && strcmp(cod,elenco_corse[i]->cod)!=0){
            capolinea=1;//suppongo sia capolinea
            strcpy(cod,elenco_corse[i]->cod);
            for(j=0;j<n && capolinea;j++){
                if(confronta_stringhe(elenco_corse[j]->dest,fermata)==0 && strcmp(cod,elenco_corse[j]->cod)==0
                   && confronta_stringhe(elenco_corse[i]->dest,elenco_corse[j]->part)!=0){
                    printf("%s non e' un capolinea nella linea %s.\n",fermata,cod);
                    capolinea=0;
                }else if(confronta_stringhe(elenco_corse[j]->dest,fermata)==0 && strcmp(cod,elenco_corse[j]->cod)==0
                         && confronta_stringhe(elenco_corse[i]->dest,elenco_corse[j]->part)==0){
                    x=j;
                }
            }
            if(capolinea==1) {
                printf("%s e' un capolinea nella linea %s.\n", fermata, cod);
                printcorsa(elenco_corse[x]);
            }
        }
    }
    return capolinea;
}
void ritardo(CORSE_S **elenco_corse,char *data1,char *data2){
    int i;
    for(i=0;i<n;i++){
        if(elenco_corse[i]->ritardo>0 && confronta_data(data1,elenco_corse[i]->data)<=0 && confronta_data(elenco_corse[i]->data,data2)<=0){
            printcorsa(elenco_corse[i]);
        }
    }
    printf("\n\n");
}
void ritardotot(CORSE_S **elenco_corse,char *cod){
    int i,tot=0;
    printf("Ritardo totale su quella tratta: ");
    for(i=0;i<n;i++){
        if(strcmp(elenco_corse[i]->cod,cod)==0){
            tot+=elenco_corse[i]->ritardo;
        }
    }
    printf("%d minuti.\n",tot);
    printf("\n\n");
}
comando_e leggicomando(){
    comando_e c;
    char cmd1[8],cmd2[9];
    char *CMD1[l_cmd]={ //tabella che serve per confrontare il primo comando
            "elenco","stampa","ordina","ricerca","carica","fine"
    };
    char CMD2[14][l_cmd]={ //tabella che serve per confrontare il secondo comando
            //ho messo che deve avere 14 elementi perche cosi ha gli stessi elementi di comando_e, se non ha gli stessi elementi
            //quando vado a fare il confronto nel for per vedere che comando è, il confronto verrà fatto tra una stringa
            //e un NULL quindi mi darebbe errore
            "data","codice","partenza","arrivo","file","video","date","partenza","capolinea","ritardo","ritardo_tot"
    };
    printf("\n------------------------------------------------------------------------------------------------------------------------"
            "Elenco comandi:\n"
           "Elenco Date;(Per elencare tutte le corse partite in un certo intervallo di date)\n"
           "Elenco Partenza;(Per elencare tutti le corse partite da una certa fermata)\n"
           "Elenco Capolinea;(Per elencare tutti le corse che fanno capolinea in una certa fermata)\n"
           "Elenco Ritardo;(Per elencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di date)\n"
           "Elenco Ritardo_tot;(Per elencare il ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta)\n"
           "Stampa <File/Video>;\n"
           "Ordina <Data/Codice/Partenza/Arrivo>;\n"
           "Ricerca;\n"
           "Carica;\n"
           "Fine (Termina programma).\n"
           "------------------------------------------------------------------------------------------------------------------------\n"
           "INSERISCI COMANDO:");
    scanf("%s",cmd1);
    minuscolo(cmd1);
    if(strcmp(cmd1,CMD1[0])==0){
        scanf("%s",cmd2);
        for(c=list_date;c<=err && confronta_stringhe(cmd2,CMD2[c])!=0;c++);
        if(c>list_rit_tot) c=err;//gestisco il limite superiore dei comandi, se c supera il limite allora va ad errore
        else
            printf("Stampo elenco %s\n",cmd2);
        return c;
    }else if(strcmp(cmd1,CMD1[1])==0) {
        scanf("%s",cmd2);
        for (c = file; c <= err && confronta_stringhe(cmd2,CMD2[c])!=0; c++);
        if(c>video) c=err;
        else
            printf("Stampa su %s...\n",cmd2);
        return c;
    }else if(strcmp(cmd1,CMD1[2])==0){
        scanf("%s",cmd2);
        for(c=data;c<=err && confronta_stringhe(cmd2,CMD2[c])!=0;c++);
        if(c>dest) c=err;
        else
            printf("Ordinamento per %s...",cmd2);
        return c;
    }else if(strcmp(cmd1,CMD1[3])==0){
        return ricerca;
    } else if(strcmp(cmd1,CMD1[4])==0){
        return carica;
    }else if(strcmp(cmd1,CMD1[5])==0){
        return fine;
    }else{
        return err;
    }
}
int selezionaDati(ORDINAMENTI_S *ordinamenti){
    char info1[l_max_nomi],info2[l_max_nomi];
    int found=0;
    if(cmd>=data && cmd<=dest) {
        stato=cmd;
        if(!ordinamenti[cmd].fatto){
            ordinaRef_wrapper(ordinamenti[cmd].ord);
            ordinamenti[cmd].fatto=1;
        }
        printf("completato\n");
    } else
    switch (cmd){
        case video:
            printlog(ordinamenti[stato].ord,info1);
            printf("completata\n");
            break;
        case file:
            printf("Inserisci nome file txt da creare:");
            scanf("%s.txt",info1);
            printlog(ordinamenti[stato].ord,info1);
            printf("completata\n");
            break;
        case ricerca:
            printf("Inserisci nome citta' da ricercare:");
            scanf("%s", info1);
            if(ordinamenti[part].fatto==1)
                found=ricercaDicotomicastampa(ordinamenti[part].ord,info1);
            else
                found=ricercaLinearestampa(ordinamenti[stato].ord,info1);
            if(found==-1)
                fprintf(stderr,"Errore, ricerca senza successo, stazione di partenza non trovata.\n");
            break;
        case list_date:
            printf("Inserisci date <data1> <data2>");
            scanf("%s %s",info1,info2);
            date(ordinamenti[data].ord,info1,info2);
            break;
        case list_part:
            printf("Inserisci <partenza>");
            scanf("%s",info1);
            partenza(ordinamenti[part].ord,info1);
            break;
        case list_capol:
            printf("Inserisci <capolinea>");
            scanf("%s",info1);
            capolinea(ordinamenti[data].ord,info1);
            break;
        case list_rit:
            printf("Inserisci date <data1> <data2>");
            scanf("%s %s",info1,info2);
            ritardo(ordinamenti[part].ord,info1,info2);
            break;
        case list_rit_tot:
            printf("Inserisci <codice>");
            scanf("%s",info1);
            ritardotot(ordinamenti[part].ord,info1);
            break;
        case carica:
            //le operazioni di carica vengono fatte nel main per non passare nella funzione l'indirizzo di tratta
            break;
        case fine:
            return 1;
        default:
            fprintf(stderr,"Errore comando inserito\n");
    }
return 0;
}

int main(){
    CORSE_S *tratta=NULL;
    ORDINAMENTI_S *ordinamenti=NULL;
    //sono contenuti tutti gli ordinamenti richiesti
    char info[l_max_nomi];
    int continua=0;
    if((tratta=caricafile(tratta,inizio_file,0))==NULL){
        return 1;
    }
    ordinamenti=creaOrdinamenti(tratta,ordinamenti,0);
     while(!continua){
        cmd=leggicomando();
        continua=selezionaDati(ordinamenti);
        if(cmd==carica){
            printf("Inserisci <nome_file.txt>");
            scanf("%s",info);
            tratta=caricafile(tratta,info,1);
            ordinamenti=creaOrdinamenti(tratta,ordinamenti,1);
        }
    }
    return 0;
}
