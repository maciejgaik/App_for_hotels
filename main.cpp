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
        if(myBase.newGuest("Maciej", "Gaik", "664754254", "Poland", "97500", "Radomsko", "Klekotowe", "11", "0", "23.03.2019")){
            std::cout<<"Pomysle dodano goscia"<<std::endl;
        }else{
            std::cout<<"Istnieje juz gosc o takich danych"<<std::endl;
        }
    }
    else{
        std::cout<<"BLAD POLACZENIA: " << myBase.getErrorNumber() <<std::endl;
    }
    
    return 0;
}
