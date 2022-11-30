# makefile
# updated: Wed Nov 23 11:35:06 PM PST 2022


# Don't Get Exploded!
# Copyright 2022, Brian Puthuff
#
# See LICENSE.md for details.


# files to compile
OBJECTS = main.cpp data.cpp input.cpp game.cpp graphics.cpp palettes.cpp playfield.cpp ticks.cpp

# compiler
CXX = g++

# compiler flags
FLAGS = -Wall -std=c++11

# linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image

#executable name
OUT = dge

all : $(OBJECTS)
	$(CXX) $(OBJECTS) $(FLAGS) $(LINKER_FLAGS) -o $(OUT)

clean :
	-rm $(OUT)


