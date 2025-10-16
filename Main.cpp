#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include <ctime>
#include <algorithm>
#include <random>
#include <cmath>
#include <filesystem>
#include "class.h"
using std::cin,std::cout,std::string;
template <typename T>
void save_id(T& id){ 
time_t now= time(0);
struct tm* local_time = localtime(&now);
int month = local_time->tm_mon+1;
int year= local_time->tm_year + 1900;
std::random_device rd;
std::mt19937 gn(rd());
std::uniform_int_distribution<> dist(100,900);
int r= dist(gn);
id= std::to_string(year)+std::to_string(month)+std::to_string(r);
}
string gettime(){
    time_t now= time(0);
    return ctime(&now);
}
template <typename vec>
bool found_id(std::vector<vec>& vect,string id,int& count){
for (size_t i = 0; i < vect.size(); i++)
{
    if ((vect[i].id == id))
    {
        count=i;
        return true;
    }
}
return false;
}
string upper(string a){
    std::transform(a.begin(),a.end(),a.begin(), [](unsigned char c){return toupper(c);});
    return a;
}
string lower(string a){
    std::transform(a.begin(), a.end(),a.begin(),[](unsigned char c){return tolower(c);});
    return a;
}
template <typename T>
bool found_entity(std::vector<T>& items, string user_input,int& count){
    for (size_t i = 0; i < items.size(); i++)
    {
        if (lower(items[i].name) == lower(user_input))
        {
             count=i;
            return true;
        }
    }
    return false;
}
template <typename T>
void valid(T& a){
    while (true)
    {
        if (cin>>a)
        {
           if (cin.peek() == '\n' && a >= 0)
           {
            break;
           }
        }   
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        cout << "Invalid input please try again: ";
    }
}
void storeprice(int& price,float user_input){
price = std::round(user_input*100);
}
void saveitems(std::vector<item>& items){
    std::ofstream save("data/items.csv", std::ios::out);
      for(int i=0; i < items.size(); i++)
        save << items[i].id <<","<< lower(items[i].name) << "," << items[i].stock << ","<<items[i].cents_price << "," << items[i].points_got_from_item << "," << items[i].points_to_get_item << "\n";
    save.close();
}
void readitems(std::vector<item>& items, int& count){
std::ifstream read("data/items.csv");
string line;
while (std::getline(read,line))
{
    item it;
    std::stringstream ss(line);
    std::getline(ss,it.id,',');
    std::getline(ss,it.name,',');
    ss >> it.stock;
    ss.ignore(1,',');
    ss >> it.cents_price ;
    ss.ignore(1,',');
    ss>> it.points_got_from_item;
    ss.ignore(1,',');
    ss >> it.points_to_get_item;
    items.emplace_back(it);
    count++;
}
read.close();
}
void savecustomers(std::vector<customer>& customers){
    std::ofstream save("data/customers.csv", std::ios::out);
    for(int i=0; i<customers.size(); i++)
        save<<customers[i].id << "," <<lower(customers[i].name) << ","<< customers[i].phone_number <<","<<customers[i].points << "\n";
    save.close();
}
void readcustomers(std::vector<customer>& customers,int& count){
    std::ifstream read("data/customers.csv");
    string line;
    while (std::getline(read,line))
    {
        customer cu;
        std::stringstream ss(line);
        std::getline(ss,cu.id,',');
        std::getline(ss,cu.name,',');
        std::getline(ss,cu.phone_number,',');
        ss >> cu.points;
        customers.emplace_back(cu);
        count++;
    }
    read.close();
}
void savemain(company info){
std::ofstream save("data/main.csv", std::ios::out);
save << info.name << "," <<info.money << "," << upper(info.curr);
save.close();
}
bool readmain(company& info){
    std::ifstream reads("data/main.csv");
    string line;
    while (std::getline(reads,line))
    {
        std::stringstream ss(line);
        std::getline(ss,info.name,',');
        ss >> info.money;
        ss.ignore(1);
        std::getline(ss,info.curr);
        return true;
    }
    return false;
}
void valid_checker(string& user){
    while(lower(user)!="y" || lower(user)!="n"){
    cout << "Invalid input try again: ";
    cin >> user;
   }
}
void save_purchase(std::vector<purchase>& purchases,string it, int item_count,int price)
{
    purchase p;
 std::ofstream save("data/purchases.csv", std::ios::app);
    save << gettime() <<","<<it << "," << item_count << "," << price <<"\n";
    p.time=gettime();p.item_name = it; p.item_quantity=item_count;p.price;
    purchases.emplace_back(p);
save.close();
}
void read_purchase(std::vector<purchase>& purchases){
std::ifstream read("data/purchases.csv");
string line;
purchase p;
while (std::getline(read,line))
{
    std::stringstream ss(line);
    std::getline(ss,p.time,',');
    std::getline(ss,p.item_name,',');
    ss >> p.item_quantity;
    cin.ignore(1);
    ss>> p.price;
    purchases.emplace_back(p);
}
}
void save_sold(std::vector <sold>& sol, string time, std::vector<customer> cust, int cust_count, std::vector<item>items, int it_count){
sold new_sold;
std::ofstream save("data/sold.csv" , std::ios::app);
new_sold.time = gettime(); new_sold.cust_id = cust[cust_count].id; new_sold.cust_name = cust[cust_count].name; new_sold.item_name = items[it_count].name; new_sold.item_quantity = cust[cust_count].qtt_customer; new_sold.cust_pay = cust[cust_count].paid;
save << new_sold.time << "," << new_sold.cust_id << "," << new_sold.cust_name << "," << new_sold.item_name <<"," <<new_sold.item_quantity << "," << new_sold.cust_pay;
sol.emplace_back(new_sold);
save.close();
}
void separator(){
    for (size_t i = 0; i < 80; i++)
    {
        cout << "*";
    }cout << "\n";
}
void read_sold(std::vector<sold>& sol){
sold new_sold;
std::string line;
std::ifstream read("data/sold.csv");
while (std::getline(read,line))
{
    std::stringstream ss (line);
    std::getline(ss,new_sold.time,',');
    std::getline(ss,new_sold.cust_id,',');
    std::getline(ss,new_sold.cust_name,',');
    std::getline(ss,new_sold.item_name,',');
    ss >> new_sold.item_quantity;
    ss.ignore(1);
    ss>>new_sold.cust_pay;
    sol.emplace_back(new_sold);
}
}
bool checker(){
    std::ifstream read_checker("data/checker.csv");
    string line;
    int a;
    while (std::getline(read_checker,line))
    {
        std::stringstream ss(line);
        ss >> a;
    }if(a == 0){
        std::ofstream write_checker("data/checker.csv", std::ios::out);
        write_checker << 1;
        read_checker.close();
        write_checker.close();
        return true;
    }else{
        read_checker.close();
}return false;
}
void closing(){
    std::ofstream write_checker("data/checker.csv", std::ios::out);
    write_checker << 0;
    write_checker.close();
}
int main() { 
    if (!std::filesystem::exists("data"))
    {
        std::filesystem::create_directories("data");
    }
    cout << std::fixed << std::setprecision(2);
    std::vector<item> items;
    std::vector<customer> customers;
    std::vector<purchase> purchases;
    std::vector<sold> solds;
    company info;
    customer new_customer;
    item new_item;
    bool found=false;
    float user_input_float;
    string user_input_string, purchase_string;
    int paid,option=1,customer_count=0,items_count=0, user_input_int=1;
    bool running = true;
    if(checker()){
    if (!readmain(info))
    {
        cout << "Welcome new user to the store application please enter your name: "; 
        std::getline(cin,info.name);
        cout << "Thank you now please Mr./Ms. " << info.name << " how much money does your company have currently: ";
        valid(user_input_float);
        storeprice(info.money,user_input_float);
        cout << "Enter the name of the company: ";
        cin.ignore();
        std::getline(cin,info.company_name);
        cout << "Now what currency are you using: ";
        cin >> info.curr;
        cout << "Thank you Mr./Ms. " << info.name << " for using the application all ur data has been saved\n";
        savemain(info);
         new_customer.id = "0";
    new_customer.name="Guest";
    customers.emplace_back(new_customer);
    savecustomers(customers);
    }else{
    cout << "Welcome Mr./Ms. " << info.name << " again you currently have in ur acc "<< info.money/100 << " " << info.curr <<"\n";
    readitems(items,items_count);
    readcustomers(customers,customer_count);
    read_purchase(purchases);
    read_sold(solds);
    }
    while (option != 10)
    {
        cout << "Would you like to:\n0-Edit the company's info (your name/money/currency)\n1-Buy/Sell an item\n2-Add a customer\n3-Edit a customer\n4-Add an item\n5-Edit an item\n6-View list of items\n7-View list of customers\n8-View purchase history\n9-View sold history\n10-Exit\n";
        cin >> option;
        if (option == 0)
        {
            while(user_input_int != 4){
            cout <<"Would you like to:\n1-Change your name\n2-Edit the amount of money the company currently have\n3-change the currency\n4-Exit\n";
            valid(user_input_int);
            switch (user_input_int)
            {
            case 1:
                cout << "Enter the new name: "; cin >> info.name;
                break;
            case 2:
            cout << "Enter the new amount: "; valid(user_input_float);
            storeprice(info.money,user_input_float);
            break;
            case 3:
            cout << "Enter the new currency: "; cin >> info.curr;
            break;
            default:
                break;
            }
        }cout << "Changes has been saved successfully\n"; 
        savemain(info);
    }if (option == 1)
    {
        user_input_int =0;
        while(user_input_int != 3){
        cout << "Would you like to:\n1- Buy an item\n2- Sell an item\n3-Exit\n";
        valid(user_input_int);
        switch (user_input_int)
        {
        case 1:
            cout << "What is the item you want to buy: ";
            cin.ignore();
            std::getline(cin,user_input_string);
            if (found_entity(items,user_input_string,items_count) || found_id(items,user_input_string,items_count))
            {
                cout << "Item has been found in memory: \n";
                cout << "Enter the amount of " << lower(user_input_string) << " you have bought: ";
                valid(user_input_int);
                items[items_count].stock += user_input_int;
                cout << "Enter how much you have paid: ";
                valid(user_input_float);
                if(info.money >= std::round(user_input_float*100)){
                info.money -= std::round(user_input_float*100);
                saveitems(items);
                purchase_string = gettime() + "|" + std::to_string(user_input_int) + std::to_string(std::round(user_input_float*100));
                cout << "The number of " << user_input_string << " has been increased\n";
                save_purchase(purchases,items[items_count].name,items[items_count].stock,std::round(user_input_float*100));
                }else
                cout << "Not enough money please change the amount of money the company have!\n";
            }else{
                cout << "Enter the amount of " << lower(user_input_string) << " you have bought: ";
                valid(user_input_int);
                new_item.name = lower(user_input_string);
                new_item.stock = user_input_int;
                cout << "Enter how much you have paid: ";
                valid(user_input_float);
                info.money -= std::round(user_input_float*100);
               do{
                save_id(new_item.id);
               }while(found_id(items,new_item.id,items_count));
               cout << "Enter the amount that you want to sell your item for: ";
               valid(user_input_float);
               storeprice(new_item.cents_price,user_input_float);
               cout << "How many points do the item cost: ";
               valid(user_input_int);
               new_item.points_to_get_item= user_input_int;
               cout << "How many points do the item gives: ";
               valid(user_input_int);
               new_item.points_got_from_item=user_input_int;
               items.emplace_back(new_item);
               saveitems(items);
               cout << "The new item has been added into the company\n";
               save_purchase(purchases,new_item.name,new_item.stock,std::round(user_input_float*100));
            }
            cout << "Your company now have: " << info.money << " " << info.curr; 
            break;
        case 2:
        cout << "Does the customer have an account? y/n\n";
        valid_checker(user_input_string);
        if(user_input_string == "y"){
            cout << "Enter the id of the customer: ";
            cin>>user_input_string;
            if (found_id(customers,user_input_string,customer_count))
            {
                found=true;
            }else
            cout << "Customer not found!\n";
        }else
        customer_count=0;
        while(user_input_string != "0"){
        cout << "Enter the name/id of the items you sold (When done enter 0): ";
        cin.ignore();
        std::getline(cin,user_input_string);
        if(user_input_string != "0"){
        if (!found_entity(items,user_input_string,items_count) || !found_id(items,user_input_string,items_count))
        {
            cout << "Error: Item not found in memory!!\n";
        }else{
            cout << "Enter the quantity sold: ";
            valid(user_input_int);
            if(items[items_count].stock >= user_input_int){
            items[items_count].stock -= user_input_int;
            customers[customer_count].qtt_customer =user_input_int;
            if (found)
            {
                cout << "Did the customer paid via points? y/n\n";
                valid_checker(user_input_string);
                if(lower(user_input_string)!="y")
                customers[customer_count].points -= items[items_count].points_to_get_item*user_input_int;
                customers[customer_count].paid =0;
            }else{
                customers[customer_count].paid = items[items_count].cents_price*customers[customer_count].qtt_customer;
                customers[customer_count].points+= items[items_count].points_got_from_item*customers[customer_count].qtt_customer;
            }
        }else
        cout << "Not enough items in stock\n";
    }
    } cout << "Every change has been saved \n";
    save_sold(solds,gettime(),customers,customer_count,items,items_count);
    savemain(info);
    saveitems(items);
    savecustomers(customers);
        }
        }
    }
}if (option == 2)
    {
        cout << "Enter customer's name: ";
        cin.ignore();
        std::getline(cin,user_input_string);
        new_customer.name = lower(user_input_string);
        cout << "Enter customer's Phone number: ";
        std::getline(cin,new_customer.phone_number);
        save_id(new_customer.id);
        customers.emplace_back(new_customer);
        savecustomers(customers);
    }if (option == 3)
    {
        cout << "Enter the id of the customer: ";
        cin >> user_input_string;
        if(found_id(customers,user_input_string,customer_count)){
            cout << "The user has been found under the name of: " << customers[customer_count].name <<"\n";
            user_input_int =0;
            while (user_input_int != 4)
            {
            cout << "Would you like to:\n1- Change the name\n2- Change the phone number\n3- Delete the customer\n4- Exit\n";
            valid(user_input_int);
                switch(user_input_int){
                    case 1: cout << "Enter the new full name: ";
                    cin.ignore();
                    std::getline(cin,customers[customer_count].name);
                    break;
                    case 2: cout <<"Enter the phone number: ";
                    cin.ignore();
                    std::getline(cin,customers[customer_count].phone_number);
                    break;
                    case 3: customers.erase(customers.begin()+customer_count);
                    savecustomers(customers);
                    break;
                }
            }
        }else{
        cout << "User not found\n";
    }
    }if (option == 4)
    {
       cout << "Enter the name of the item: ";
       cin.ignore();
       std::getline(cin,user_input_string);
       if (!found_entity(items,user_input_string,items_count))
       {
        new_item.name = lower(user_input_string);
        cout << "Enter the price: ";
        valid(user_input_float);
        storeprice(new_item.cents_price,user_input_float);
        cout << "Enter the quantity: ";
        valid(user_input_int);
        new_item.stock = user_input_int;
        cout << "Enter the number of points the item gives: ";
        valid(user_input_int);
        new_item.points_got_from_item = user_input_int;
        cout << "Enter how much the item cost in points: ";
        valid(user_input_int);
        new_item.points_to_get_item=user_input_int;
        items.emplace_back(new_item);
        saveitems(items);
       }else
       cout << "Item already exist\n";
    }if (option == 5)
    {
        cout << "Enter the name/Id of the item you'd like to edit: ";
        cin.ignore();
        std::getline(cin,user_input_string);
        if(found_entity(items,user_input_string,items_count)|| found_id(items,user_input_string,items_count)){
            user_input_int=0;
            cout << "Item has been found under the name of: " << items[items_count].name <<"\n";
            while (user_input_int!= 6 || user_input_int != 7)
            {
                 cout << "Would you like to:\n1- Change the name\n2- Change the price\n3- Change the quantity\n4- Change the points it needs\n5- Change the points it gives\n6- Delete the item\n7- Exit and Save\n";
            cin>>user_input_int;
            switch (user_input_int)
            {
            case 1:
                cout << "Enter the new name: ";
                cin.ignore();
                std::getline(cin,user_input_string);
                items[items_count].name = user_input_string;
                break;
                case 2:
                cout <<"Enter the new price: ";
                valid(user_input_float);
                storeprice(items[items_count].cents_price,user_input_float);
                break;
                case 3:
                cout << "Enter the new quantity of the item: ";
                valid(user_input_int);
                items[items_count].stock = user_input_int;
                break;
                case 4:
                cout << "Enter the new amount of points that the item need for purchase: ";
                valid(user_input_int);
                items[items_count].points_to_get_item = user_input_int;
                break;
                case 5:
                cout << "Enter the new amount of points that the item gives after purchase: ";
                valid(user_input_int);
                items[items_count].points_got_from_item = user_input_int;
                break;
                case 6:
                items.erase(items.begin()+items_count);
            default:
                break;
            }
            cout << "Changes has been saved successfully\n"; 
            saveitems(items);
            }
        }else
        cout << "Item has not been found! \n";
    }if (option == 6)
    {
        separator();
        cout << "Id" << std::setw(5) << "|" << std::setw(5) << "Name" << std::setw(5) << "|" << std::setw(10) << "Quantity" << std::setw(5) << "|" << std::setw(7) << "Price in " << upper(info.curr) << std::setw(5) << "|" << std::setw(8) << "Points given" << std::setw(5) << "|" << std::setw(10) << "Points needed\n";
        for (size_t i = 0; i < items.size(); i++)
        {
        cout << items[i].id << std::setw(5) << "|" << std::setw(5) << upper(items[i].name) << std::setw(5) << "|" << std::setw(5) << items[i].stock << std::setw(5) << "|" << std::setw(5) << items[i].cents_price/100 << std::setw(5) << "|" << std::setw(5) << items[i].points_got_from_item << std::setw(5) << "|" << std::setw(5) << items[i].points_to_get_item <<"\n";
        }
        separator();
    }if (option == 7)
    {
        separator();
        cout << "Id" << std::setw(5) << "|" << std::setw(5) << "Name" << std::setw(5) << "|" << std::setw(5) << "Phone Number" << std::setw(5) << "|" << std::setw(5) << "Points\n";
        for (size_t i = 0; i < customers.size(); i++)
        {
        cout << customers[i].id << std::setw(5) << "|" << std::setw(5) << upper(customers[i].name) << std::setw(5) << "|" << std::setw(5) << customers[i].phone_number << std::setw(5) << "|"<<std::setw(5) << customers[i].points <<"\n";
        }
        separator();
    }
    if (option == 8)
    {separator();
        cout << "Time" << " | "<< "Name" << " | " << "Quantity" <<" | " <<"Paid Price";  
       for (size_t i = 0; i < purchases.size(); i++)
       {
         cout << purchases[i].time << " | " << purchases[i].item_name << " | " << purchases[i].item_quantity << " | " << purchases[i].price; 
       }
       separator();
    }if (option == 9)
    {
        separator();
        cout << "Time" <<" | " << "ID" << " | " << "Customer Name" << " | " <<"Item Name" << " | " << "Quamtity Bought" << " | " << "Customer Paid\n";
        for (size_t i = 0; i < solds.size(); i++)
        {
            cout << solds[i].time << " | " << solds[i].cust_id <<" | " << solds[i].cust_name <<" | " << solds[i].item_name <<" | " << solds[i].item_quantity << " | " <<solds[i].cust_pay << "\n";
        }
        separator();
    }
    if (option == 10)
    {
        closing();
    }
    if (option > 10 || option < 0)
    {
        cout << "Invalid input!\n";
    }
    }
}else{
cout << "App might be already opened please check! If you're sure there is no other copies opened press 0 else close that window!\n"; 
valid(user_input_int);
if (user_input_int == 0)
{
    closing();
    cout << "Please restart the app !\n";
    cin.ignore();
    cin.get();
}
}

}
