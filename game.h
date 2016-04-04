#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "SDL2/SDL.h"
#include <utility>
#include <random>
#include <ctime>

// Don't Get Exploded!
// by Brian Puthuff

// game.h
// Updated: Sun Apr  3 01:21:56 PDT 2016

enum { EASY_PEASY, I_LIKE_IT_SPICY, WHY_SO_SERIOUS };

class Game
{
	public:
		Game(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* tiles);
		~Game();
		void play();
	private:
		int width;
		int height;
		
		// local pointers
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Surface* tiles;
		
		// internal mixing and painting
		SDL_Texture* render_texture;
		SDL_Surface* pixels;
		SDL_Surface* mix_surface_1;
		SDL_Surface* mix_surface_2;
		SDL_Surface* bg_surface;

		// map <lower, upper>
		std::pair<int, int> map[400];

		// key variables
		int correctly_placed_flags;
		int placed_flags;
		int mines;
		int difficulty;
		int current_message;

		// sprites (tiles)
		SDL_Rect sprites[33];

		// for radial gradient <1st color, 2nd color>
		std::pair<Uint32, Uint32> bg_colors[3];

		SDL_Event event;
		bool is_running;
		bool is_playing;
		bool got_exploded;

		// game functions
		void initialize(void);
		void generateMap();
		void renderWindow(void);
		void renderStats(void);
		void changeBackgroundColor(int index);
		void renderBackground(Uint32 color_1, Uint32 color_2);
		void flagCell(int cell);
		int sweepCell(int cell);
		void blurSurface(SDL_Surface* source, SDL_Surface* destination);
		void screenshot(void);
		int getTile(int x, int y);
};

#endif
