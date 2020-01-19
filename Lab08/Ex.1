#include <stdio.h>
#include <stdlib.h>
#define file "att.txt"

typedef struct{
    int s,f;
}att;

int maxdur=0,l_b_sol=0;
int leggifile(att **v){
    FILE *fp;
    att *temp;
    int n,i;
    fp=fopen(file,"r");
    if(fp==NULL)
        exit(1);
    fscanf(fp,"%d",&n);
    temp=malloc(n*sizeof(att));
    for(i=0;i<n;i++){
        fscanf(fp,"%d%d",&temp[i].s,&temp[i].f);
    }
    *v=temp;
    fclose(fp);
    return n;
}
int check(att *sol,int pos,att v){
    int i;
    for(i=0;i<pos;i++){
        //se uno dei 2 estremi dell'attività che voglio aggiungere
        // è dentro un'attività gia in sol, allora  incompatibile
        if(sol[i].s<=v.s && v.s<sol[i].f)
            return 0;
        if (sol[i].s<v.f && v.f<=sol[i].f)
            return 0;
    }
    return 1;
    //controllo compatibilità

}
int dur(att *sol,int pos){
    int dur=0;
    for(int i=0;i<pos;i++)
        dur+=sol[i].f-sol[i].s;
    return dur;
}
void aggMax(att *b_sol,att *sol,int pos){
    for(int i=0;i<pos;i++){
        b_sol[i].s=sol[i].s;
        b_sol[i].f=sol[i].f;
    }
    l_b_sol=pos;
}
void attSelR(int pos,att *v,att *sol,att *b_sol,int k,int start){
    int i,durata;
    for(i=start;i<k;i++){
        if(check(sol,pos,v[i])){
            sol[pos]=v[i];
            attSelR(pos+1,v,sol,b_sol,k,i+1);
        }
    }
    durata=dur(sol,pos);
    if(durata>=maxdur){
        maxdur=durata;
        aggMax(b_sol,sol,pos);
    }
    return;
}
void stampasol(att *sol){
    for(int i=0;i<l_b_sol;i++)
        printf("(%d,%d), ",sol[i].s,sol[i].f);
    printf("\n");
}
void attSel(int N, att *v){
    //uso powerset con cominazioni ripetute
    att *sol,*b_sol;
    sol=malloc(N*sizeof(att));
    b_sol=malloc(N*sizeof(att));
    attSelR(0,v,sol,b_sol,N,0);
    printf("Uno dei sottoinsiemi di S di attivita' compatibili che massimizza la somma delle durate e':\n");
    stampasol(b_sol);
    printf("per una somma delle durate pari a %d",maxdur);
    free(sol);free(b_sol);
}

int main(void){
    att *v;
    int n;

    n=leggifile(&v);
    printf("HAI INSERITO:\n%d\n",n);
    for(int i=0;i<n;i++){
        printf("%d %d\n", v[i].s,v[i].f);
    }
    attSel(n,v);
    free(v);
    return 0;
}
