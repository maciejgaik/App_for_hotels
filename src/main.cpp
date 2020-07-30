//
//  main.cpp
//  database
//
//  Created by Maciej Gaik on 20/07/2020.
//  Copyright © 2020 Maciej Gaik. All rights reserved.
//

#include <iostream>
#include "base.hpp"

int main(int argc, const char * argv[]) {
    base myBase;
    if(myBase.connect()){
        std::cout<<"POLACZONO Z BAZA!"<<std::endl;
        try{
            myBase.new_reser_for_new_guest("Maciej", "Gaik", "664754254", "Poland", "97500", "Radomsko", "Klekotowe", "11", "0", "2021-04-12", "2021-04-11", "1");
        }catch(my_error err){
            switch(err){
                case my_error::QUERY_ERROR: std::cout<<"Zle zapytanie"<<std::endl;
                case my_error::DATE_ERROR: std::cout<<"Zla data"<<std::endl;
                case my_error::ROOM_RESERVED: std::cout<<"Pokoj zajety"<<std::endl;
            }
        }
        //std::cout<<std::endl<<myBase.reservation.calcNights(myBase.reservation.getDate("20.03.2020"), myBase.reservation.getDate("25.03.2020"));
    }
    else{
        std::cout<<"BLAD POLACZENIA: " << myBase.getErrorNumber() <<std::endl;
    }
        
    return 0;
}


