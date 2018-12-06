CC=g++

all : obj/test obj/Thread_Pool.o

obj/test : test.cpp obj/Thread_Pool.o
	$(CC) -o obj/test test.cpp obj/Thread_Pool.o -std=c++11 -pthread

obj/Thread_Pool.o : Thread_Pool.cpp Thread_Pool.h
	$(CC) -o obj/Thread_Pool.o -c Thread_Pool.cpp

clean : 
	-rm obj/test obj/Thread_Pool.o
