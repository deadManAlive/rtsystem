#ifndef ORDER_H
#define ORDER_H

#include "generics.h"

//ordering macros
typedef unsigned long int distance_kmeter; //distance

//order struct :D
typedef struct{
    //usable in array, hopefully.
    bool is_occupied;
    
    //Identity parameters
    char name[50];
    char phone_num[20];

    //order details parameters
    //orgin and destination are index of distance_list arr
    index origin_idx;          
    index destination_idx;

    //date
    int date;   
    int month;
    int year;
    
    //?
    unsigned long int price; //dependept parameters, set in newOrder func[!!!]
    unsigned int order_num;  //set at ordering, count all passengers?
} Order;

//functions
Order newOrder(Order* order_list_arr, index size); //Pemesanan, by main menu #1
bool searchOrder(Order order_ctr, unsigned int order_number); //order search by order_num

#endif