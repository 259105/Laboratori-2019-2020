//
// Created by s259105 on 14/02/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include "Coppia.h"
#include "ST.h"
#include <ctype.h>

int isperfect(int **MP,int **MA,Coppia *C,int N){
    int **MC,tc=0,ts=0,no=0; //ts:=trovata preferenza soluzione tc:=trovata preferenza alternativa
    MC=malloc(sizeof(int*)*N);
    for(int i=0;i<N;i++) MC[i]=malloc(sizeof(int)*N);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            MC[i][j]=0;

    for(int i=0;i<N;i++)
        for(int x=0;x<N;x++)
            for(int y=0;y<N;y++){
                if(x==C[i].p && y!=C[i].a){
                    ts=0;tc=0;no=0;
                    for(int m=0;m<N;m++){//su tutte le preferenze
                        if(MP[x][m]==C[i].a) ts=1;
                        if(MP[x][m]==y) tc=1;
                        if(tc==1 && ts==0) {MC[x][y]++;break;}
                        if(ts==1 && tc==0) break;
                    }
                }
                if(x!=C[i].p && y==C[i].a){
                    ts=0;tc=0;
                    for(int m=0;m<N;m++){//su tutte le preferenze
                        if(MA[y][m]==C[i].p) ts=1;
                        if(MA[y][m]==x) tc=1;
                        if(tc==1 && ts==0) {MC[x][y]++;break;}
                        if(ts==1 && tc==0) break;
                    }
                }
            }
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(MC[i][j]==2) no=1;
    for(int i=0;i<N;i++)
        free(MC[i]);
    free(MC);
    if(no) return 0;
    return 1;
}

int perfectmathR(int **MP,int **MA,int *RP,int *RA,int pos,Coppia *sol,int N){
    if(pos==N){
        if(isperfect(MP,MA,sol,N))
            return 1;
        return 0;
    }
    for(int i=0;i<N;i++)//Persona i-esima
        for(int j=0;j<N;j++)//Azienda j-esima
            if(RP[i]!=0 && RA[j]!=0){ //se non sono gia stati scelti
                RP[i]=0; RA[j]=0; //li scelgo
                sol[pos]=COPPIAcreate(i,j);
                if(perfectmathR(MP,MA,RP,RA,pos+1,sol,N))
                    return 1;
                RP[i]=1; RA[j]=1; //backtrack
            }
    return 0;
}

Coppia* perfectmath(int** MP,int** MA,int N){
    Coppia *sol=malloc(sizeof(Coppia)*N);
    int *RP,*RA;
    RP=malloc(sizeof(int)*N);RA=malloc(sizeof(int)*N);
    for(int i=0;i<N;i++){RP[i]=RA[i]=1;}
    if(perfectmathR(MP,MA,RP,RA,0,sol,N)) return sol;
    return NULL;
}

int main(int argc,char** argv){
    if(argc!=5) exit(1);
    char persona[11],azienda[11];
    int N,P,A,**MP,**MA;
    FILE *fPP,*fPA,*fC/*,*fa,*fp*/;
    Coppia *C;
    ST tabP,tabA;

    N=atoi(argv[1]);
    tabP=STinit(N); tabA=STinit(N);
    /*fa=fopen("aziende.txt","r");
    fp=fopen("persone.txt","r");*/
    fPP=fopen(argv[2],"r");
    fPA=fopen(argv[3],"r");
    fC=fopen(argv[4],"r");
    C=malloc(sizeof(Coppia)*N);
    MP=malloc(sizeof(int*)*N);
    MA=malloc(sizeof(int*)*N);
    for(int i=0;i<N;i++){
        MP[i]=malloc(sizeof(int)*N);
        MA[i]=malloc(sizeof(int)*N);
    }
    /*for(int i=0;i<N;i++){
        fscanf(fa,"%s",azienda);
        fscanf(fp,"%s",persona);
        STinsert(tabA,azienda);
        STinsert(tabP,persona);
    }*/
    for(int i=0;i<N;i++){
        fscanf(fPP,"%s",persona);
        P=STinsert(tabP,persona);
        for(int j=0;j<N;j++){
            fscanf(fPP,"%s",azienda);
            A=STsearch(tabA,azienda);
            if(A<0) A=STinsert(tabA,azienda);
            MP[P][j]=A;
        }
    }
    for(int i=0;i<N;i++){
        fscanf(fPA,"%s",azienda);
        A=STsearch(tabA,azienda);
        for(int j=0;j<N;j++){
            fscanf(fPA,"%s",persona);
            P=STsearch(tabP,persona);
            MA[A][j]=P;
        }
    }
    for(int i=0;i<N;i++){
        fscanf(fC,"%s %s",persona,azienda);
        P=STsearch(tabP,persona);
        A=STsearch(tabA,azienda);
        C[i]=COPPIAcreate(P,A);
    }
    fclose(fPP); fclose(fPA); fclose(fC);
    /*for(int i=0;i<N;i++)
        for(int j=0;j<N;j++){
            fscanf(fa,"%d",&MA[i][j]);
            fscanf(fp,"%d",&MP[i][j]);
        }*/
    if(isperfect(MP,MA,C,N)) printf("E' perfetto\n");
    else printf("Non e' perfetto\n");

    C=perfectmath(MP,MA,N);
    if(C==NULL) printf("Non esiste un math perfetto\n");
    else
        for(int i=0;i<N;i++)
            printf("%s %s\n",STsearchByindex(tabP,C[i].p),STsearchByindex(tabA,C[i].a));

}
