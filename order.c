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
        
        if(yr > 9999){
            printf(INPUT_ERROR); printf("\n");
            continue;
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
        printf("\nMasukkan 1 untuk lanjut, 0 untuk mengulangi: ");

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
    float price[tgarage_size]; //contains price

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

            //price
            price[i] = tgarage[i]->price_multiplier * BASE_PRICE * route_distance;
            
            //view train spesc.
            printf("%d:", i + 1);
            printf("\t[%s]\n", tgarage[i]->train_name);
            printf("\tKeberangkatan\t: %02d:%02d:%02d (%-7s,%02d-%02d-%d)\n", tgarage[i]->hour, tgarage[i]->minute, tgarage[i]->second, trainless_order->day, trainless_order->date, trainless_order->month, trainless_order->year);
            printf("\tETA\t\t: %02d:%02d:%02d (%-7s,%02d-%02d-%d) <~%.1f jam>\n", eta_time.tm_hour, eta_time.tm_min, eta_time.tm_sec, day_name[eta_time.tm_wday], eta_time.tm_mday, eta_time.tm_mon + 1, eta_time.tm_year + 1900, rtime/3600);
            printf("\tJumlah gerbong\t: %d\n", tgarage[i]->train_length);
            printf("\tJumlah seat\t: %d/%d\n", tgarage[i]->psg_seat_x * tgarage[i]->psg_seat_y, tgarage[i]->train_length * tgarage[i]->psg_seat_x * tgarage[i]->psg_seat_y);
            printf("\tSeat tersedia\t: %d\n", freeSeatCalc(tgarage[i]));
            printf("\tOngkos\t\t: Rp.%.2f\n\n", price[i]);
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

            trainless_order->price  = price[optptr];
        }

        printf("Masukkan 1 untuk lanjut, 0 untuk mengulangi: ");

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
            printf(": kolom");
            printf("\n");
            continue;
        }

        if(scol < 0 || scol >= tgarage[seatless_order->train_index]->psg_seat_y){ //range checking
            printf(INPUT_ERROR);
            printf(": kolom");
            printf("\n");
            continue;
        }
        
        --srow;
        if(srow < 0 || srow >= tgarage[seatless_order->train_index]->psg_seat_x){ //range checking
            printf(INPUT_ERROR);
            printf(": baris");
            printf("\n");
            continue;
        }

        --scar;
        if(scar < 0 || scar >= tgarage[seatless_order->train_index]->train_length){
            printf(INPUT_ERROR);
            printf(": gerbong");
            printf("\n");
            continue;
        }

        //printf("scar:%d scol:%d srow:%d\n", scar, scol, srow);

        if(seatSetter(tgarage[seatless_order->train_index], DRIFT, scar, srow, scol)){ //sets seat to DRIFT to detect in mapper func.
            system(CLEAR_SCREEN);
            printf("Pemilihan seat berhasil!\n");

            seatless_order->pcar = scar;
            seatless_order->pseatx = srow;
            seatless_order->pseaty = scol;

            trainMapper(tgarage[seatless_order->train_index]);
            printf("\nSeat terpilih ditandai '#'\n\n");
            printf("Masukkan 1 untuk lanjut: ");
            pause_scr('1');

            seatSetter(tgarage[seatless_order->train_index], TRUE, scar, srow, scol); //sets DRIFT-ed seat to TRUE

            seat_menu_loop = FALSE;
        }
        else{
            printf("Gagal memilih seat...\n");
            printf("Masukkan 0 untuk mengulangi: ");
            pause_scr('0');
            continue;
        }
    }
}

void finalizeOrder(Order* props, Train* tgarage[], int tgarage_size){
    int optvar;

    char name[50];
    char phone[20];


    bool final_menu_loop = TRUE;

    while(final_menu_loop){
        system(CLEAR_SCREEN);

        //summary viewer
        printf("Ringkasan pesanan:\n");
        printf("\tAsal\t: %s\n", station_list[props->origin_idx]);
        printf("\tTujuan\t: %s\n", station_list[props->destination_idx]);
        printf("\tKereta\t: %s\n", tgarage[props->train_index]->train_name);
        printf("\tJadwal\t: %s, %02d-%02d-%d @ %02d:%02d:%02d\n", props->day, props->date,  props->month, props->year, props->hour, props->minute, props->second);
        printf("\tSeat\t: %d%c%d", props->pcar + 1, props->pseaty + 'A', props->pseatx + 1);

        printf("\n\n#######################################################\n\n");
        printf("\t1.Lanjut.\n");
        printf("\t2.Perbaiki jadwal.\n");
        printf("\t3.Perbaiki rute.\n");
        printf("\t4.Pilih ulang kereta.\n");
        printf("\t5.Pilih ulang seat.\n");
        printf("Opsi: ");

        scanf("%d", &optvar);

        switch(optvar){
            case 1:
                printf("Masukkan nama\t\t: ");
                scanf("%s", &name);
                printf("Masukkan no telp.\t: ");
                scanf("%s", &phone);

                strcpy(props->name, name);
                strcpy(props->phone_num, phone);

                final_menu_loop = FALSE;
                break;
            case 2:
                orderDateInput(props);
                break;
            case 3:
                orderRouteInput(props);
                break;
            case 4:
                trainSelector(props, tgarage, tgarage_size);
                break;
            case 5:
                seatSelector(props, tgarage, tgarage_size);
                break;
            default:
                printf(INPUT_ERROR);
                printf("Masukkan 0 untuk lanjut: ");         
                pause_scr('0');
                finalizeOrder(props, tgarage, tgarage_size); //a recursion
        }

        //order ID setter
        char order_ID_c[20];

        //two-last-digit-of-year setter
        char year[10];
        sprintf(year, "%d", props->year); //int to char*
        sprintf(year, "%c%c", year[strlen(year) - 2], year[strlen(year) - 1]); //get 2 last digit

        sprintf( //assign formatted string to ordid
            order_ID_c,
            "%02d%02d%s%02d%02d%02d%c%d%c", //"ddmmyyhhmmssTxy"
            props->date,
            props->month,
            year,
            props->hour,
            props->minute,
            props->second,
            tgarage[props->train_index]->train_name[0],
            props->pseatx,
            (char)(props->pseaty + 'A')
        );

        strcpy(props->order_ID, order_ID_c);

        srand(time(NULL)); //seed randomization

        props->is_occupied_L = randTimeGen(RAND_MAX/2, RAND_MAX);

        props->is_occupied_R = props->is_occupied_L;
    }
}

int orderListArr(Order order_list_arr[], index order_arr_size){ //order array placement func. return -1 when array full
    for(index i = 0; i < order_arr_size; i++){
        if(order_list_arr[i].is_occupied_L > 0 || order_list_arr[i].is_occupied_R > 0){ //if either pair is non-zero (to check if order initialized to trash in memory)
            if(order_list_arr[i].is_occupied_L != order_list_arr[i].is_occupied_R){
                return i;
            }
        }
        else if(order_list_arr[i].is_occupied_L == 0 && order_list_arr[i].is_occupied_R == 0){ //if both pair is 0. if struct member assigned to 0 when initialized.
            return i;
        }
    }
    return -1;
}

void ticketView(Order* props, int ord_idx, Train* tgarage[], int tgarage_size){
    char str_ctr[100]; //temporary string container
    int str_sz; //temporary 

    system(CLEAR_SCREEN);

    printf("//TIKET//\n\n");

    for(int i = 0; i < 50; i++){ //print upper border: 50 space width
        printf("#");
    }
    printf("\n");

    printf("# %09d%*c\n", ord_idx + 1, 39, '#');
    printf("# ID pesanan    : %s%*c\n", props->order_ID, 50 - (int)strlen(props->order_ID) - 18, '#');
    printf("# Nama          : %s%*c\n", props->name, 50 - (int)strlen(props->name) - 18, '#');
    printf("# Telepon       : %s%*c\n", props->phone_num, 50 - (int)strlen(props->phone_num) - 18, '#');
    printf("# %*c\n", 48, '#');
    printf("# Asal          : %s%*c\n", station_list[props->origin_idx], 50 - (int)strlen(station_list[props->origin_idx]) - 18, '#');
    printf("# Tujuan        : %s%*c\n", station_list[props->destination_idx], 50 - (int)strlen(station_list[props->destination_idx]) - 18, '#');
    printf("# Tanggal       : %s, %02d-%02d-%04d%*c\n", props->day, props->date, props->month, props->year, 50-(int)strlen(props->day)-30, '#');
    printf("# Waktu         : %02d:%02d:%02d%*c\n", props->hour, props->minute, props->second, 24, '#');
    printf("# %*c\n", 48, '#');
    printf("# Kereta        : [%s]%*c\n", tgarage[props->train_index]->train_name, 50 - (int)strlen(tgarage[props->train_index]->train_name) - 20, '#');
    printf("# Seat          : %-2d%-2c%-2d%*c\n", props->pcar, props->pseaty + 'A', props->pseatx, 26, '#');

    for(int i = 0; i < 50; i++){ //print upper border: 50 space width
        printf("#");
    }

    printf("\n\n");
    printf("Masukkan 1 untuk lanjut: ");
    pause_scr('1');
}

void newOrder(Order order_list_arr[], index order_arr_size, Train* train_garage[], int train_garage_size){
    //position in array
    int posarr = orderListArr(order_list_arr, order_arr_size); //get empty position in array

    if(posarr == -1){ //check if no element assignable
        printf(ORDER_FULL);
        return;
    }

    system(CLEAR_SCREEN);

    printf("order #%09d\n\n", posarr + 1); //views order number (index)

    for(int i = 0; i < train_garage_size; i++){ // generates random seat occupation on every order
        seatAvlGenerator(train_garage[i]);
    }

    Order new_order_ctr;

    printf("Pemesanan\n");
    orderDateInput(&new_order_ctr);     //call date setter func.
    orderRouteInput(&new_order_ctr);    //call route setter func.
    trainSelector(&new_order_ctr, train_garage, train_garage_size); //call train setter func.
    seatSelector(&new_order_ctr, train_garage, train_garage_size);  //seat setter.
    finalizeOrder(&new_order_ctr, train_garage, train_garage_size); //finalize

    //Ticket view
    ticketView(&new_order_ctr, posarr, train_garage, train_garage_size); //print ticket

    order_list_arr[posarr] = new_order_ctr; //assign new order to provided position in array
}