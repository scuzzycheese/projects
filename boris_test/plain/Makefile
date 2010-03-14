CC = g++
OPTIONS = -O0 -Wall -D BUFF_DEBUG

OBS = cBuffer.o cDStore.o cBufferContig.o 

all: $(OBS)
	$(CC) $(OPTIONS) $(OBS) test.cpp -o test

cBuffer.o: cBuffer.cpp cBuffer.h
	$(CC) $(OPTIONS) -c -o cBuffer.o cBuffer.cpp

cBufferContig.o: cBufferContig.cpp cBufferContig.h
	$(CC) $(OPTIONS) -c -o cBufferContig.o cBufferContig.cpp

cDStore.o: cDStore.cpp cDStore.h
	$(CC) $(OPTIONS) -c -o cDStore.o cDStore.cpp

	
clean:
	rm -Rf *.o
	rm -Rf test

	
