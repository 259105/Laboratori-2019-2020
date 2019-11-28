//
// Created by s259105 on 02/11/2019.
//

/*
 * Per dare un utilità alla funzione richiesta dall'esercizio, in questo programma viene usata
 * per ricercare e stampare tutte le parole ,appartenenti all'insieme identificato
 * dall'espressione regolare, contenute in un testo proveniente da testo.txt.
 * Il testo è tale che contiene solo caratteri alfabetici, la lunghezza di riga massima è 120.
 * Il tutto è fatto attraverso un ciclo while che prende una riga alla volta del testo, e poi qua
 * viene fatta la ricerca dell'occorrenza.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXRIGA 125
#define MAXREGEXP 30

int l_regexp;//

int reglen(char *s){
    /*
     * Serve per contare le lettere effettive del occorenza da ricercare
     */
    int cont=0;
    while (*s!='\0'){

        if(*s=='['){
            while(*s++!=']');
        }else if(strncmp(s,"\\a",2)==0 || strncmp(s,"\\A",2)==0){
            s+=2;
        }else{//qua è racchiuso il caso del '.'
            s++;
        }
        cont++;
    }
    return cont;
}

char *cercaRegexp(char *src, char *regexp){
    /*
     * Per cercare l'espressione regolare nella stringa src, creo un puntatore a src "s", a regexp "r".
     * Da qui parte un ciclo while che termina quando il puntatore s punta o a \0 o a \n, dentro al ciclo
     * viene scansionata la prima parola attraverso una sscanf, viene presa la lunghezza e viene puntata da p.
     * Con il puntatore alla parola viene fatto il confronto con l'espressione regolare.
     *
     * Il confronto viene fatto incrementando contemporaneamente sia p che r se *p e *r sono uguali, se invece
     * siamo nel caso in cui r punta a un carattere non alfabetico si rientra nei casi di:
     *
     * []= qua si suddivide in altri 2 sottocasi, ovvero con ^ o senza.
     * Se c'è ^ allora se si viene a riscontrare che la lettera successica a ^ è uguale a la lettera puntata da p
     * il ciclo do-while viene interrotto e saltata la parola con la successiva. Il ciclo while funziona in modo tale
     * che se una lettera è gia stata trovata non si controllano le altre, questo grazie al flag trovato e al successivo
     * break.
     *
     */
    char parola[MAXREGEXP];
    char *s=src,*r=regexp,*p;
    int cont=0,padding;
    int trovato;
    int l_parola;

    while (*s!='\0' && *s!='\n'){
        r=regexp;
        cont=0;
        sscanf(s,"%s%n",parola,&padding);
        l_parola=(int)strlen(parola);
        p=parola;
        if(l_parola==l_regexp)//si controlla la parola solo se è uguale alla parola dell'espressione regolare
        while(*p!='\0'){
            if(!isalpha(*r)){
                if(*r=='.'){
                    r++;p++;cont++;
                }else if(*(r++)=='['){
                    trovato=0;//inizializzo il flag
                    do{
                        if(*r=='^'){
                            if(*(++r)==*p){//incremento r per andare all'elemento successivo a ^
                                p++;
                                break;//esco dal ciclo perche ho trovato l'elemento che non deve esserci
                            }else if(!trovato){
                                p++;
                                cont++;
                                trovato=1;
                            }
                        }else if(*r==*p && !trovato){
                            trovato=1;
                            p++;
                            cont++;
                        }
                    }while (*r++!=']');
                    if(trovato==0)
                        break;
                }else if(*r=='a' && islower(*p)) {
                    p++;r++;
                    cont++;
                }else if(*r=='A' && isupper(*p)){
                    p++;r++;
                    cont++;
                }
            }else if(*p==*r){
                cont++;
                r++; p++;
            }else{
                break;
            }
            if(l_regexp==cont){
                /*
                 * Grazie al padding che mi dice la lunchezza da s fino a fine parola, compresi gli spazi
                 * posso calcolarmi di quanto far avanzare s in modo tale da restituirmi s che punta all'inizio
                 * della parola senza gli spazi d'avanti.
                 */
                return s+(padding-l_parola);
            }
        }
        s+=l_parola+(padding-l_parola);
    }
    return NULL;
}

char* stampastringa(char *parola,char *regexp){
    int size_parola=reglen(regexp),i;
    for(i=0;i<size_parola;i++,parola++)
        printf("%c",*parola);
    printf("\t");
    return parola;
}


int main(void){
    char riga[MAXRIGA+1];
    char regexp[MAXREGEXP+1];
    char *segno;
    int i=1;
    FILE *fp;

    if((fp=fopen("testo.txt","r"))==NULL){
        fprintf(stderr,"Errore apertura file");
        return 1;
    }
    printf("Instruzioni di uso delle espressioni regolari:\n"
           ">>) . trova un singolo carattere\n"
           ">>) [] trova un singolo carattere contenuto nelle parentesi\n"
           ">>) [^ ] trova ogni singolo carattere non contenuto nelle parentesi\n"
           ">>) \\a trova un carattere minuscolo\n"
           ">>) \\A trova un carattere maiuscolo\n");
    printf("Inserisci espressione regolare che indetifica un'insieme di stringhe:\n");
    scanf("%s",regexp);
    l_regexp=reglen(regexp);
    while(fgets(riga,MAXRIGA,fp)!=NULL){
        segno=riga;
        printf("\nRiga %d: ",i++);
        while((segno=cercaRegexp(segno,regexp))!=NULL){
            segno=stampastringa(segno,regexp); //restituisce il puntatore esattamente dopo la parola stampata
        }
    }
    return 0;
}
