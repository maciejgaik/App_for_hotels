//
//  reservation.cpp
//  datareservation
//
//  Created by Maciej Gaik on 29/07/2020.
//  Copyright © 2020 Maciej Gaik. All rights reserved.
//

#include "reservation.hpp"

using namespace std;

bool reservation::newReservation(const char* startDate, const char* endDate, const char* roomID, const char* guestID){
    if(!checkDate(startDate, endDate)) return false;
    
    
    return true;
}
bool reservation::chceckRoom(const char* startDate, const char* endDate, const char* roomID){
    /*Query making*/
    string query="SELECT * FROM hotelDB.RESERVATION WHERE ID_ROOM = ";
    query+=roomID;
    
    /*Query executing*/
    mysql_query(mysql, query.c_str());
    
    struct tm* startTm = getDate(startDate);
    struct tm* endTm = getDate(endDate);

    MYSQL_RES *res = mysql_store_result(mysql);
    int num_fields = mysql_num_fields(res);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res))){
        int day;
        int month;
        int year;
        sscanf(row[1], "%d-%d-%d", &year, &month, &day);
        struct tm* date1=new struct tm;
        date1->tm_mday=day;
        date1->tm_mon=month;
        date1->tm_year=year-1900;
        sscanf(row[2], "%d-%d-%d", &year, &month, &day);
        struct tm* date2=new struct tm;
        date2->tm_mday=day;
        date2->tm_mon=month;
        date2->tm_year=year-1900;
        if(!comapreDate(date2, startTm) && !comapreDate(endTm, date1)){
            delete date1;
            delete date2;
            delete startTm;
            delete endTm;
            return false;
        }
        delete date1;
        delete date2;
    }
    delete startDate;
    delete endTm;
    return true;
}
bool reservation::comapreDate(struct tm* date1, struct tm* date2){
    unsigned long seconds1 = date1->tm_mday + 100*date1->tm_mon + 1000*date1->tm_year;
    unsigned long seconds2 = date2->tm_mday + 100*date2->tm_mon + 1000*date2->tm_year;

    return seconds1<seconds2;
}

bool reservation::checkDate(const char *startDate, const char *endDate){
    struct tm* date1 = getDate(startDate);
    struct tm* date2 = getDate(endDate);
    time_t now = time(0);
    struct tm* timeNow = localtime(&now);
    return comapreDate(timeNow, date1) && comapreDate(date1, date2);
}

struct tm* reservation::getDate(const char* date){
    int day;
    int month;
    int year;
    sscanf(date, "%d.%d.%d", &day, &month, &year);
    struct tm* tm1=new struct tm;
    tm1->tm_mday=day;
    tm1->tm_mon=month;
    tm1->tm_year=year-1900;
    return tm1;
}
