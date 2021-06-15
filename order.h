#ifndef ORDER_H
#define ORDER_H

#include "generics.h"

//ordering macros
typedef unsigned long int distance_kmeter; //distance

//order struct :D
typedef struct{
    //usable in array.
    bool is_occupied;
    //dependent members
    unsigned long int price; //dependept parameters, set in newOrder func[!!!]
    char order_ID[12];  //set at ordering. used when user recheck for order (ddmmyyhhmm[train_init])
    
    //Identity parameters
    char name[50];
    char phone_num[20];

    //order details parameters
    //orgin and destination are index of distance_list arr
    index origin_idx;          
    index destination_idx;

    //date
    char day[10];
    int date;   
    int month;
    int year;
    
} Order;

//functions
Order newOrder(Order* order_list_arr, index size); //Pemesanan, by main menu #1
bool searchOrder(Order order_ctr, const char* order_ID); //order search by order_num

#endif