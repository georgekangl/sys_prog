# Makefile
CXX = g++
DEBUG = -g
CFLAGS = -c -Wall
LFLAGS = -Wall
INCLUDES = -I .
OBJECTS = sys.o
.PHONY: all clean

all: sysProgram

sysProgram: $(OBJECTS)
	@echo "Building..."
	$(CXX) $(LFLAGS) $(INCLUDES) $(OBJECTS) -o sysProgram

sys.o: sys.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) sys.cpp

clean:
	@echo "Cleaning up ... "
	-rm sysProgram
	-rm $(OBJECTS)
	
