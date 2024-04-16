CC:=gcc
CCFLAGS:=-g -I.
CPP:=g++
CPPFLAGS:=-g -I.

adt_list.o: adt_list.c adt_list.h
	$(CC) $(CCFLAGS) -c adt_list.c

test_99.o: test_99.cpp adt_list.h adt_list.o
	$(CPP) $(CPPFLAGS) -c test_99.cpp

test_99: test_99.o adt_list.o
	$(CPP) $(CCFLAGS) adt_list.o test_99.o -lm -lgtest -lgtest_main -o test_99

check: test_99
	./test_99

clean:
	rm -rf  adt_list.o
	rm -rf test_99.o
	rm -rf test_99
