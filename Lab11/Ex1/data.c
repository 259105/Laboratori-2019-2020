//
// Created by s259105 on 19/01/2020.
//
#include "data.h"
#include <stdio.h>
int DATAcmp(data d1,data d2){
    long data1,data2;
    data1=d1.giorno+31*d1.mese+372*d1.anno;
    data2=d2.giorno+31*d2.mese+372*d2.anno;
    return (int)(data1-data2);
}
/*int ORAcmp(data d1,data d2){
    long data1,data2;
    data1=d1.minuti+60*d1.ore;
    data2=d2.minuti+60*d2.ore;
    return (int)(data1-data2);
}*/
data dataSetNULL(){
    data d;
    d.minuti=0;
    d.giorno=0;
    d.anno=0;
    d.ore=0;
    d.mese=0;
    return d;
}
data DATAinit(char *d,char *o){
    data data;
    sscanf(d,"%d/%d/%d",&data.anno,&data.mese,&data.giorno);
    sscanf(o,"%d:%d",&data.ore,&data.minuti);
    return data;
}
