//
// Created by s259105 on 13/02/2020.
//
#include "COORD.h"
#include <math.h>

int COORDdist(Coord p1,Coord p2){
    return (int)(sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)));
}

Coord COORDcreate(int x,int y){
    Coord p;
    p.x=x; p.y=y;
    return p;
}
