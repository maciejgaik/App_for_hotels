//
//  base.hpp
//  database
//
//  Created by Maciej Gaik on 20/07/2020.
//  Copyright © 2020 Maciej Gaik. All rights reserved.
//

#ifndef base_hpp
#define base_hpp

#include <iostream>
#include <mysql.h>
#include <ctime>
#include <cstring>
#include <ctime>

#include "guest.hpp"
#include "reservation.hpp"

class base{
public:
    base(){
        mysql_init(&mysql);
        guest.init(&mysql);
        reservation.init(&mysql);
    }
    
    bool connect(){
        return mysql_real_connect(&mysql, "127.0.0.1", "root", "gaiczek1", "hotelDB", 0, NULL, 0);
    };
    
    void disconnect(){
        mysql_close(&mysql);
    };
    
    unsigned int getErrorNumber(){
        return mysql_errno(&mysql);
    }
    
    bool new_reser_for_new_guest(const char* name, const char* surname, const char *phone, const char* country, const char *zip_code, const char* city, const char* street, const char *house_number, const char *flat_number, const char* start_date, const char* end_date, const char* room_ID);
    bool findGuest();
    bool edit();
    bool findRoom();
private:
    MYSQL mysql;
    unsigned getNewID(const char *table);
    Guest guest;
    Reservation reservation;

};

#endif /* base_hpp */
