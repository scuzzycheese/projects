CC = g++
CARGS = -g
COBJ = -c

CCBUILD = $(CC) $(CARGS)
CCBUILDOBJ = $(CCBUILD) $(COBJ)

OBJECTS = cVector.o cLine.o cShape.o cParser.o cRectangle.o

all: $(OBJECTS)
	$(CCBUILD) -o lapper lapper.cpp cVector.o cShape.o cLine.o cParser.o cRectangle.o

%.o: %.h %.cpp
	$(CCBUILDOBJ) -o $*.o $*.cpp

clean:
	rm -Rf lapper
	rm -Rf $(OBJECTS)
