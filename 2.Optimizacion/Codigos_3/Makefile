CPPFLAGS=-Wall -Wextra -pedantic -DNDEBUG -DREPORT_MEM
CXXFLAGS=-O3 -flto
LDFLAGS=-flto

all: test1 test2 test3 test4

test1: Vector.o mem.o test1.o
	g++ $(LDFLAGS) Vector.o mem.o test1.o -o test1

test2: Vector.o mem.o test2.o
	g++ $(LDFLAGS) Vector.o mem.o test2.o -o test2

test3: Vector.o mem.o test3.o
	g++ $(LDFLAGS) Vector.o mem.o test3.o -o test3

test4: Vector.o mem.o test4.o
	g++ $(LDFLAGS) Vector.o mem.o test4.o -o test4

test1.o: test1.cpp Vector.h
	g++ $(CPPFLAGS) $(CXXFLAGS) -c test1.cpp

test2.o: test2.cpp Vector.h
	g++ $(CPPFLAGS) $(CXXFLAGS) -c test2.cpp

test3.o: test3.cpp Vector.h
	g++ $(CPPFLAGS) $(CXXFLAGS) -c test3.cpp

test4.o: test4.cpp Vector.h
	g++ $(CPPFLAGS) $(CXXFLAGS) -c test4.cpp
	
mem.o: mem.cpp mem.h
	g++ $(CPPFLAGS) $(CXXFLAGS) -c mem.cpp

Vector.o: Vector.cpp Vector.h mem.h
	g++ $(CPPFLAGS) $(CXXFLAGS) -c Vector.cpp

clean:
	rm -f Vector.o mem.o test1.o test2.o test3.o test4.o test1 test2 test3 test4
