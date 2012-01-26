all: cVector cLine cRectangle
	g++ -o lapper lapper.cpp cVector.o cRectangle.o cLine.o

cVector: cVector.h cVector.cpp
	g++ -c -o cVector.o cVector.cpp

cLine: cLine.h cLine.cpp
	g++ -c -o cLine.o cLine.cpp

cRectangle: cRectangle.h cRectangle.cpp
	g++ -c -o cRectangle.o cRectangle.cpp


clean:
	rm -Rf lapper
