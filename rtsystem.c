//Dasar Komputer-02
//Kelompok 7
//"Self-service train ticketing system + (simulation)"
#include <stdio.h>
#include <stdlib.h>

#include "order.h"
#include "simulation.h"

//OS command compatibility
#ifdef _WIN32
#define CLEAR_SCREEN "cls"     // for Windows
#else
#define CLEAR_SCREEN "clear"   // for *nix
#endif

//error macros
#define INPUT_ERROR "Err 001: masukkan salah! Tekan 1 untuk lanjut: "

int main(){
    //global vars
    int menu_opt;               //menu choice container
    bool is_not_closed = TRUE;  //main menu loop bool
    char buf[50];               //bufferplaceholder

    //main menu loop
    while(is_not_closed){
        //clear terminal
        system(CLEAR_SCREEN);

        //welcome texts and menu list
        printf("Self-service Train Ticketing Machine\n");
        printf("by DK02-07 v0.0.1\n");

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
                break;
            case 2:
                //Lihat pesanan
                break;
            case 3:
                //bantuan
                break;
            case 0:
                is_not_closed = FALSE;
                break;
            default:
                printf(INPUT_ERROR);
                while (getchar() != '1'); //shows error until user inputs '1'
        }
    }

    system(CLEAR_SCREEN);
    printf("Terima kasih telah menggunakan layanan kami.");

    return 0;
}