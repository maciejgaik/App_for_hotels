//
//  reservation.hpp
//  database
//
//  Created by Maciej Gaik on 29/07/2020.
//  Copyright © 2020 Maciej Gaik. All rights reserved.
//

#ifndef reservation_hpp
#define reservation_hpp

#include <iostream>
#include <mysql.h>
#include <ctime>
#include <cstring>
#include <ctime>

class reservation{
    MYSQL* mysql;
public:
    reservation(MYSQL* _mysql) : mysql{_mysql} {}
    bool newReservation(const char* startDate, const char* endDate, const char* roomID, const char* guestID);
    struct tm* getDate(const char* date);
    bool comapreDate(struct tm* date1, struct tm* date2);
    bool checkDate(const char* startDate, const char* endDate);
    bool chceckRoom(const char* startDate, const char* endDate, const char* roomID);

};

#endif /* reservation_hpp */
