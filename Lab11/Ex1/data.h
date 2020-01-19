//
// Created by s259105 on 19/01/2020.
//

#ifndef ALG_PROG_DATA_H
#define ALG_PROG_DATA_H
typedef struct{
    int anno,mese,giorno,ore,minuti;
}data;

int DATAcmp(data d1,data d2);
//int ORAcmp(data d1,data d2);
data dataSetNULL();
data DATAinit(char *data,char *ora);

#endif //DATA_H
