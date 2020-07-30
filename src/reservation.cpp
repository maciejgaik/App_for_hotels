//
//  reservation.cpp
//  datareservation
//
//  Created by Maciej Gaik on 29/07/2020.
//  Copyright © 2020 Maciej Gaik. All rights reserved.
//

#include "reservation.hpp"

using namespace std;

bool Reservation::new_reservation(const char* start_date, const char* end_date, const char* room_ID, unsigned guest_ID){
    if(check_room(start_date, end_date, room_ID) || check_date(start_date, end_date)){
        throw my_error::DATE_ERROR;
        return false;
    }
    
    string query = "CALL hotelDB.NEW_RESERV(";
    query+=to_string(get_new_ID("RESERVATION"));
    query+=", \"";
    query+=start_date;
    query+="\", \"";
    query+=end_date;
    query+="\", ";
    query+=to_string(calc_nights(get_date(start_date), get_date(end_date)));
    query+=", ";
    query+=room_ID;
    query+=", ";
    query+=to_string(guest_ID);
    query+=")";
    
    cout<<query;
    /*Query executing*/
    if(mysql_query(mysql, query.c_str())){
        throw my_error::QUERY_ERROR;
    }
    
    return true;
}
bool Reservation::check_room(const char* start_date, const char* end_date, const char* room_ID){
    /*Query making*/
    string query="SELECT * FROM hotelDB.RESERVATION WHERE ID_ROOM = ";
    query+=room_ID;
    
    /*Query executing*/
    if(mysql_query(mysql, query.c_str())){
        throw my_error::QUERY_ERROR;
    }
    
    struct tm* startTm = get_date(start_date);
    struct tm* endTm = get_date(end_date);

    MYSQL_RES *res = mysql_store_result(mysql);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res))){
        int day;
        int month;
        int year;
        sscanf(row[1], "%d-%d-%d", &year, &month, &day);
        struct tm* date1=new struct tm;
        date1->tm_mday=day;
        date1->tm_mon=month-1;
        date1->tm_year=year-1900;
        sscanf(row[2], "%d-%d-%d", &year, &month, &day);
        struct tm* date2=new struct tm;
        date2->tm_mday=day;
        date2->tm_mon=month-1;
        date2->tm_year=year-1900;
        if(!comapre_date(date2, startTm) && !comapre_date(endTm, date1)){
            delete date1;
            delete date2;
            delete startTm;
            delete endTm;
            throw my_error::ROOM_RESERVED;
            return false;
        }
        delete date1;
        delete date2;
    }
//    delete startDate;
  //  delete endTm;
    return true;
}
bool Reservation::comapre_date(struct tm* date1, struct tm* date2){
    unsigned long seconds1 = date1->tm_mday + 100*date1->tm_mon + 1000*date1->tm_year;
    unsigned long seconds2 = date2->tm_mday + 100*date2->tm_mon + 1000*date2->tm_year;

    return seconds1<seconds2;
}

bool Reservation::check_date(const char *start_date, const char *end_date){
    struct tm* date1 = get_date(start_date);
    struct tm* date2 = get_date(end_date);
    time_t now = time(0);
    struct tm* timeNow = localtime(&now);
    return comapre_date(timeNow, date1) && comapre_date(date1, date2);
}

struct tm* Reservation::get_date(const char* date){
    int day;
    int month;
    int year;
    sscanf(date, "%d-%d-%d", &year, &month, &day);
    struct tm* tm1=new struct tm;
    tm1->tm_mday=day;
    tm1->tm_mon=month-1;
    tm1->tm_year=year-1900;
    return tm1;
}

unsigned Reservation::get_new_ID(const char *table){
    
    /*Query making*/
    string query="Select MAX(ID) from hotelDB." + string(table);
    
    /*Query executing*/
    if(mysql_query(mysql, query.c_str())){
        throw my_error::QUERY_ERROR;
    }
    MYSQL_ROW row = mysql_fetch_row(mysql_store_result(mysql));
    
    /*Return max ID in table + 1*/
    if(row){
        return atoi(row[0])+1;
    }
    return 0;
}

unsigned Reservation::calc_nights(struct tm* date1, struct tm* date2){
    time_t timeA, timeB;
    timeA = mktime(date1);
    timeB = mktime(date2);
    time_t now = time(0);
    return static_cast<unsigned>(difftime(timeB, timeA))/(3600*24);
}
