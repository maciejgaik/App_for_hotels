//
//  employee.hpp
//  database
//
//  Created by Maciej Gaik on 29/07/2020.
//  Copyright © 2020 Maciej Gaik. All rights reserved.
//

#ifndef employee_hpp
#define employee_hpp

#include <iostream>
#include <mysql.h>
#include <ctime>
#include <cstring>
#include <ctime>

class employee{
    MYSQL* mysql;
public:
    employee(MYSQL* _mysql) : mysql{_mysql} {}
    bool newEmployee();
    bool findEmployee();
};

#endif /* employee_hpp */
