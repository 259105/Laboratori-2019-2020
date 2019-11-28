//
// Created by s259105 on 25/11/2019.
//

#include <stdlib.h>
#include <stdio.h>
#define N 4 //indica il numero di pietre diverse
//se si modifica N, va modificato in teoria tutto il programma perche ci sono gli enum
#define nome_file "pietre.txt"

typedef enum{
    zaffiro=0,smeraldo,rubino,topazio
}Nome;
typedef struct{
    unsigned int n;
    //n dice quante pietre sono rimaste, Val indica il valore della pietra. Tot dice quante pietre avevo inizialmente
}_pietre;

int min(unsigned int n, unsigned int n1){
    if(n<n1) return n;
    return n1;
}

_pietre* allocapietre(_pietre *pietre) {
    pietre=malloc(N* sizeof(_pietre));
    return pietre;
}
int inputpietre(_pietre *pietre,int **m,int j) {
    int lunghezza=0,i;
    /*printf("Inserisci numero di <zaffiri> <smeraldi> <rubini> <topazi>:");
    scanf("%u%u%u%u",&pietre[zaffiro].n,&pietre[smeraldo].n,&pietre[rubino].n,&pietre[topazio].n);
    */
    for(i=0;i<N;i++){
        pietre[i].n=m[j][i];
        lunghezza+=pietre[i].n;
    }
    return lunghezza;
}
int **leggifile(int *r){
    int **m;
    FILE *fp;
    fp=fopen(nome_file,"r");
    fscanf(fp,"%d",r);
    m=malloc(*r* sizeof(int*));
    for(int i=0;i<*r;i++){
        m[i]=malloc(4* sizeof(int));
        fscanf(fp,"%d%d%d%d",&m[i][zaffiro],&m[i][rubino],&m[i][topazio],&m[i][smeraldo]);
    }

    fclose(fp);
    return m;
}
void freematr(int **m,int r){
    for(int i=0;i<r;i++){
        free(m[i]);
    }
    free(m);
}
void stampa_prova(int *sol,int pos) {
    int i=0;
    printf("\n-");
    for(i=0;i<pos;i++){
        if(sol[i]==zaffiro) printf("z-");
        if(sol[i]==smeraldo) printf("s-");
        if(sol[i]==rubino) printf("r-");
        if(sol[i]==topazio) printf("t-");
    }
    printf("\nLunghezza massima: %d",pos);
}
int contr_preced(int p,int i, _pietre *pietre,int start){
    if(p==-1){//per la prima ricorsione
        if((i)==zaffiro && pietre[zaffiro].n>0  && start==zaffiro)
            return zaffiro;
        if((i)==smeraldo && pietre[smeraldo].n>0 && start==smeraldo)
            return smeraldo;
    }

    if(p==zaffiro || p==topazio){
        if(i==zaffiro && pietre[zaffiro].n>0)
            return zaffiro;
        if(i==rubino && pietre[rubino].n>0)
            return zaffiro;
    }
    if(p==smeraldo || p==rubino){
        if(i==smeraldo && pietre[smeraldo].n>0)
            return smeraldo;
        if(i==topazio && pietre[topazio].n>0)
            return topazio;
    }
    return -1;//se non ha trovato nessun successivo

}
int disp(int *sol,int pos, _pietre *pietre,int l,int p,int start){
    //p indica la scelta precedente
    int i=0;
    if(pos==l){
        stampa_prova(sol,pos);
        return 1;
    }
    for(i=0;i<N;i++) {
        if (contr_preced(p, i,pietre,start)>=0){
            sol[pos] = i;
            pietre[i].n--;
            if(disp(sol, pos+1, pietre,l,i,start))
                return 1;
            pietre[i].n++;
        }
    }
    return 0;
}

int main(void){
    int *sol,**m;
    _pietre *pietre=NULL;
    int i,l,l_sol,r,minimo;
    pietre=allocapietre(pietre);
    m=leggifile(&r);
    for(int j=0;j<r;j++){
        l=inputpietre(pietre,m,j);
        sol=malloc(l* sizeof(int));
        for(i=0;i<l;i++)
            sol[i]=-1;//significa che in quella posizione della collana non c'è nulla
        minimo=min(pietre[rubino].n,pietre[topazio].n);
        l_sol=pietre[zaffiro].n+pietre[smeraldo].n+minimo*2+1; //calcolo della lunghezza massima possibile
        if(minimo==(int)pietre[rubino].n) disp(sol,0,pietre,l_sol,-1,smeraldo);
        else disp(sol,0,pietre,l_sol,-1,zaffiro);
        free(sol);
    }
    free(pietre);
    freematr(m,r);
    return 0;
}


