CC = g++
CARGS = -g
COBJ = -c

CCBUILD = $(CC) $(CARGS)
CCBUILDOBJ = $(CCBUILD) $(COBJ)

OBJECTS = cVector.o cShape.o cParserFromFile.o cParse.o cRectangle.o cLineRep.o

all: $(OBJECTS)
	$(CCBUILD) -o lapper lapper.cpp $(OBJECTS)

%.o: %.h %.cpp
	$(CCBUILDOBJ) -o $*.o $*.cpp

clean:
	rm -Rf lapper
	rm -Rf $(OBJECTS)
