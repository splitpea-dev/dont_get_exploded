//
// Don't Get Exploded!
// Copyright 2022 - 2024, Brian Puthuff
//
// See LICENSE.md for details.
//


#include <iostream>
#include <cstdlib>
#include <ctime>


#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


#include "game.hpp"


int8_t init_sdl(void);
void clean_up_sdl(void);


int main(int argc, char **argv)
{
	c_game game;


        if (init_sdl() < 0) {
		std::cerr << "Program terminated." << std::endl;
                return 1;
        }
	
	// initialize random seed
	srand(time(NULL));

	// instantiate game object and run
	game.init();
	game.play();

        clean_up_sdl();

	return 0;
}


int8_t init_sdl(void)
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Could not initialize SDL." << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		return -1;
	}
	// std::cout << "SDL initialized." << std::endl;

	// initialize SDL image
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cerr << "SDL Image could not initialize." << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		std::cerr << "Program terminated.\n";
		return -1;
	}
	// std::cout << "SDL image initialized." << std::endl;

        return 0;
}


void clean_up_sdl(void)
{
	IMG_Quit();
	SDL_Quit();
}

