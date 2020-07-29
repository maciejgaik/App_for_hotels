FALGS=-Wall -pedantic -g -I/usr/local/mysql/include -L/usr/local/mysql/lib -Iinc -lz -lm -lmysqlclient -std=c++17

prog: obj src/main.cpp obj/base.o obj/guest.o obj/employee.o obj/reservation.o
	g++ -o prog ${FALGS} src/main.cpp obj/base.o obj/guest.o obj/employee.o obj/reservation.o

obj:
	mkdir -p obj

obj/base.o: src/base.cpp inc/base.hpp
	g++ -c ${FALGS} -o obj/base.o src/base.cpp

obj/guest.o: src/guest.cpp inc/guest.hpp
	g++ -c ${FALGS} -o obj/guest.o src/guest.cpp

obj/reservation.o: src/reservation.cpp inc/reservation.hpp
	g++ -c ${FALGS} -o obj/reservation.o src/reservation.cpp

obj/employee.o: src/employee.cpp inc/employee.hpp
	g++ -c ${FALGS} -o obj/employee.o src/employee.cpp

clean:
	rm -f obj/*.o prog