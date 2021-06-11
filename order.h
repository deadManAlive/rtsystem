#ifndef ORDER_H
#define ORDER_H

#include "generics.h"

//ordering macros
typedef unsigned long int distance_kmeter; //distance

//order struct :D
typedef struct{
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
    char bool_is_occupied;   //set to "TRUE" if true "FALSE" if false, cannot use bool because struct has no constructor.
} Order;

//functions
Order newOrder(Order* order_list_arr, index size); //Pemesanan, by main menu #1
bool searchOrder(Order order_ctr, unsigned int order_number); //order search by order_num

#endif