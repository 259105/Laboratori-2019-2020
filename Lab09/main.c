//
// Created by s259105 on 11/12/2019.
//

#include <stdio.h>
#include <stdlib.h>

void displaySol(int *opt, int *val, int n) {
    int i, *sol;
    sol = calloc((n + 1), sizeof(int));
    sol[1] = 1;
    i = n;
    while (i >= 2) {
        //printf("i=%d\n", i);
        if (opt[i] == opt[i - 1]) {
            sol[i] = 0;
            i--;
        } else if (opt[i] == opt[i - 2] + val[i]) {
            sol[i] = 1;
            sol[i - 1] = 0;
            i -= 2;
        }
    }
    for (i = 1; i <= n; i++)
        if (sol[i])
            printf("%d ", val[i]);
    printf("\n");
}

void solveDP(void){
    int i, *opt;
    int n=6;
    int val[7]={0,10,20,5,15,55,30};
    opt = calloc((n+1),sizeof(int));
    opt[1] = val[1];
    for (i=2; i<=n; i++) {
        if (opt[i-1] > opt[i-2]+val[i])
            opt[i] = opt[i-1];
        else
            opt[i] = opt[i-2] + val[i];
    }
    printf("Dynamic programming solution: ");
    printf("maximum population covered %d\n", opt[n]);
    displaySol(opt, val, n);
}

int main(void){
    solveDP();
}
