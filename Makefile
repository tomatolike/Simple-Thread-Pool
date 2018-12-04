CC=g++

test : test.cpp Thread_Pool.o
	$(CC) -o test test.cpp Thread_Pool.o

Thread_Pool.o : Thread_Pool.cpp Thread_Pool.h
	$(CC) -c Thread_Pool.cpp

clean : 
	-rm test Thread_Pool.o
