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
#include "my_error.hpp"

enum class error{
    QUERY_ERROR
};

class Reservation{
    MYSQL* mysql;
public:
    void init(MYSQL* _mysql){ mysql = _mysql; };
    bool new_reservation(const char* start_date, const char* end_date, const char* room_ID, unsigned guest_ID);
    struct tm* get_date(const char* date);
    bool comapre_date(struct tm* date1, struct tm* date2);
    bool check_date(const char* start_date, const char* end_date);
    bool check_room(const char* start_date, const char* end_date, const char* room_ID);
    unsigned get_new_ID(const char *table);
    unsigned calc_nights(struct tm* date1, struct tm* date2);
};

#endif /* reservation_hpp */
