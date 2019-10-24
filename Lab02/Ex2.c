//
// Created by s259105 on 18/10/2019.
//

#include <stdio.h>
#include <string.h>

int controlloEndian(){
    int n=1;
    unsigned char *p;
    p=(unsigned char *)&n;
    return p[0];//accedo al primo byte dell intero
}

void stampaCodifica (void *p,int size,int bigEndian){
    int i,n,j,k,esp,zeri,stampati,spazio=0,cont=0,start=0;
    char tipo[15];
    unsigned char *c;
    c=(unsigned char *)p;
    switch(size){
        case 4: spazio=9;
                strcpy(tipo,"Float     ");
            break;
        case 8: spazio=12;
                strcpy(tipo,"Double    ");
            break;
        case 12: spazio=16;
                strcpy(tipo,"Long Double");
            break;
    }
    printf("\n%s\t",tipo);
    if(size==12){ //faccio questa operazione perchè ci sono 2byte di padding iniziali
        start=2;
        size-=2;
    }
    for(bigEndian?(i=start):(i=size-1);bigEndian?i<size:i>=0;bigEndian?i++:i--){
        n=(unsigned int)c[i];
        for(j=2,esp=1;j*2<=n;j*=2,esp++);
        n?(zeri=8-esp-1):(zeri=8);
        for(k=zeri;k>0;k--) {
            printf("0");
            cont++;
            if(cont==spazio || cont==1)
                printf("\t");
        }
        for(stampati=0;stampati<=esp;stampati++){
            if(n-j>=0){
                n-=j;
                printf("1");
                cont++;
                if(cont==spazio || cont==1)
                    printf("\t");
            }else if(zeri!=8) {
                printf("0");
                cont++;
                if(cont==spazio || cont==1)
                    printf("\t");
            }
            j/=2;
        }
    }
}

int main(){
    float af;
    double ad;
    long double ald;
    int bigEndian=0;//se è 0 allora è Little Endian

    if(controlloEndian()==0)
        bigEndian=1;// allora è Big Indian
    printf("Il tuo calcolatore utilizza la codifica %s\n",  bigEndian?"BigEndian":"LittleEndian");
    printf("La dimenzione del float e': %dbyte ovvero %dbit\n"
           "La dimenzione del double e': %dbyte ovvero %dbit\n"
           "La dimenzione del longdouble e': %dbyte ovvero %dbit\n"
           ,sizeof(af),sizeof(af)*8,sizeof(ad), sizeof(ad)*8, sizeof(ald), sizeof(ald)*8);
    printf("Inserisci numero con virgola:");
    scanf("%lf",&ad);
    printf("\nTipo Dato\tSegno\tEsponente\tMantissa");

    af=(float)ad; ald=(long double)ad;
    stampaCodifica((void *) &af, sizeof(af),bigEndian);
    stampaCodifica((void *) &ad, sizeof(ad),bigEndian);
    stampaCodifica((void *) &ald, sizeof(ald),bigEndian);

    return 0;
}
