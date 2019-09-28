//
// Created by 259105 on 27/09/2019.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 20

int conta(char S[20], int n);
int conta(char S[20], int n){
    int i,j,f=0,count=0,l;
    l=strlen(S);
    for(j=0;j<=(l-n);j++){
        f=0;
        for(i=j;i<j+n;i++){
            if(S[i]=='a' || S[i]=='e'|| S[i]=='i' || S[i]=='o'|| S[i]=='u' || S[i]=='A' || S[i]=='E'|| S[i]=='I' || S[i]=='O'|| S[i]=='U'){
                f++;
            }
        }
        if(f==2){
            count++;
        }
    }
 return count;
}


int main(){
    FILE *fp;
    int m,n,tot=0,sub;
    char S[N+1],F[N+1];

    printf("Inserisci il nome del file da aprire (20 char max):\n");
    scanf("%s",F);
    if(strlen(F)>20){
       fprintf(stderr,"Errore rinomina il file (20 char max)");
        return 1;
    }


    if((fp=fopen(F,"r"))==NULL){
        fprintf(stderr,"Errore apertura file.");
        return 1;
    }

    printf("Inserisci  un intero n che rappresenta la lunghezza delle sottostringhe da cercare.\n");
    scanf("%d",&n);
    fscanf(fp,"%d",&m);
    while(!feof(fp)){
        fscanf(fp,"%s",S);
        sub=conta(S,n);
        tot=tot+sub;
    }
    printf("%d",tot);
    return 0;
}
