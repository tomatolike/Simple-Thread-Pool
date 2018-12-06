CC=g++

test : test.cpp Thread_Pool.o
	$(CC) -o obj/test test.cpp obj/Thread_Pool.o

Thread_Pool.o : Thread_Pool.cpp Thread_Pool.h
	$(CC) -o obj/Thread_Pool.o -c Thread_Pool.cpp -std=c++11 -pthread

clean : 
	-rm obj/test obj/Thread_Pool.o
