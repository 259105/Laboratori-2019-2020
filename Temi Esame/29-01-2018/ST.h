#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED

typedef struct symbtab *ST;

ST  	STinit(int maxN) ;
void    STfree(ST st) ;
int		STcount(ST st) ;
int  	STinsert(ST st,char *val) ;
int     STsearch(ST st,char *val) ;
char*   STsearchByindex(ST st,int index);

#endif
