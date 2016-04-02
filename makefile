# makefile
# updated: Mon Mar 21 23:06:50 PDT 2016

# files to compile
OBJECTS = main.cpp game.cpp

# compiler
CXX = g++

# compiler flags
FLAGS = -Wall -std=c++11

# linker flags
LINKER_FLAGS = -lSDL2

#executable name
OUT = dge

all : $(OBJECTS)
	$(CXX) $(OBJECTS) $(FLAGS) $(LINKER_FLAGS) -o $(OUT)

clean :
	-rm $(OUT)


