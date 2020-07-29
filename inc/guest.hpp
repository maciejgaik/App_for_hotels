//
//  guest.hpp
//  database
//
//  Created by Maciej Gaik on 29/07/2020.
//  Copyright © 2020 Maciej Gaik. All rights reserved.
//

#ifndef guest_hpp
#define guest_hpp

#include <iostream>
#include <mysql.h>
#include <ctime>
#include <cstring>
#include <ctime>

class guest{
    unsigned getNewID(const char* table);
    bool checkGuest(const char* name, const char* surname,const char* city, const char* street, const char *houseNumber);
    MYSQL* mysql;
public:
    guest(MYSQL* _mysql) : mysql{_mysql} {}
    bool newGuest(const char* name, const char* surname, const char *phone, const char* country, const char *zipCode, const char* city, const char* street, const char *houseNumber, const char *flatNumber);
    
};

#endif /* guest_hpp */
