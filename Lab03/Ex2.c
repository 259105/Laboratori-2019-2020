//
// Created by s259105 on 18/10/2019.
//

#include <stdio.h>
#include <string.h>
#define pritf__mingw_printf

int controlloEndian(){
    /*
     * Per capire se il calcolatore usa la convezione Big Endian oppure Little Endian, inizializzo una
     * variabile int a 1, in questo modo viene salvato un cella di memoria di 4byte, in cui sarà presente
     * qualcosa del genere:
     * 00000000 00000000 00000000 00000001
     * adesso dichiaro un puntatore a unsigned char p e lo facco puntare all'indirizzo di n covertendolo
     * con un cast ad unsigned char. Così facendo il puntatore mi punta al primo byte dei 4 byte del ormai
     * non più int.
     * Se nel primo byte è presente 1 ==> si usa la convenzine Little Endian
     * Sennò si usa la convenzione Big Endian
     */
    int n=1;
    unsigned char *p;
    p=(unsigned char *)&n;
    return p[0];//accedo al primo byte dell intero
}

void stampaCodifica (void *p,int size,int bigEndian){
    /*
     * La variabile spazio serve per capire dove stampare lo spazio tra esponente e mantissa.
     * per fare questo serve un contatore che mi conta tutti i caratteri stampati.
     *
     * Per stampare la codifica, attraverso un generatore online so che un float=1 è rappresentato nel seguente modo:
     * 00111111100000000000000000000000
     * Avendo il puntatore void al numero
     * lo converto in un unsigned char cosi da spacchettarlo in 4byte separati, per poi prendere
     * singolo byte e convertirlo in unsigned int (n):
     * 00111111 = 63 (int)
     * 10000000 = 128 (int)
     * 00000000 = 0 (int)
     * 00000000 = 0 (int)
     * Adesso converto gli int in binario.
     * Analagamente funziona per Double e Long Double(quest'ultimo con qualche accorgimento)
     */
    int i,n,j,k,esp,zeri,stampati,spazio=0,cont=0,start=0;
    char tipo[15]; // perche voglio che mi stampi la tipologia di formato prima della codifica
    unsigned char *c;
    c=(unsigned char *)p;
    switch(size){ // In base ai byte capisco se p che tipologia di dato è.
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
    if(size==12){ //faccio questa operazione perchè ci sono 2byte di padding iniziali nei long double
        start=2;  // faccio cominciare il for 2 byte dopo oppure se è little endian 2 posizioni dietro.
        size-=2;
    }
    //uso espressioni condizionali per fare la distinzione tra big endian e little endian.
    for(bigEndian?(i=start):(i=size-1);bigEndian?i<size:i>=0;bigEndian?i++:i--){
        n=(unsigned int)c[i];
        for(j=2,esp=1;j*2<=n;j*=2,esp++);
        n?(zeri=8-esp-1):(zeri=8);
        for(k=zeri;k>0;k--) { //serve per stampare tutti gli zeri che sono presenti prima del numero binario
            printf("0");
            cont++;
            if(cont==spazio || cont==1)//controllo se devo stampare o no lo spazio, dopo il primo carattere
                printf("\t");           // stampo uno spazio per separare il segno.
        }
        //codifica Binario
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
    __mingw_scanf("%Lf",&ald);
    printf("\nTipo Dato\tSegno\tEsponente\tMantissa");

    af=(float)ald; ad=(double)ald;
    stampaCodifica((void *) &af, sizeof(af),bigEndian);
    stampaCodifica((void *) &ad, sizeof(ad),bigEndian);
    stampaCodifica((void *) &ald, sizeof(ald),bigEndian);

    return 0;
}
