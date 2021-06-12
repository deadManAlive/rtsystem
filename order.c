//ordering mechanics

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "order.h"

//ordering vars
const char* day_name[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

//station list by distance from Gambir, pretty scalable in linear branchless route model.
const distance_kmeter distance_list[] = {
    0,      //0. Gambir
    218,    //1. Cirebon
    442,    //2. Semarang
    742,    //3. Surabaya
    870     //4. Malang
};

void orderDateInput(Order* dateless_order){
    //function's vars
    int dt, mt, yr;         //date vars
    bool date_menu_loop = TRUE; //make loopable

    //GET current time
    time_t t = time(NULL);
    struct tm current_time = *localtime(&t); //months, days in week, days in year start at 0, years start at 1900

    while(date_menu_loop){
        printf("Masukkan tanggal keberangkatan (dd m yyyy): ");
        scanf("%d%d%d", &dt, &mt, &yr);

        //date checking alg.
        //1. check if date values are valid
        //non zero check
        if(dt < 1 || mt < 1 || yr < 1){
            printf(INPUT_ERROR); printf("\n");
            continue;
        } //or just absolutize these values...?
        
        bool is_leap_year = (yr % 400 == 0)? TRUE : FALSE; //initialize leap year boole by checking if it's centurial leap year
        if(!is_leap_year){ //if it's not centurial leap year...
            if(yr % 100 != 0){ //AND not centurial year...
                if(yr % 4 == 0){ //AND divisible by 4...
                    is_leap_year = TRUE; //it is a leap year
                }
            }
        }

        if(mt > 12){ //check if month is valid
            printf(INPUT_ERROR); printf("\n");
            continue;
        }

        switch(mt){ //check number of day in month for each
            case 1: //jan
            case 3: //mar
            case 5: //may
            case 7: //jul
            case 8: //aug
            case 10://oct
            case 12://dec
                if(dt > 31){
                    printf(INPUT_ERROR); printf("\n");
                    continue;
                }
                break;
            case 2: //feb
                if(dt > 28 + (int)is_leap_year){ //is_leap_year is a bool that IS also an uint
                    printf(INPUT_ERROR); printf("\n");
                    continue;
                }
                break;
            default: //else...
                if(dt > 30){
                    printf(INPUT_ERROR); printf("\n");
                    continue;
                } 
                
        }

        //2. check if date is not in the past

        if(yr < current_time.tm_year + 1900){
            printf(TIME_ERROR); printf("\n");
            continue;
        }
        else if(yr == current_time.tm_year + 1900){
            if(mt < current_time.tm_mon + 1){
                printf(TIME_ERROR); printf("\n");
                continue;
            }
            else if(mt == current_time.tm_mon + 1){
                if(dt < current_time.tm_mday){
                    printf(TIME_ERROR); printf("\n");
                    continue;
                }
            }
        }

        //end of checking stuff

        //SET departure date time struct, for stuff
        struct tm departure_time = {.tm_mday = dt, .tm_mon = mt - 1, .tm_year = yr - 1900, .tm_isdst = -1};
        mktime(&departure_time);

        printf("Tanggal yg dipilih: %s, %d-%d-%d.\nMasukkan 1 untuk lanjut, 0 untuk mengulang: ", day_name[departure_time.tm_wday], departure_time.tm_mday, departure_time.tm_mon + 1, departure_time.tm_year + 1900);
        
        //loopback
        getchar(); //clears buffer from '\n'(?)
        if(getchar() == '1'){
            //set to new order container
            dateless_order->date   = dt;
            dateless_order->month  = mt;
            dateless_order->year   = yr;

            //end this while loop
            date_menu_loop = FALSE;
        }//user doesn't really need to input 0...?
    }
}

void station_list(char* list_head){
        printf("Pilihan stasiun %s: \n", list_head);
        printf("\t1.Jakarta\n");
        printf("\t2.Cirebon\n");
        printf("\t3.Semarang\n");
        printf("\t4.Surabaya\n");
        printf("\t5.Malang\n");
        printf("Pilihan: ");
    }

void orderRouteInput(Order* routeless_order){
    //route func. vars
    bool route_menu_loop = TRUE;
    index org; //origin station option container
    index dst; //dest. station opt. ctr.

    //menu texts
    station_list("asal");
}

Order newOrder(Order* order_list_arr, index size){
    Order new_order_ctr; //new order container

    system(CLEAR_SCREEN);

    printf("Pemesanan\n");
    orderDateInput(&new_order_ctr);     //call date setter func.
    orderRouteInput(&new_order_ctr);    //call route setter func.
}