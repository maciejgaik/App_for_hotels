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

bool base::comapreDate(struct tm* date1, struct tm* date2){
    unsigned long seconds1 = date1->tm_mday + 100*date1->tm_mon + 1000*date1->tm_year;
    unsigned long seconds2 = date2->tm_mday + 100*date2->tm_mon + 1000*date2->tm_year;
    
    return seconds1<seconds2;
}

struct tm* base::getDate(const char* date){
    int day;
    int month;
    int year;
    sscanf(date, "%d.%d.%d", &day, &month, &year);
    struct tm* tm1=new struct tm;
    struct tm* tm2=new struct tm;
    tm1->tm_mday=day;
    tm1->tm_mon=month;
    tm1->tm_year=year-1900;
    tm2->tm_mday=day;
    tm2->tm_mon=month;
    tm2->tm_year=year-1900;
    time_t timek = mktime(tm1);
    time_t timel = mktime(tm2);
    cout<<difftime(timel, timek)<<endl;
    time_t now = time(0);
    struct tm* timeNow = localtime(&now);
    timeNow->tm_year+=1900;
    cout<<timeNow->tm_mday<<"."<<timeNow->tm_mon<<"."<<timeNow->tm_year<<endl;
    return tm1;
}

bool base::checkGuest(const char *name, const char *surname, const char *city, const char *street, const char *houseNumber){
    
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
    mysql_query(&mysql, query.c_str());
    
    /*If there is the same guest return true, else false*/
    if(mysql_num_rows(mysql_store_result(&mysql))) return true;
    else return false;
}

bool base::newGuest(const char* name, const char* surname, const char *phone, const char* country, const char *zipCode, const char* city, const char* street, const char *houseNumber, const char *flatNumber, const char* startDate){

    getDate(startDate);
    if(checkGuest(name, surname, city, street, houseNumber)){
        return false;
    }
    
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
