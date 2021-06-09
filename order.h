#ifndef ORDER_H
#define ORDER_H

//bool macros, for readibility
#define TRUE  1
#define FALSE 0
#define bool unsigned int

//station position relative to Jakarta


typedef struct{
    //Identity parameters
    char name[50];
    char phone_num[20];
    unsigned int order_num;

    //order details parameters

} Order;

Order newOrder(); //Pemesanan, by main menu #1
bool searchOrder(Order order_ctr, unsigned int order_number); //order search by order_num

#endif