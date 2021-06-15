//ordering mechanics

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "order.h"
#include "simulation.h"

#define BASE_PRICE 420   //Rp. / km
#define TRAIN_AVG_SPEED 82  //kph
#define ETA_DEV_PCT 0.16 //probability/coefficient of route time calculation deviation


//ordering vars
const char* day_name[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

//station list by distance from Gambir
const distance_kmeter distance_list[] = {
    0,      //0. Gambir
    218,    //1. Cirebon
    442,    //2. Semarang
    742,    //3. Surabaya
    870     //4. Malang
};

const char *station_list[] = {
    "Gambir",
    "Cirebon",
    "Semarang",
    "Surabaya",
    "Malang"
};

void orderDateInput(Order* dateless_order){
    //function's vars
    int dt, mt, yr;         //date vars
    bool date_menu_loop = TRUE; //make loopable

    //GET current time
    time_t now = time(NULL);
    struct tm current_time = *localtime(&now); //months, days in week, days in year start at 0, years start at 1900

    system(CLEAR_SCREEN);

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

        //if two digit number entered as year
        if(yr < 100){
            yr += 2000;
        }
        
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
            strcpy(dateless_order->day, day_name[departure_time.tm_wday]);

            //end this while loop
            date_menu_loop = FALSE;
        }//user doesn't really need to input 0...?
    }
}

void station_list_and_ask(const char* list_head){ //unnecessary, but helps scalability
        printf("Pilihan stasiun %s: \n", list_head);
        for(index i = 0; i < (sizeof(distance_list)/sizeof(int)); i++){
            printf("\t%u.%s\n", i + 1, station_list[i]);
        }
        /*
        printf("\t1.Jakarta\n");
        printf("\t2.Cirebon\n");
        printf("\t3.Semarang\n");
        printf("\t4.Surabaya\n");
        printf("\t5.Malang\n");
        */
        printf("Pilihan: ");
    }

void orderRouteInput(Order* routeless_order){
    //route func. vars
    bool route_menu_loop = TRUE;
    index org; //origin station option container
    index dst; //dest. station opt. ctr.

    system(CLEAR_SCREEN);

    //menu loop
    while(route_menu_loop){
        //origin
        station_list_and_ask("asal");
        scanf("%u", &org);
        //dest.
        station_list_and_ask("tujuan");
        scanf("%u", &dst);

        //index adjustment
        --org;
        --dst;

        //check if input is valid
        if(org > sizeof(distance_list) || dst > sizeof(distance_list)){
            printf(INPUT_ERROR);
            printf("\n");
            continue;
        }
        else if(org == dst){
            printf(STAT_ERROR);
            printf("\n");
            continue;
        }
        else{
            routeless_order->origin_idx = org;
            routeless_order->destination_idx = dst;
        }

        printf("Pesanan:\n");
        printf("\tTanggal:\t");
        printf("%s, %d-%d-%d.\n", routeless_order->day, routeless_order->date, routeless_order->month, routeless_order->year);
        printf("\tStasiun asal:\t%s.\n", station_list[routeless_order->origin_idx]);
        printf("\tStasiun tujuan:\t%s.\n", station_list[routeless_order->destination_idx]);
        printf("\nMasukkan 1 untuk lajut, 0 untuk mengulangi: ");

        getchar(); //clears buffer from '\n'(?)
        if(getchar() == '1'){
            //end this while loop
            route_menu_loop = FALSE;
        }//user doesn't really need to input 0 again
    }
}

void trainSelector(Order* seatless_order, Train* tgarage[], int tgarage_size){
    //train select vars.
    bool tselect_menu_loop = TRUE;
    index tptr; //opt. container

    //GET current time
    time_t now = time(NULL);
    struct tm current_time = *localtime(&now);

    system(CLEAR_SCREEN);

    while(tselect_menu_loop){
        printf("Pilihan kereta\n");
        printf("Untuk %s, %d-%d-%d dari %s menuju %s:\n\n", seatless_order->day, seatless_order->date, seatless_order->month, seatless_order->year, station_list[seatless_order->origin_idx], station_list[seatless_order->destination_idx]);
        for(index i = 0; i < tgarage_size; i++){
            //ETA analysis
            //generate time struct for departure
            struct tm ttime = {
                .tm_year    = seatless_order->year - 1900,
                .tm_mon     = seatless_order->month - 1,
                .tm_mday    = seatless_order->date,
                .tm_hour    = tgarage[i]->hour,
                .tm_min     = tgarage[i]->minute,
                .tm_sec     = tgarage[i]->second
            };
            time_t dtime =  mktime(&ttime); //departure time value

            //ETA calculation

            int route_distance = abs(distance_list[seatless_order->destination_idx] - distance_list[seatless_order->origin_idx]);
            int route_est_time_seconds = 3600*(float)route_distance/TRAIN_AVG_SPEED;

            //add deviation to route_est_time_seconds

            route_est_time_seconds = randTimeGen((1.0 - ETA_DEV_PCT/2) * route_est_time_seconds, (1.0 + ETA_DEV_PCT/2) * route_est_time_seconds);

            //ETA
            time_t eta_second = dtime + (time_t)route_est_time_seconds;
            struct tm eta_time = *localtime(&eta_second);
            
            //view train spesc.
            printf("Kereta #%d:\n", i + 1);
            printf("\t[%s]\n", tgarage[i]->train_name);
            printf("\tKeberangkatan\t: %02d:%02d:%02d (%-7s,%d-%d-%d)\n", tgarage[i]->hour, tgarage[i]->minute, tgarage[i]->second, seatless_order->day, seatless_order->date, seatless_order->month, seatless_order->year);
            printf("\tETA\t\t: %02d:%02d:%02d (%-7s,%d-%d-%d)\n", eta_time.tm_hour, eta_time.tm_min, eta_time.tm_sec, day_name[eta_time.tm_wday], eta_time.tm_mday, eta_time.tm_mon + 1, eta_time.tm_year + 1900);
            printf("\tKursi tersedia\t: %d\n", freeSeatCalc(tgarage[i]));
            printf("\tOngkos\t\t: Rp.%.2f\n", tgarage[i]->price_multiplier * BASE_PRICE * route_distance);
        }

        tselect_menu_loop = FALSE;
    }
}

Order newOrder(Order* order_list_arr, index size){
    Order new_order_ctr;

    //array of trains
    Train* train_garage[] = {
        trainFactory("Ekonomi", 1.0, randTimeGen(7, 19), randTimeGen(0, 60), 0, 4, 25, 4),
        trainFactory("Bisnis", 1.25, randTimeGen(9, 15), randTimeGen(0, 60), 0, 3, 16, 4),
        trainFactory("Eksekutif", 1.65, randTimeGen(8, 14), randTimeGen(0, 60), 0, 3, 12, 4),
        trainFactory("Sleeper", 1.95, randTimeGen(16, 23), randTimeGen(0, 60), 0, 3, 23, 2)
    };
    int train_garage_size = sizeof(train_garage)/sizeof(train_garage[0]); //the size

    printf("Pemesanan\n");
    orderDateInput(&new_order_ctr);     //call date setter func.
    orderRouteInput(&new_order_ctr);    //call route setter func.
    trainSelector(&new_order_ctr, train_garage, train_garage_size); //call train setter func.

    //free unused trains
    for(index i = 0; i < train_garage_size; i++){
        trainRecycle(train_garage[i]);
    }
}