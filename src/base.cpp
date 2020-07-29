//
//  base.cpp
//  database
//
//  Created by Maciej Gaik on 20/07/2020.
//  Copyright © 2020 Maciej Gaik. All rights reserved.
//

#include "base.hpp"

using namespace std;

unsigned base::getNewID(const char *table){
    
    /*Query making*/
    string query="Select MAX(ID) from hotelDB." + string(table);
    
    /*Query executing*/
    mysql_query(&mysql, query.c_str());
    MYSQL_ROW row = mysql_fetch_row(mysql_store_result(&mysql));
    
    /*Return max ID in table + 1*/
    return atoi(row[0])+1;
}

bool base::newReserForNewGuest(const char* name, const char* surname, const char *phone, const char* country, const char *zipCode, const char* city, const char* street, const char *houseNumber, const char *flatNumber, const char* startDate, const char* endDate, const char* roomID){

//    getDate(startDate);
//    if(checkGuest(name, surname, city, street, houseNumber)){
//        return false;
//    }
    
    /*Query making*/
    string query = "CALL hotelDB.NEW_GUEST(";
    query+=to_string(getNewID("guest"));
    query+=", \"";
    query+=name;
    query+="\", \"";
    query+=surname;
    query+="\", ";
    query+=phone;
    query+=", \"";
    query+=country;
    query+="\", ";
    query+=zipCode;
    query+=", \"";
    query+=city;
    query+="\", \"";
    query+=street;
    query+="\", ";
    query+=houseNumber;
    query+=", ";
    query+=flatNumber;
    query+=")";
    
    /*Query executing*/
    mysql_query(&mysql, query.c_str());
    return true;
}
