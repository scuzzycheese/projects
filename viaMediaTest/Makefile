CC = g++
CARGS = -g
COBJ = -c

CCBUILD = $(CC) $(CARGS)
CCBUILDOBJ = $(CCBUILD) $(COBJ)

OBJECTS = cVector.o cShape.o cParser.o cRectangle.o

all: $(OBJECTS)
	$(CCBUILD) -o lapper lapper.cpp $(OBJECTS)

%.o: %.h %.cpp
	$(CCBUILDOBJ) -o $*.o $*.cpp

clean:
	rm -Rf lapper
	rm -Rf $(OBJECTS)
