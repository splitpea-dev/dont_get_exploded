#ifndef PALETTE_H
#define PALETTE_H


#include <iostream>
#include <vector>
#include <fstream>
#include "SDL2/SDL.h"


class Palettes
{
	public:
	Palettes ( uint8_t palettes_count, uint8_t colors_count );
	~Palettes ( );

	SDL_Color *
	getPalette ( uint8_t palette_index );
	
	SDL_Color *
	getColor ( uint8_t palette_index, uint8_t color_index );
	
	uint8_t
	getRed ( uint8_t palette_index, uint8_t color_index );
	
	uint8_t
	getBlue ( uint8_t palette_index, uint8_t color_index );
	
	uint8_t
	getGreen ( uint8_t palette_index, uint8_t color_index );
	
	uint8_t
	getPaletteCount ( void );
	
	uint8_t
	getColorCount ( void );
	
	void
	setRGB ( uint8_t palette_index, uint8_t color_index, uint8_t r, uint8_t g, uint8_t b );
	
	int8_t
	load ( const char *filename );

	private:
	uint8_t
	getColorValueFromHexChars ( FILE *file );

	void
	setDefaultPalettes ( void );

	uint8_t _palettes_count;
	uint8_t _colors_count;
	std::vector<SDL_Palette *> _palettes;
};


#endif
