#ifndef SIMULATION_H
#define SIMULATION_H

#include "generics.h"
//simulation thing

typedef struct{
    //train identity
    char train_name[20];
    float price_multiplier;

    //train dimension
    index train_length; //number of cars
    index psg_seat_x;   //dimension of...
    index psg_seat_y;   //passengers seating

    //seat avalaibility array, hardest part
    bool seat_avl_arr[];
} Train;

Train* trainFactory(const char* tname, float pmult, index ncar, index seatx, index seaty); //train cstr. + seat avalaibility generator
void trainRecycle(Train* old_train); //garbage stuff(?)
void trainMapper(const Train* a_train); //view seats
int freeSeatCalc(const Train* a_train); //return free seats
bool seatSetter(Train* a_train, index ncar, index seatx, index seaty); //seat setter

#endif