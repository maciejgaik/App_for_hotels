//
//  guest.cpp
//  database
//
//  Created by Maciej Gaik on 29/07/2020.
//  Copyright © 2020 Maciej Gaik. All rights reserved.
//

#include "guest.hpp"

using namespace std;

unsigned Guest::getNewID(const char *table){
    
    /*Query making*/
    string query="Select MAX(ID) from hotelDB." + string(table);
    
    /*Query executing*/
    if(mysql_query(mysql, query.c_str())){
        throw my_error::QUERY_ERROR;
    }
    
    MYSQL_ROW row = mysql_fetch_row(mysql_store_result(mysql));
    //cout<<row[0];
    if(row){
        return atoi(row[0])+1;
    }
    else return 0;
}

unsigned Guest::checkGuest(const char *name, const char *surname, const char *city, const char *street, const char *houseNumber){
    
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
    if(mysql_query(mysql, query.c_str())){
        throw my_error::QUERY_ERROR;
    }
    
    MYSQL_ROW row = mysql_fetch_row(mysql_store_result(mysql));
    /*If there is the same guest return ID, else INT_MAX*/
    if(row){
        return atoi(row[0]);
    }
    else return INT_MAX;
}

unsigned Guest::newGuest(const char* name, const char* surname, const char *phone, const char* country, const char *zipCode, const char* city, const char* street, const char *houseNumber, const char *flatNumber){
    
    unsigned ID = checkGuest(name, surname, city, street, houseNumber);

    /*Chechking if there is the same guest*/
    /*If yes return ID*/
    if(ID != INT_MAX) return ID;
    
    ID = getNewID("guest");
    /*Query making*/
    string query = "CALL hotelDB.NEW_GUEST(";
    query+=to_string(ID);
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
    if(mysql_query(mysql, query.c_str())){
        throw my_error::QUERY_ERROR;
    }
    return ID;
}

