//
// Created by s259105 on 30/10/2019.
//

#include <stdio.h>

int gcd(int a,int b){
    // questa funzione funziona solo se a>b..
    //se a,b sono pari allora => 2*gdc(a/2,b/2)
    //se a è dispari e b è pari => gdc(a,b/2)
    //se a e b sono dispari => gdc((a-b)/2,b)
    //condizione di terminazione: se a=0 => ritorno b
    // (b è il massimo comun divisore)
    int tmp;//mi serve per invertirli in caso se b>a

    if(a==0) //condizione di terminazione
        return b;

    if (b>a){//inversione
        tmp=a;
        a=b;
        b=tmp;
    }
    if(a%2==0 && b%2==0){
        return 2*gcd(a/2,b/2);
    }else if(a%2==1 && b%2==0){
        return gcd(a,b/2);
    }else if(a%2==1 && b%2==1){
        return gcd((a-b)/2,b);
    }else{
        return gcd(a/2,b);
    }
}


int main(){
    int x1,x2;
    printf("Inserisci i numeri di cui vuoi sapere il Massimo Comun Divisore: <x1> <x2>\n");
    scanf("%d %d",&x1,&x2);
    printf("%d",gcd(x1,x2));
    return 0;
}
