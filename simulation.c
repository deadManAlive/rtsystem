//simulation mechanics
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "simulation.h"

#define PSG_DST_COEFF 7     //probability param.

//train constructor and seat avalaibility gen. takes train name, price multiplier, and capacity.
Train* trainFactory(const char* tname, float pmult, int hh, int mm, int ss, index ncar, index seatx, index seaty){
    //train constructor
    Train* new_train = (Train*)calloc(1, sizeof(*new_train) + sizeof(int[ncar][seatx][seaty]));//intialize new_train, that points to a Train, to a pointer to allocated memory with size of new_train plus size of flexible array member seat_avl_arr, that casted to a Train pointer.

    strcpy(new_train->train_name, tname);
    new_train->price_multiplier = pmult;
    new_train->train_length = ncar;
    new_train->psg_seat_x   = seatx;
    new_train->psg_seat_y   = seaty;

    new_train->hour         = hh;
    new_train->minute       = mm;
    new_train->second       = ss;

    //seat avalaibility generator

    srand(time(NULL));

    bool(*savlptr)[new_train->train_length][new_train->psg_seat_x][new_train->psg_seat_y] = (bool(*)[new_train->train_length][new_train->psg_seat_x][new_train->psg_seat_y]) new_train->seat_avl_arr;

    //intialize an 3d array of pointer that points to seat_avl_arr member, that casted to a 3d array of pointer of type bool.

    for(index incar = 0; incar < new_train->train_length; incar++){
        for(index iseatx = 0; iseatx < new_train->psg_seat_x; iseatx++){
            for(index iseaty = 0; iseaty < new_train->psg_seat_y; iseaty++){
                (*savlptr)[incar][iseatx][iseaty] = (rand() < RAND_MAX/PSG_DST_COEFF); //random boolean generator, probability set by RAND_MAX divisor
            }
        }
    }

    return new_train;
}

void trainRecycle(Train* old_train){
    free(old_train); //
}

void trainMapper(const Train* a_train){
    bool(*sseek)[a_train->train_length][a_train->psg_seat_x][a_train->psg_seat_y] = (bool(*)[a_train->train_length][a_train->psg_seat_x][a_train->psg_seat_y]) a_train->seat_avl_arr;
    
    for(index incar = 0; incar < a_train->train_length; incar++){
        printf("Gerbong %d\n", incar + 1);
        printf("\t");
        for(int i = 0; i < a_train->psg_seat_y; i++){
            if(i == a_train->psg_seat_y/2){
                printf("\t");
            }
            printf(" %c  ", 'A' + i);
        }
        printf("\n\n");
        for(index iseatx = 0; iseatx < a_train->psg_seat_x; iseatx++){
            for(index iseaty = 0; iseaty < a_train->psg_seat_y; iseaty++){
                if(a_train->psg_seat_y%2 == 0){
                    if(iseaty == a_train->psg_seat_y/2){
                        printf("\t");
                    }
                }
                printf("[%c] ", (*sseek)[incar][iseatx][iseaty]?'x':' ');
            }
            printf("\n");
        }
        printf("\n");
    }
}

int freeSeatCalc(const Train* a_train){
    int free_seat_sum = 0;

    bool(*savlptr)[a_train->train_length][a_train->psg_seat_x][a_train->psg_seat_y] = (bool(*)[a_train->train_length][a_train->psg_seat_x][a_train->psg_seat_y]) a_train->seat_avl_arr;


    for(index incar = 0; incar < a_train->train_length; incar++){
        for(index iseatx = 0; iseatx < a_train->psg_seat_x; iseatx++){
            for(index iseaty = 0; iseaty < a_train->psg_seat_y; iseaty++){
                if((*savlptr)[incar][iseatx][iseaty] == FALSE){
                    free_seat_sum++;
                }
            }
        }
    }

    return free_seat_sum;
}

bool seatSetter(Train* a_train, index ncar, index seatx, index seaty){ //if seat occupied, return FALSE. else set seat TRUE and return TRUE.
    bool(*savlptr)[a_train->train_length][a_train->psg_seat_x][a_train->psg_seat_y] = (bool(*)[a_train->train_length][a_train->psg_seat_x][a_train->psg_seat_y]) a_train->seat_avl_arr;

    if((*savlptr)[ncar][seatx][seaty] == TRUE){
        return FALSE;
    }
    else{
        (*savlptr)[ncar][seatx][seaty] = TRUE;
        return TRUE;
    }
}

int randTimeGen(int tmin, int tmax){
    return (tmin + rand() / (RAND_MAX / (tmax - tmin + 1) + 1));
    //better than modulus according to http://c-faq.com/lib/randrange.html
}