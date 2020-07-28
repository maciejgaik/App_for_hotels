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

class base{
public:
    base(){
        mysql_init(&mysql);
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
    
    bool newGuest(const char* name, const char* surname, const char *phone, const char* country, const char *zipCode, const char* city, const char* street, const char *houseNumber, const char *flatNumber, const char* startDate);
    bool newEmployee();
    bool newReservation();
    bool findGuest();
    bool findEmployee();
    bool edit();
    bool findRoom();
    
    
    
private:
    MYSQL mysql;
    unsigned getNewID(const char* table);
    bool checkGuest(const char* name, const char* surname,const char* city, const char* street, const char *houseNumber);
    struct tm* getDate(const char* date);
    bool comapreDate(struct tm* date1, struct tm* date2);
};

#endif /* base_hpp */
