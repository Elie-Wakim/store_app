#pragma once
#include<string>
#include <vector>
#include <iostream>
struct company{
int money;
std::string curr,name,company_name;
};
struct item {
    
    int stock;
    int cents_price = 0, points_to_get_item=0, points_got_from_item=0;
    std::string name,id;
};
struct customer {
    
    std::string name,id,phone_number="NULL";
    int qtt_customer=0;
    int paid=0, points=0;
};
struct purchase{
std::string time,item_name;
int item_quantity,price;
};
struct sold{
std::string time,cust_id,cust_name,item_name;
int item_quantity,cust_pay;
};