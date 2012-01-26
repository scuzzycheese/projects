all: cVector cLine cShape cParser cRectangle
	g++ -o lapper lapper.cpp cVector.o cShape.o cLine.o cParser.o cRectangle.o

cVector: cVector.h cVector.cpp
	g++ -c -o cVector.o cVector.cpp

cLine: cLine.h cLine.cpp
	g++ -c -o cLine.o cLine.cpp

cShape: cShape.h cShape.cpp
	g++ -c -o cShape.o cShape.cpp

cParser: cParser.h cParser.cpp
	c++ -c -o cParser.o cParser.cpp

cRectangle: cRectangle.h cRectangle.cpp
	c++ -c -o cRectangle.o cRectangle.cpp


clean:
	rm -Rf lapper
