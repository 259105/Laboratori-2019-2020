//
// Created by s259105 on 25/11/2019.
//

#include <stdlib.h>
#include <stdio.h>
#define N 4 //indica il numero di pietre diverse
//se si modifica N, va modificato in teoria tutto il programma perche ci sono gli enum
#define nome_file "pietre_e2.txt"

typedef enum{
    zaffiro=0,smeraldo,rubino,topazio
}Nome;
typedef struct{
    int n,val,usate,consecutive;
    //n dice quante pietre sono rimaste;
}_pietre;
//Var globali
int l_part=0,max_rip=0,val_max=0,l_max=0;

int min(int n,int n1){
    if(n<n1) return n;
    return n1;
}
_pietre* allocapietre(_pietre *pietre) {
    pietre=malloc(N* sizeof(_pietre));
    return pietre;
}
int conversionefileprof(int i){
    int k=0;
    if(i==zaffiro) k=0; else if(i==rubino) k=1; else if(i==topazio) k=2; else if(i==smeraldo) k=3;
    return k;
}
int inputpietre(_pietre *pietre,int **m,int j) {
    int lunghezza=0,i,k;
    for(i=0;i<N;i++){
        k=conversionefileprof(i);
        pietre[i].n=m[j][k];
        pietre[i].val=m[j][k+4];
        pietre[i].consecutive=pietre[i].usate=0;
        lunghezza+=pietre[i].n;
    }
    max_rip=m[j][8];
    return lunghezza;
}
int **leggifile(int *r){
    int **m;
    FILE *fp;
    fp=fopen(nome_file,"r");
    fscanf(fp,"%d",r);
    m=malloc(*r* sizeof(int*));
    for(int i=0;i<*r;i++){
        m[i]=malloc(9* sizeof(int));
        for(int j=0;j<9;j++)
            fscanf(fp,"%d",&m[i][j]);
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
void stampadati(_pietre *pietre,int l){
    printf("zaffiro = %d [%d],",pietre[zaffiro].n,pietre[zaffiro].val);
    printf(" rubino = %d [%d],",pietre[rubino].n,pietre[rubino].val);
    printf(" topazio = %d [%d],",pietre[topazio].n,pietre[topazio].val);
    printf(" smeraldo = %d [%d],",pietre[smeraldo].n,pietre[smeraldo].val);
    printf(" TOT = %d {max_rip = %d}\n",l,max_rip);
}
void stampa(int *sol) {
    int i=0;
    printf("Soluzione ottima di valore %d usando %d gemma/e\nComposizione collana: ",val_max,l_max);
    for(i=0;i<l_max;i++){
        if(sol[i]==zaffiro) printf("z");
        if(sol[i]==smeraldo) printf("s");
        if(sol[i]==rubino) printf("r");
        if(sol[i]==topazio) printf("t");
    }
    printf("\n");
}
int contr_preced(int p,int i, _pietre *pietre){
    if(p==-1){//per la prima ricorsione
        /* Non posso iniziare con il zaffiro perchè violerebbe la condizione
         * if(i==zaffiro && pietre[zaffiro].n>0)
            return 1;
         */
        if(i==smeraldo && pietre[smeraldo].n>0){
            pietre[topazio].consecutive=pietre[zaffiro].consecutive=pietre[rubino].consecutive=0;
            pietre[smeraldo].consecutive++;
            return 1;
        }
        if(i==rubino && pietre[rubino].n>0){
            pietre[zaffiro].consecutive=pietre[smeraldo].consecutive=pietre[topazio].consecutive=0;
            pietre[rubino].consecutive++;
            return 1;
        }
        if(i==topazio && pietre[topazio].n>0){
            pietre[zaffiro].consecutive=pietre[rubino].consecutive=pietre[smeraldo].consecutive=0;
            pietre[topazio].consecutive++;
            return 1;
        }
    }

    if(p==zaffiro || p==topazio){
        if(i==zaffiro && pietre[zaffiro].n>0 && pietre[zaffiro].usate<pietre[smeraldo].usate && (pietre[zaffiro].consecutive)<max_rip){
            //l'ultima condizione dice che i zaffiri usati devono essere minori dei smeraldi usati
            pietre[zaffiro].consecutive++;
            pietre[rubino].consecutive=pietre[smeraldo].consecutive=pietre[topazio].consecutive=0;
            return 1;
        }
        if(i==rubino && pietre[rubino].n>0 && (pietre[rubino].consecutive)<max_rip){
            pietre[zaffiro].consecutive=pietre[smeraldo].consecutive=pietre[topazio].consecutive=0;
            pietre[rubino].consecutive++;
            return 1;
        }
    }
    if(p==smeraldo || p==rubino ){
        if(i==smeraldo && pietre[smeraldo].n>0 && (pietre[smeraldo].consecutive)<max_rip){
            pietre[smeraldo].consecutive++;
            pietre[topazio].consecutive=pietre[zaffiro].consecutive=pietre[rubino].consecutive=0;
            return 1;
        }
        if(i==topazio && pietre[topazio].n>0 && (pietre[topazio].consecutive)<max_rip){
            pietre[zaffiro].consecutive=pietre[rubino].consecutive=pietre[smeraldo].consecutive=0;
            pietre[topazio].consecutive++;
            return 1;
        }
    }
    return 0;//se non ha trovato nessun successivo
}
int calcola_val(int *sol,int pos,_pietre *pietre){
    int tot=0;
    for(int i=0;i<pos;i++){
        tot+=pietre[sol[i]].val;
    }
    return tot;
}
int *aggiornamassimo(int *b_sol,int *sol,int pos){
    for(int i=0;i<pos;i++){
        b_sol[i]=sol[i];
    }
    return b_sol;
}
int *disp(int *b_sol,int *sol,int pos, _pietre *pietre,int p){
    //p indica la scelta precedente
    int i=0;
    int t_succ=0;//non ho trovato un successore
    int val_curr=calcola_val(sol,pos,pietre);// valore corrente della collana
    if(pos==l_part){
            if(val_curr>val_max){
                val_max=val_curr;
                l_max=pos;
                aggiornamassimo(b_sol,sol,pos);
            }
            return b_sol;
    }
    for(i=0;i<N;i++) {
            if (contr_preced(p, i,pietre)){
                t_succ=1;
                sol[pos] = i;
                pietre[i].n--; pietre[i].usate++;
                //usando questo mark pietre, non è più diposizioni, ma permutazioni con ripetizione
                disp(b_sol,sol, pos+1, pietre, i);
                pietre[i].n++; pietre[i].usate--;
            }
    }
    if(!t_succ){ //condizione di terminazione anticipata
        if(val_curr>val_max){
            val_max=val_curr;
            l_max=pos;
            aggiornamassimo(b_sol,sol,pos);
        }
        return b_sol;
    }
    return b_sol;
}

int main(void){
    int *sol,**m;
    int *b_sol;
    int r,j,minimoTR,minimoSZ,l;
    _pietre *pietre=NULL;

    pietre=allocapietre(pietre);
    m=leggifile(&r);

    for(j=0;j<r;j++){
        printf("TEST #%d\n",j+1);
        l=inputpietre(pietre,m,j);
        stampadati(pietre,l);
        minimoSZ=min(pietre[zaffiro].n,pietre[smeraldo].n);
        minimoTR=min(pietre[rubino].n,pietre[topazio].n);
        l_part=pietre[smeraldo].n+minimoSZ+minimoTR*2+1; //calcolo della lunghezza di partenza per la ricerca
        //che sarebbe la lunghezza massima ottenibile con quelle pietre
        if(l_part>l) l_part=l;
        sol=malloc(l_part* sizeof(int));
        b_sol=malloc(l_part* sizeof(int));

        disp(b_sol,sol,0,pietre,-1);
        stampa(b_sol);

        val_max=0,l_max=0;
        free(sol);
        free(b_sol);
    }
    free(pietre);
    freematr(m,r);
   return 0;
}
