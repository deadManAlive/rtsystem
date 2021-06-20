//Dasar Komputer-02
//Kelompok 7
//"Self-service train ticketing system + (simulation)"
#include <stdio.h>
#include <stdlib.h>

#include "order.h"
#include "simulation.h"

//order containers
Order order_list[MAX_ORD_SIZE] = {0};

int main(){
    //global vars
    int menu_opt;               //menu choice container
    bool is_not_closed = TRUE;  //main menu loop bool
    char buf[50];               //bufferplaceholder

    //train assets
    //array of trains
    Train* train_garage[] = {
        trainFactory("Ekonomi", 1.0, randTimeGen(7, 19), randTimeGen(0, 60), 0, 4, 25, 4),
        trainFactory("Bisnis", 1.25, randTimeGen(9, 15), randTimeGen(0, 60), 0, 3, 16, 4),
        trainFactory("Eksekutif", 1.65, randTimeGen(8, 14), randTimeGen(0, 60), 0, 3, 12, 4),
        trainFactory("Sleeper", 1.95, randTimeGen(16, 23), randTimeGen(0, 60), 0, 3, 23, 2)
    };
    int train_garage_size = sizeof(train_garage)/sizeof(train_garage[0]); //the size

    system(CLEAR_SCREEN);

    //main menu loop
    while(is_not_closed){

        //welcome texts and menu list
        printf("Self-service Train Ticketing Machine\n");
        printf("by DK02_g07 (v1.0.0)\n");

        printf("Menu:\n");
        printf("\t1. Pemesanan.\n");
        printf("\t2. Lihat pesanan.\n");
        printf("\t3. Daftar pesanan.\n");
        printf("\t4. Bantuan.\n");
        printf("\t0. Keluar\n");
        printf("Masukan pilihan: ");

        scanf("%d", &menu_opt);        //main menu input read

        switch(menu_opt){
            case 1:
                //Pemesanan
                newOrder(order_list, MAX_ORD_SIZE, train_garage, train_garage_size);
                break;
            case 2:
                //Lihat pesanan
                searchOrder(order_list, MAX_ORD_SIZE, train_garage, train_garage_size);
                break;
            case 3:
                //daftar pesanan
                listOrders(order_list, MAX_ORD_SIZE);
                break;
            case 4:
                {
                    system(CLEAR_SCREEN);

                    printf("This source code is made by DK02_g07 as final programming assignment in Even Semester\n2020/2021 for course Basic Computer + Lab. (ENEE603014) in Undergraduate of\nElectrical Engineering study program, Department of Electrical Engineering, Faculty of\nEngineering, Universitas Indonesia.");

                    printf("\n\n");

                    printf("INPUT X TO CONTINUE: ");

                    pause_scr('X');
                }
                break;
            case 0:
                is_not_closed = FALSE;
                break;
            default:
                printf(INPUT_ERROR); printf(" Masukkan 0 untuk lanjut: ");
                pause_scr('0');
        }

        //clear terminal
        system(CLEAR_SCREEN);
    }

    //system(CLEAR_SCREEN);
    printf("Terima kasih telah menggunakan layanan kami.");

    getchar(); //clears '\n'

    while (getchar() != '\n');

    return 0;
}