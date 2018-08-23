CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -Wno-long-long -O0 -ggdb

all: compile doc

compile: main.o CUserInterface.o CCalendar.o CEvent.o CDateAndTime.o
	$(CC) $(CFLAGS) main.o CUserInterface.o CCalendar.o CEvent.o CDateAndTime.o -o pernyond

main.o:
	$(CC) $(CFLAGS) -c src/main.cpp -o main.o

CUserInterface.o:
	$(CC) $(CFLAGS) -c src/CUserInterface.cpp -o CUserInterface.o

CCalendar.o:
	$(CC) $(CFLAGS) -c src/CCalendar.cpp -o CCalendar.o

CEvent.o:
	$(CC) $(CFLAGS) -c src/CEvent.cpp -o CEvent.o

CDateAndTime.o:
	$(CC) $(CFLAGS) -c src/CDateAndTime.cpp -o CDateAndTime.o

clean:
	rm -rf doc *.o doc ./pernyond

doc:
	doxygen Doxyfile

run:
	./pernyond
