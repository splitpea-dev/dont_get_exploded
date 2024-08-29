# makefile
# updated: Tue Aug 27 11:31:12 PM PDT 2024


# Don't Get Exploded!
# Copyright 2022 - 2024, Brian Puthuff
#
# See LICENSE.md for details.


# files to compile
SOURCE = ./source/main.cpp ./source/input.cpp ./source/game.cpp ./source/video.cpp ./source/playfield.cpp

# compiler
CXX = g++

# compiler flags
FLAGS = -Wall -std=c++11

# linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image

#executable name
OUT = dge

all : $(SOURCE)
	$(CXX) $(SOURCE) $(FLAGS) $(LINKER_FLAGS) -o $(OUT)

clean :
	rm $(OUT)


