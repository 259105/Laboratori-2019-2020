//
// Created by s259105 on 30/10/2019.
//

#include <stdio.h>
#define N 50

int inside_majority(int *a,int l,int r){
    int ml,mr,i;
    int contml=0,contmr=0;
    /*
     * Servono per contare le occorrenze dei numeri maggioritari
     * trovati nel sottovettore di sinistra e destra.
     */
    int q=(l+r)/2;
    int n=(r-l)+1;

    if(n==1)
        return a[l];

    ml=inside_majority(a,l,q);
    mr=inside_majority(a,q+1,r);
    //Se l'elemento maggioritario del sub-vettore di sx e dx sono uguali allora quell'elemento è maggioritario
    //anche per il vettore.
    if(ml==mr && ml!=-1)
        return ml;
    for(i=l;i<=r;i++){
        if(ml!=-1 && ml==a[i])
            contml++;
        if(mr!=-1 && mr==a[i])
            contmr++;
    }
    //Se le occorrenze dei numeri maggioritari sono maggiori stretto a n/2 allora quello è un numero maggioritario.
    if(contml>contmr && contml>n/2)
        return ml;
    if(contmr>contml && contmr>n/2)
        return mr;
    return -1;
}

int majority(int *a,int n){
    return inside_majority(a,0,n-1);
}

int main(){
    int a[N],n=-1,i=0,j;
    int m;
    /*
     * il programma acquisisce il vettore un numero alla volta e termina l'inserimento
     * con il numero -1.
    */
    do{
        if(n!=-1){
            a[i]=n;
            i++;
        }
        printf("Inserisci numero nel vettore (-1 per terminare inserimento):");
        scanf("%d",&n);
    }while(n!=-1);

    printf("\nIl vettore inserito e': ");
    //stampo vettore inserito e la sua lunghezza
    for(j=0;j<i;j++)
        printf("%d ",a[j]);
    printf("\nN e' %d",i);
    m=majority(a,i);
    if(m==-1)
        printf("\nNon c'e' un elemento maggioritario.");
    else
        printf("\nL'elemento maggioritario e' %d",m);
    return 0;
}
