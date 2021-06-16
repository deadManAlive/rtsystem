#ifndef ORDER_H
#define ORDER_H

#include "generics.h"
#include "simulation.h"

//ordering macros
typedef unsigned long int distance_kmeter; //distance

//order struct :D
typedef struct{
    //struct occupation validation param.
    //type is long to contains RAND_MAX value
    //probability of same L-R value = 1/(RAND_MAX^2) = 2 * 10^-17.
    long is_occupied_L;
    long is_occupied_R;
    
    //order
    unsigned long int price; //dependept parameters, set in newOrder func[!!!]
    char order_ID[20];  //set at ordering. used when user recheck for order (ddmmyyhhmm[train_init].x.y)
    index pcar;   //car numb.  
    index pseatx; //seat...
    index pseaty; //...number index (start at 0)
    index train_index; //index to train type
    
    //Identity parameters
    char name[50];
    char phone_num[20];

    //order details parameters
    //orgin and destination are index of distance_list arr
    index origin_idx;          
    index destination_idx;

    //departure date
    char day[10];
    int date;   
    int month;
    int year;
    //departure time
    int hour;
    int minute;
    int second;
    
} Order;

//functions
void newOrder(Order* order_list_arr, index size, Train* train_garage[], int train_garage_size); //Pemesanan, by main menu #1
int searchOrder(Order order_ctr, const char* order_ID); //order search by order_num

#endif