/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "game.h"


<<<<<<< HEAD
int main ( int argc, char **argv )
{
	// game object
	Game *game;

	// initialize SDL
	if ( SDL_Init ( SDL_INIT_EVERYTHING ) < 0 )
	{
=======
int main(int argc, char **argv)
{
	Game *game;


	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
>>>>>>> 41dc873 (General refactoring.)
		std::cerr << "Could not initialize SDL." << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		std::cerr << "Program terminated." << std::endl;
		return 1;
	}
	// std::cout << "SDL initialized." << std::endl;

	// initialize SDL image
<<<<<<< HEAD
	if ( IMG_Init ( IMG_INIT_PNG ) != IMG_INIT_PNG )
	{
		std::cerr << "SDL Image could not initialize." << std::endl;
		std::cerr << SDL_GetError ( ) << std::endl;
		std::cerr << "Program terminated.\n";
		SDL_Quit ( );
		return 1;
	}
	// std::cout << "SDL image initialized." << std::endl;
	
	// initialize random seed
	srand ( time ( NULL ) );

	// instantiate game object and run
	game = new Game ( );
	game->play ( );

	// free up memory
	delete game;
	IMG_Quit ( );
	SDL_Quit ( );
=======
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cerr << "SDL Image could not initialize." << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		std::cerr << "Program terminated.\n";
		SDL_Quit();
		return 1;
	}
	
	// initialize random seed
	srand(time(NULL));

	// instantiate game object and run
	game = new Game();
	game->play();

	// free up memory
	delete game;
	IMG_Quit();
	SDL_Quit();
>>>>>>> 41dc873 (General refactoring.)

	return 0;
}
