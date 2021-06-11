//Dasar Komputer-02
//Kelompok 7
//"Self-service train ticketing system + (simulation)"
#include <stdio.h>
#include <stdlib.h>

#include "order.h"
#include "simulation.h"

//ORDERING DATA
/*
station position relative to Jakarta (Gambir)
1. Jakarta: Gambir
2. Cirebon: Cirebon
3. Semarang: Poncol
4. Surabaya: Pasar Turi
5. Malang: Malang
*/
const distance_kmeter distance_list[] = {
    0,      //Gambir
    218,    //Cirebon
    442,    //Semarang
    742,    //Surabaya
    870     //Malang
};

//temporary orders container, before simulation implementation
Order order_list[100];

//pause screen function
void pause_scr(char char_to_press){
    while (getchar() != char_to_press); //prevent adv. until user inputs certain char.
}

int main(){
    //global vars
    int menu_opt;               //menu choice container
    bool is_not_closed = TRUE;  //main menu loop bool
    char buf[50];               //bufferplaceholder

    //main menu loop
    while(is_not_closed){

        //welcome texts and menu list
        printf("Self-service Train Ticketing Machine\n");
        printf("by DK02_g07 (v0.0.1)\n");

        printf("Menu:\n");
        printf("\t1. Pemesanan.\n");
        printf("\t2. Lihat pesanan.\n");
        printf("\t3. Bantuan.\n");
        printf("\t0. Keluar\n");
        printf("Masukan pilihan: ");

        scanf("%d", &menu_opt);        //main menu input read

        switch(menu_opt){
            case 1:
                //Pemesanan
                newOrder(order_list, 100);
                pause_scr('0');
                break;
            case 2:
                //Lihat pesanan
                pause_scr('0');
                break;
            case 3:
                //bantuan
                pause_scr('0');
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

    return 0;
}