#include <iostream>
#include "SDL2/SDL.h"
#include "game.h"

/* ....................... */
/* : Don't Get Exploded! : */
/* ::::::::::::::::::::::: */

// 

// window dimensions
const Uint16 window_width = 640;
const Uint16 window_height = 672;

int main(int argc, char** argv)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Could not initialize SDL.\n";
		std::cerr << SDL_GetError() << '\n';
		std::cerr << "Program terminated.\n";
		return 1;
	}

			
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_CreateWindowAndRenderer(window_width, window_height, SDL_WINDOW_SHOWN, &window, &renderer);
	if((window == NULL) || (renderer == NULL))
	{
		std::cerr << "Issue creeating SDL window and/or renderer.\n";
		std::cerr << SDL_GetError() << '\n';
		std::cerr << "Program terminated.\n";
		SDL_Quit();
		return 1;
	}

	// set window title
	SDL_SetWindowTitle(window, "Don't Get Exploded!");

	// initial renderer update
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	//	SDL_Surface* render_surface = SDL_GetWindowSurface(window);
	//	std::cout << render_surface->w << ", " << render_surface->h << '\n';
	SDL_Surface* tiles = SDL_LoadBMP("./tiles.bmp");

	if(tiles == NULL) 
	{
		std::cerr << "Issue loading assets.\n";
		std::cerr << SDL_GetError() << '\n';
		std::cerr << "Program terminated.\n";
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	
	Game game(window, renderer, tiles);
	game.play();

	SDL_FreeSurface(tiles);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
