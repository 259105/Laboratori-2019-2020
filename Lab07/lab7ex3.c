//
// Created by s259105 on 30/11/2019.
//
// IMPORTANTE.. PER CAPIRE AL MEGLIO IL PROGRAMMA BISOGNA AVERE ANCHE LO SCHEMA DELLE TABELLE
//controllare il fatto dei codici dei personaggi
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_CHAR 50
#define MAX_EQUIP 8

typedef struct {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;
typedef struct inv_s inv_t,*linkInv;
struct inv_s {
    char *nome;
    char *tipo;
    stat_t stat;
};
typedef struct{
    inv_t* vettInv;
    int nInv;
    int maxInv;
}tabInv_t;
typedef struct{
    int inUso;
    int nEquip;
    linkInv vettEq[MAX_EQUIP];
}tabEquip_t;
typedef struct {
    char codice[7];
    char *nome;
    char *classe;
    tabEquip_t* equip;
    stat_t stat,statEff;
}pg_t;
typedef struct nodoPg_t *link;
struct nodoPg_t{
    pg_t val;
    link next;
};
typedef struct {
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

typedef enum{
    add=1,del,equip,stat,term,err
}cmd_e;

void minuscolo(char *s){
    int i=0;
    for(i=0;i<(int)strlen(s);i++)
        s[i]=tolower(s[i]);
}
int confronta_stringhe(char *s1,char *s2){
    char stri1[MAX_CHAR],stri2[MAX_CHAR];//Creo questo 2 nuove stringhe per non modificare i caratteri nella struct
    strcpy(stri1,s1);
    strcpy(stri2,s2);
    minuscolo(stri1);
    minuscolo(stri2);
    return strcmp(stri1,stri2);
}
//Funzioni creazione EQUIPAGGIAMENTO
tabEquip_t * creaListaEquip(){
    tabEquip_t *temp;
    temp=(tabEquip_t*)malloc(sizeof(tabEquip_t));
    if(temp==NULL){
        fprintf(stderr,"Errore di allocazione.");
        exit(2);
    }
    temp->inUso=0;
    temp->nEquip=0;
    for(int i=0;i<MAX_EQUIP;i++){
        temp->vettEq[i]=NULL;
    }
    return temp;
}
//Funzioni creazione PG
link creaNodo(pg_t val,link succ){
    link n;
    n=malloc(sizeof (*n));
    if(n==NULL){
        fprintf(stderr,"Errore di allocazione.");
        exit(2);
    }
    n->val=val;
    n->next=succ;
    return n;
}
tabPg_t* creaListaPg(){
    tabPg_t *temp;
    temp=(tabPg_t*)malloc(sizeof(tabPg_t));
    if(temp==NULL){
        fprintf(stderr,"Errore di allocazione.");
        exit(2);
    }
    temp->headPg=NULL;
    temp->tailPg=NULL;
    temp->nPg=0;
    return temp;
}
void inserisciCodaPg(tabPg_t *tab,pg_t pg){
    link n;
    n=creaNodo(pg,NULL);
    if(tab->tailPg==NULL && tab->headPg==NULL) {// caso iniziale tutti e 2 puntano a null
        tab->headPg=tab->tailPg=n;
        return;
    }
    tab->tailPg->next=n;// imposto che il successico della coda deve essere il nuovo nodo
    tab->tailPg=tab->tailPg->next; //aggiorno coda
}
tabPg_t* inputPg(){
    // se s==0 => si stà caricando il file di personaggi
    // se s==1 => si vuole aggiungere un nuovo personaggio
    tabPg_t *tab=creaListaPg();
    pg_t pg;
    FILE *fp;
    char nome[MAX_CHAR],classe[MAX_CHAR];
    if((fp=fopen("pg.txt","r"))==NULL){
        fprintf(stderr,"Errore file non trovato.");
        exit(1);
    }
    while ((fscanf(fp,"%*s%s%s%d%d%d%d%d%d",nome,classe,&pg.stat.hp,&pg.stat.mp,&pg.stat.atk,&pg.stat.def,&pg.stat.mag,&pg.stat.spr))>0){ //chiedere se posso fare così
        tab->nPg++;
        pg.statEff.hp=pg.stat.hp;
        pg.statEff.mp=pg.stat.mp;
        pg.statEff.atk=pg.stat.atk;
        pg.statEff.def=pg.stat.def;
        pg.statEff.mag=pg.stat.mag;
        pg.statEff.spr=pg.stat.spr;
        sprintf(pg.codice,"PG%.4d",tab->nPg);
        pg.equip=creaListaEquip();
        pg.nome=strdup(nome);
        pg.classe=strdup(classe);
        if(pg.nome==NULL ||pg.classe==NULL){
            fprintf(stderr,"Errore di allocazione.");
            exit(2);
        }
        inserisciCodaPg(tab,pg);
    }
    fclose(fp);
    return tab;
}
void addPg(tabPg_t *tab){
    pg_t pg;
    char nome[MAX_CHAR],classe[MAX_CHAR];
    printf("Inserire <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>:\n");
    fscanf(stdin,"%s%s%d%d%d%d%d%d",nome,classe,&pg.stat.hp,&pg.stat.mp,&pg.stat.atk,&pg.stat.def,&pg.stat.mag,&pg.stat.spr); //chiedere se posso fare così
    tab->nPg++;
    sprintf(pg.codice,"PG%.4d",tab->nPg);// %.4 significa che devono esserci 4 cifre e senno mette gli zeri
    pg.nome=strdup(nome);
    pg.classe=strdup(classe);
    if(pg.nome==NULL ||pg.classe==NULL){
        fprintf(stderr,"Errore di allocazione.");
        exit(2);
    }
    inserisciCodaPg(tab,pg);
    printf("Personaggio %s aggiunto correttamente con codice %s.\n",nome,pg.codice);
}
//Funzioni creazione INVENTARIO
tabInv_t* creaListaInv(int O){
    tabInv_t *temp;
    temp=(tabInv_t*)malloc(sizeof(tabInv_t));
    if(temp==NULL){
        fprintf(stderr,"Errore di allocazione.");
        exit(2);
    }
    temp->vettInv=(inv_t*)malloc(O*sizeof(inv_t));
    if(temp->vettInv==NULL){
        fprintf(stderr,"Errore di allocazione.");
        exit(2);
    }
    temp->nInv=O;
    temp->maxInv=0;
    return temp;
}
tabInv_t* inputInv(){
    tabInv_t *tab;
    int O;
    FILE *fp=fopen("inventario.txt","r");
    char nome[MAX_CHAR],tipo[MAX_CHAR];

    if(fp==NULL){
        fprintf(stderr,"Errore file non trovato.");
        exit(1);
    }
    fscanf(fp,"%d",&O);
    tab=creaListaInv(O);
    for(int i=0;i<O;i++){
        fscanf(fp,"%s%s%d%d%d%d%d%d",nome,tipo,&tab->vettInv[i].stat.hp,&tab->vettInv[i].stat.mp,&tab->vettInv[i].stat.atk,&tab->vettInv[i].stat.def,&tab->vettInv[i].stat.mag,&tab->vettInv[i].stat.spr);
        tab->vettInv[i].nome=strdup(nome);
        tab->vettInv[i].tipo=strdup(tipo);
        if(tab->vettInv[i].nome==NULL ||tab->vettInv[i].tipo==NULL){
            fprintf(stderr,"Errore di allocazione.");
            exit(2);
        }
    }
    return tab;
}
//Funzioni FREE
void freeNodo(link nodo){
    free(nodo->val.nome);
    free(nodo->val.classe);
    free(nodo);
}
void freeLista(tabPg_t *tab){
    link n;
    for (n=tab->headPg;n!=NULL;n=n->next){
        freeNodo(n);
    }
    free(tab);
}
void freeElementoV(inv_t elemento){
    free(elemento.nome);
    free(elemento.tipo);
}
void freeInventario(tabInv_t *tab){
    for(int i=0;i<tab->nInv;i++){
        freeElementoV(tab->vettInv[i]);
    }
    free(tab->vettInv);
    free(tab);
}
//Funzioni STAMPA
void stampaSPg(link nodo){//Stampa singolo PG
    printf("%s %s %s;\n",nodo->val.codice,nodo->val.nome,nodo->val.classe);
}
void stampaPgR(link nodo){
    if(nodo==NULL) return;
    stampaSPg(nodo);
    stampaPgR(nodo->next);
    return;
}
void stampaPg(tabPg_t *tab){
    stampaPgR(tab->headPg);
    printf("\n");
}
int controllaOgg(link nodo,linkInv ogg){
    //controllo che l'oggetto scelto non sia gia nel'equipaggiamento
    int i;
    for(i=0;i<MAX_EQUIP;i++)
        if(nodo->val.equip->vettEq[i]==ogg)
            return 1;
    return 0;
}//non è una funzione di stampa ma mi serve qua
void stampaInv(tabInv_t *tab,link nodo){
    for(int i=0;i<tab->nInv;i++)
        if(!controllaOgg(nodo,&(tab->vettInv[i])))//se controllo oggetto mi da esito negativo, significa che l'oggetto non è nell'equipaggiamento
            printf("%s %s %d %d %d %d %d %d;\n",tab->vettInv[i].nome,tab->vettInv[i].tipo,tab->vettInv[i].stat.hp,tab->vettInv[i].stat.mp,tab->vettInv[i].stat.atk,tab->vettInv[i].stat.def,tab->vettInv[i].stat.mag,tab->vettInv[i].stat.spr);
    printf("\n");
}
void stampaEquip(link nodo){
    int i=0;
    if (nodo->val.equip->nEquip==0){
        printf("Il %s %s %s non ha equipaggiato niente:\n",nodo->val.codice,nodo->val.nome,nodo->val.classe);
        return;
    }
    printf("Il %s %s %s ha equipaggiato:\n",nodo->val.codice,nodo->val.nome,nodo->val.classe);
    for(i=0;i<MAX_EQUIP;i++)
        if(nodo->val.equip->vettEq[i]!=NULL)// perche ci possono essere dei "buchi" nell'inventario
            printf("%s %s\n",nodo->val.equip->vettEq[i]->nome,nodo->val.equip->vettEq[i]->tipo);
    printf("\n");
}
void stampaStat(link nodo){
    printf("HP: %d;\n"
           "MP: %d;\n"
           "Attacco: %d;\n"
           "Difesa: %d;\n"
           "MAG: %d;\n"
           "SPR: %d.\n",
           nodo->val.statEff.hp,nodo->val.statEff.mp,nodo->val.statEff.atk,nodo->val.statEff.def,nodo->val.statEff.mag,nodo->val.statEff.spr);
}
//Funzioni VARIE
link ricercaNodoR(char *key,link nodo){
    if(nodo==NULL) return NULL;
    if(confronta_stringhe(nodo->val.codice,key)==0)
        return nodo;
    return ricercaNodoR(key,nodo->next);
}
void eliminaNodo(tabPg_t *tab){
    char key[7];
    link n,p;
    do{
        printf("Inserire codice del personaggio da eliminare tra: (0 per tornare al menu')\n");
        stampaPg(tab),
        fscanf(stdin,"%s",key);
        if (strcmp(key,"0")==0) return;

        for(p=NULL,n=tab->headPg;n!=NULL && confronta_stringhe(key,n->val.codice)!=0;p=n,n=n->next);//ricerco elemento e il precedente
        if(n==NULL) printf("Errore il codice inserito non presente.\n");
    }while(n==NULL);
    if (p==NULL){
        if(tab->headPg==tab->tailPg) tab->headPg=tab->tailPg=NULL; //nel caso ci fosse un solo elemento e lo si vuole eliminare
        tab->headPg=n->next;//nel caso fosse il primo elemento allora cambio l'head
    }
    else{
        if(n==tab->tailPg){
            tab->tailPg=p; //nel caso che vuoi eliminare l'ultimo elemento aggirono la tail
            tab->nPg--;
        }
        p->next=n->next;//by-pass collego il precendete a n con il successivo
    }
    printf("Eliminazione di %s completata.\n",n->val.nome);
    freeNodo(n); //elimino il nodo
}
linkInv ricercaInv(char* key,tabInv_t *tabInv){
    int i;
    for(i=0;i<tabInv->nInv && confronta_stringhe(key,tabInv->vettInv[i].nome)!=0;i++);
    if(i==tabInv->nInv) return NULL;  //significa che non è stato trovato nulla
    return &(tabInv->vettInv[i]);
}
//Funzioni STATISTICA
void aggiornaStat(link nodo){// da chiedere come va fatto (io modifico le statistiche del pg)
    int i;
    //riparto sempre dalle statistiche del giocatore e poi gli aggiungo l'equipaggiamento
    nodo->val.statEff.hp=nodo->val.stat.hp;
    nodo->val.statEff.mp=nodo->val.stat.mp;
    nodo->val.statEff.atk=nodo->val.stat.atk;
    nodo->val.statEff.def=nodo->val.stat.def;
    nodo->val.statEff.mag=nodo->val.stat.mag;
    nodo->val.statEff.spr=nodo->val.stat.spr;
    for(i=0;i<MAX_EQUIP;i++){
        if(nodo->val.equip->vettEq[i]!=NULL){
            if((nodo->val.statEff.hp+=nodo->val.equip->vettEq[i]->stat.hp)<=1)
                nodo->val.statEff.hp=1;
            if((nodo->val.statEff.mp+=nodo->val.equip->vettEq[i]->stat.mp)<=1)
                nodo->val.statEff.mp=1;
            if((nodo->val.statEff.atk+=nodo->val.equip->vettEq[i]->stat.atk)<=1)
                nodo->val.statEff.atk=1;
            if((nodo->val.statEff.def+=nodo->val.equip->vettEq[i]->stat.def)<=1)
                nodo->val.statEff.def=1;
            if((nodo->val.statEff.mag+=nodo->val.equip->vettEq[i]->stat.mag)<=1)
                nodo->val.statEff.mag=1;
            if((nodo->val.statEff.spr+=nodo->val.equip->vettEq[i]->stat.spr)<=1)
                nodo->val.statEff.spr=1;
        }
    }
}
void statistiche(tabPg_t *tabPg){
    char key[MAX_CHAR];
    link nodo;
    do{
        printf("Inserisci codice personaggio tra:\n");
        stampaPg(tabPg);
        scanf("%s",key);
        nodo=ricercaNodoR(key,tabPg->headPg);
        if(nodo==NULL)
            printf("Errore codice inserito non corretto.\n");
    }while (nodo==NULL);
    stampaStat(nodo);
}
//Funzioni EQUIPAGGIAMENTO
void aggiungiEquip(link nodo,tabInv_t *tabInv){
    char key[MAX_CHAR];
    linkInv oggetto;
    if(nodo->val.equip->nEquip==MAX_EQUIP){
        printf("Il PG ha già l'equipaggiamento pieno.\n");
        return;
    }
    do{
        printf("Inserisci nome dell'oggetto d'aggiungere tra:\n");
        stampaInv(tabInv,nodo);
        scanf("%s",key);
        oggetto=ricercaInv(key,tabInv);
        if(controllaOgg(nodo,oggetto)){
            printf("Errore l'oggetto che vuoi inserire e' gia nell'equipaggiamento.\n");
            return;
        }
        if(oggetto==NULL)
            fprintf(stderr,"Errore oggetto non trovato nell'inventario.\n");
    }while(oggetto==NULL);

    for(int i=0;i<MAX_EQUIP;i++){//mette l'oggetto nel primo posto vuoto che trova
        if(nodo->val.equip->vettEq[i]==NULL){
            nodo->val.equip->vettEq[i]=oggetto;
            nodo->val.equip->nEquip++;
            printf("Oggetto %s aggiunto correttamente a %s.\n",nodo->val.equip->vettEq[i]->nome,nodo->val.nome);
            break;
        }
    }
    //fare il controllo degli oggetti ripetuti
}
void rimuoviEquip(link nodo){
    char key[MAX_CHAR];
    int i,trovato=0;
    if(nodo->val.equip->nEquip==0){
        printf("Il PG ha gia' l'equipaggiamento vuoto.\n");
        return;
    }
    do{
        stampaEquip(nodo);
        printf("Inserisci nome dell'oggetto da rimuovere:\n");
        scanf("%s",key);
        for(i=0;i<MAX_EQUIP;i++){
            if(nodo->val.equip->vettEq[i]!=NULL && confronta_stringhe(key,nodo->val.equip->vettEq[i]->nome)==0){
                nodo->val.equip->vettEq[i]=NULL;
                nodo->val.equip->nEquip--;
                printf("Oggetto rimosso correttamente a %s.\n",nodo->val.nome);
                trovato=1;
                break;
            }
        }
        if(!trovato) fprintf(stderr,"Errore oggetto non trovato nell'equipaggiamento.\n");
    }while(trovato==0);
}
void equipaggiamento(tabPg_t *tabPg,tabInv_t *tabInv){
    char key[7];
    int cmd,term=0;
    link nodo;
    do{
        printf("Inserisci codice personaggio da equipaggiare:\n");
        stampaPg(tabPg);
        scanf("%s",key);
        nodo=ricercaNodoR(key,tabPg->headPg);
        if(nodo==NULL)
            printf("Errore codice inserito non corretto.\n");
    }while (nodo==NULL);
    stampaEquip(nodo);
    do{
        printf("Inserisci comando:\n"
               "1 - Aggiungere oggetto all'equipaggiamento;\n"
               "2 - Rimuovere oggetto dall'equipaggiamento;\n"
               "3 - Visualizza Equipaggiamento corrente;\n"
               "4 - Stampa statistiche personaggio;\n"
               "5 - Torna al menu principale.\n");
        scanf("%d",&cmd);
        switch(cmd){
            case 1: aggiungiEquip(nodo,tabInv); aggiornaStat(nodo); break;
            case 2: rimuoviEquip(nodo); aggiornaStat(nodo); break;
            case 3: stampaEquip(nodo); break;
            case 4: stampaStat(nodo); break;
            case 5: term=1; break;
            default: fprintf(stderr,"Errore comando inserito errato.\n"); break;
        }
    }while (!term);
}

cmd_e leggiComando(){
    int cmd;
    printf("Inserire comando(1..5):\n"
           "1 - Aggiungi nuovo personaggio;\n"
           "2 - Elimina personaggio;\n"
           "3 - Aggiungi/rimuovi oggetto dall'equipaggiamento di un personaggio;\n"
           "4 - Visualizza statistiche di un personaggio;\n"
           "5 - Fine.\n");
    scanf("%d",&cmd);
    return cmd;
}

int main(void){
    tabPg_t *tabPg;
    tabInv_t *tabInv;
    cmd_e cmd;
    int continua=1;

    tabPg=inputPg();
    tabInv=inputInv();

    while (continua){
        cmd=leggiComando();
        switch(cmd){
            case add: addPg(tabPg); break;
            case del: eliminaNodo(tabPg); break;
            case equip: equipaggiamento(tabPg,tabInv); break;
            case stat: statistiche(tabPg); break;
            case term: continua=0; break;
            default: fprintf(stderr,"Errore comando inserito errato.\n"); break;
        }
    }

    freeLista(tabPg);
    freeInventario(tabInv);
}
