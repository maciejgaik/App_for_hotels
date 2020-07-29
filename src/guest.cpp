//
//  guest.cpp
//  database
//
//  Created by Maciej Gaik on 29/07/2020.
//  Copyright © 2020 Maciej Gaik. All rights reserved.
//

#include "guest.hpp"

using namespace std;

unsigned guest::getNewID(const char *table){
    
    /*Query making*/
    string query="Select MAX(ID) from hotelDB." + string(table);
    
    /*Query executing*/
    mysql_query(mysql, query.c_str());
    MYSQL_ROW row = mysql_fetch_row(mysql_store_result(mysql));
    
    /*Return max ID in table + 1*/
    return atoi(row[0])+1;
}

bool guest::checkGuest(const char *name, const char *surname, const char *city, const char *street, const char *houseNumber){
    
    /*Query making*/
    string query = "SELECT * FROM GUEST WHERE G_NAME = \"";
    query+=name;
    query+="\" AND SURNAME = \"";
    query+=surname;
    query+="\" AND CITY = \"";
    query+=city;
    query+="\" AND STREET = \"";
    query+=street;
    query+="\" AND NUM_BUILDING = ";
    query+=houseNumber;
    
    /*Query executing*/
    mysql_query(mysql, query.c_str());
    
    /*If there is the same guest return true, else false*/
    if(mysql_num_rows(mysql_store_result(mysql))) return true;
    else return false;
}

bool guest::newGuest(const char* name, const char* surname, const char *phone, const char* country, const char *zipCode, const char* city, const char* street, const char *houseNumber, const char *flatNumber){

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
    mysql_query(mysql, query.c_str());
    return true;
}

