#ifndef ORDER_H
#define ORDER_H

#include "generics.h"


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

    unsigned long int price; //dependept parameters, set in newOrder func[!!!]
    unsigned int order_num;  //set at ordering, count all passengers?
    bool is_ordered;         //wtf?  
} Order;

//functions
void newOrder(Order* order_list_arr, index size); //Pemesanan, by main menu #1
bool searchOrder(Order order_ctr, unsigned int order_number); //order search by order_num

#endif