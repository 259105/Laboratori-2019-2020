//
// Created by s259105 on 13/02/2020.
//

#ifndef COORD_H
#define COORD_H

typedef struct {
    int x,y;
}Coord;

int COORDdist(Coord p1,Coord p2);
Coord COORDcreate(int x,int y);

#endif //COORD_H
