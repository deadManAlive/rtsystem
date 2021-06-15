//ordering mechanics

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include "order.h"

#define BASE_PRICE 360   //Rp. / km
#define TRAIN_AVG_SPEED 84  //kph
#define ETA_DEV_PCT 0.36 //probability/coefficient of route time calculation deviation


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

void trainSelector(Order* trainless_order, Train* tgarage[], int tgarage_size){
    //train select vars.
    bool tselect_menu_loop = TRUE;
    index optptr; //opt. container

    //to supress certain randomness
    bool is_repeat = FALSE; //bool for wheter the menu loop happens after an error in input
    int eta_ctr[tgarage_size]; //contains previous value of eta time value

    //GET current time
    time_t now = time(NULL);
    struct tm current_time = *localtime(&now);

    system(CLEAR_SCREEN);

    while(tselect_menu_loop){
        printf("Pilihan kereta\n");
        printf("Untuk %s, %d-%d-%d dari %s menuju %s:\n\n", trainless_order->day, trainless_order->date, trainless_order->month, trainless_order->year, station_list[trainless_order->origin_idx], station_list[trainless_order->destination_idx]);

        for(index i = 0; i < tgarage_size; i++){
            //ETA analysis
            //generate time struct for departure
            struct tm ttime = {
                .tm_year    = trainless_order->year - 1900,
                .tm_mon     = trainless_order->month - 1,
                .tm_mday    = trainless_order->date,
                .tm_hour    = tgarage[i]->hour,
                .tm_min     = tgarage[i]->minute,
                .tm_sec     = tgarage[i]->second
            };
            time_t dtime =  mktime(&ttime); //departure time value

            //ETA calculation

            int route_distance = abs(distance_list[trainless_order->destination_idx] - distance_list[trainless_order->origin_idx]);
            int route_est_time_seconds; //the eta time

            if(!is_repeat){ //if current cycle is not one after input error, eta time randomized as usual
                route_est_time_seconds = 3600*(float)route_distance/TRAIN_AVG_SPEED;
                route_est_time_seconds = randTimeGen((1.0 - 0.25*ETA_DEV_PCT) * route_est_time_seconds, (1.0 + 0.75*ETA_DEV_PCT) * route_est_time_seconds); //weight deviation range to more late than early by 1:3.
                eta_ctr[i] = route_est_time_seconds; //this stores current eta time
            }
            else{ //if current loop happens after input error, eta time DOES NOT randomized. assigned to value on previous cycle instead
                route_est_time_seconds = eta_ctr[i];
            }

            //ETA
            time_t eta_second = dtime + (time_t)route_est_time_seconds; //eta time value
            struct tm eta_time = *localtime(&eta_second);

            float rtime = difftime(eta_second, dtime);
            
            //view train spesc.
            printf("%d:", i + 1);
            printf("\t[%s]\n", tgarage[i]->train_name);
            printf("\tKeberangkatan\t: %02d:%02d:%02d (%-7s,%02d-%02d-%d)\n", tgarage[i]->hour, tgarage[i]->minute, tgarage[i]->second, trainless_order->day, trainless_order->date, trainless_order->month, trainless_order->year);
            printf("\tETA\t\t: %02d:%02d:%02d (%-7s,%02d-%02d-%d) <~%.1f jam>\n", eta_time.tm_hour, eta_time.tm_min, eta_time.tm_sec, day_name[eta_time.tm_wday], eta_time.tm_mday, eta_time.tm_mon + 1, eta_time.tm_year + 1900, rtime/3600);
            printf("\tJumlah gerbong\t: %d\n", tgarage[i]->train_length);
            printf("\tSeat per gerbong\t: %d\n", tgarage[i]->psg_seat_x * tgarage[i]->psg_seat_y);
            printf("\tSeat tersedia\t: %d\n", freeSeatCalc(tgarage[i]));
            printf("\tOngkos\t\t: Rp.%.2f\n\n", tgarage[i]->price_multiplier * BASE_PRICE * route_distance);
        }

        printf("pilihan kereta (1-%d): ", tgarage_size);

        scanf("%u", &optptr);

        --optptr; //index adj.

        //input checker
        if(optptr < 0 || optptr >= tgarage_size){
            is_repeat = TRUE;
            printf(INPUT_ERROR);
            printf("\n");
            continue;
        }
        else{
            trainless_order->train_index = optptr;

            trainless_order->hour   = tgarage[optptr]->hour;
            trainless_order->minute = tgarage[optptr]->minute;
            trainless_order->second = tgarage[optptr]->second;
        }

        printf("Masukkan 1 untuk lajut, 0 untuk mengulangi: ");

        getchar(); //clears buffer from '\n'(?)
        if(getchar() == '1'){
            //end this while loop
            tselect_menu_loop = FALSE;
        }//user doesn't really need to input 0 again
    }
}

void seatSelector(Order* seatless_order, Train* tgarage[], int tgarage_size){
    //this func vars.
    bool seat_menu_loop = TRUE;
    int optptr;

    system(CLEAR_SCREEN);

    while(seat_menu_loop){
        //menu texts
        printf("[%s] %02d:%02d:%02d %s, %02d-%02d-%d (%d seat tersedia).\n",
               tgarage[seatless_order->train_index]->train_name,
               seatless_order->hour,
               seatless_order->minute,
               seatless_order->second,
               seatless_order->day,
               seatless_order->date,
               seatless_order->month,
               seatless_order->year,
               freeSeatCalc(tgarage[seatless_order->train_index])
        );
        printf("Pilihan seat yang tersedia:\n\n");

        char ncl;   //car char container
        int scar;   //car number
        int scol;   //input column (seaty) as char
        int srow;   //input row (seatx) as int

        trainMapper(tgarage[seatless_order->train_index]);

        printf("Masukkan pilihan seat [gerbong kolom baris] (contoh: 2 A 5): ");

        scanf("%d %c %d", &scar, &ncl, &srow);

        //input validator
        //scol
        scol = (int)ncl;

        if(scol >= 'A' && scol <= 'Z'){ //ASCII checking
            scol -= 'A';
        }
        else if(scol >= 'a' && scol <= 'z'){
            scol -= 'a';
        }
        else{
            printf(INPUT_ERROR);
            printf("\n");
            //continue;
        }

        if(scol < 0 || scol >= tgarage[seatless_order->train_index]->psg_seat_y){ //range checking
            printf(INPUT_ERROR);
            printf("\n");
            continue;
        }
        
        --srow;
        if(srow < 0 || srow >= tgarage[seatless_order->train_index]->psg_seat_x){ //range checking
            printf(INPUT_ERROR);
            printf("\n");
            continue;
        }

        --scar;
        if(scar < 0 || scar >= tgarage[seatless_order->train_index]->train_length){
            printf(INPUT_ERROR);
            printf("\n");
            continue;
        }

        //printf("scar:%d scol:%d srow:%d\n", scar, scol, srow);

        if(seatSetter(tgarage[seatless_order->train_index], scar, srow, scol)){
            system(CLEAR_SCREEN);
            printf("Pemilihan seat berhasil!\n");

            seatless_order->pcar = scar;
            seatless_order->pseatx = srow;
            seatless_order->pseaty = scol;

            trainMapper(tgarage[seatless_order->train_index]);
            seat_menu_loop = FALSE;
        }
        else{
            printf("Gagal memilih seat...\n");
            continue;
        }
    }
}

void finalizeOrder(Order* props, Train* tgarage[], int tgarage_size){
    //summary viewer
    printf("Ringkasan pesanan:\n");
    printf("\tAsal\t: %s\n", station_list[props->origin_idx]);
    printf("\tTujuan\t: %s\n", station_list[props->destination_idx]);
    printf("\tKereta\t: %s\n", tgarage[props->train_index]->train_name);
    printf("\tJadwal\t: %s, %02d-%02d-%d @ %02d:%02d:%02d\n", props->day, props->date, props->month, props->year, props->hour, props->minute, props->second);
    printf("\tSeat\t: %d%c%d", props->pcar + 1, props->pseaty + 'A', props->pseatx + 1);
}

Order newOrder(Order* order_list_arr, index size, Train* train_garage[], int train_garage_size){
    Order new_order_ctr;

    for(int i = 0; i < train_garage_size; i++){ // generates random seat occupation on every order
        seatAvlGenerator(train_garage[i]);
    }

    printf("Pemesanan\n");
    orderDateInput(&new_order_ctr);     //call date setter func.
    orderRouteInput(&new_order_ctr);    //call route setter func.
    trainSelector(&new_order_ctr, train_garage, train_garage_size); //call train setter func.
    seatSelector(&new_order_ctr, train_garage, train_garage_size);  //seat setter.
    finalizeOrder(&new_order_ctr, train_garage, train_garage_size);
}