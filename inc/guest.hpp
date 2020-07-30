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
#include <climits>
#include "my_error.hpp"

class Guest{
    unsigned getNewID(const char* table);
    MYSQL* mysql;
    unsigned checkGuest(const char* name, const char* surname,const char* city, const char* street, const char *houseNumber);
//    Error error;
public:
    void init(MYSQL* _mysql){ mysql = _mysql; };
    unsigned newGuest(const char* name, const char* surname, const char *phone, const char* country, const char *zipCode, const char* city, const char* street, const char *houseNumber, const char *flatNumber);
};

#endif /* guest_hpp */
