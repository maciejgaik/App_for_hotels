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

bool base::new_reser_for_new_guest(const char* name, const char* surname, const char *phone, const char* country, const char *zip_code, const char* city, const char* street, const char *house_number, const char *flat_number, const char* start_date, const char* end_date, const char* room_ID){
    
    unsigned guest_ID = guest.newGuest(name, surname, phone, country, zip_code, city, street, house_number, flat_number);
    reservation.new_reservation(start_date, end_date, room_ID, guest_ID);

    return true;
}
