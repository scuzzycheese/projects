CC = g++
CARGS = -g3
COBJ = -c

CCBUILD = $(CC) $(CARGS)
CCBUILDOBJ = $(CCBUILD) $(COBJ)

OBJECTS = cParseFromFile.o

all: $(OBJECTS)
	$(CCBUILD) -o amLines main.cpp $(OBJECTS)

%.o: %.h %.cpp
	$(CCBUILDOBJ) -o $*.o $*.cpp

clean:
	rm -Rf amLines
	rm -Rf $(OBJECTS)
