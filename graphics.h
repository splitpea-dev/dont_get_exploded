/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#ifndef GRAPHICS_H
#define GRAPHICS_H


#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "playfield.h"
#include "data.h"
#include "defines.h"
#include "palettes.h"


class Graphics
{
	public:
	Graphics ( void );
	~Graphics ( void );
	
	void
	render ( Playfield *playfield, Data *data ); 	
	
	uint16_t
	getIntegerScaler ( void );
	
	void
	setPalette ( uint8_t palette_index );
	
	void
	prevPalette ( void );
	
	void
	nextPalette ( void );

	private:
	uint8_t _palette;
	uint16_t _scaler;
	Palettes *_palettes;
	SDL_Surface *_surface;
	SDL_Surface *_tiles_surface;
	SDL_Texture *_texture;
	SDL_Renderer *_renderer;
	SDL_Window *_window;
	SDL_Rect _clips [ 33 ];

	void
	initializeClips ( void );
	
	void
	renderPlayfield ( Playfield *playfield );
	
	void
	renderData ( Data *data );
	
	void
	clearRenderer ( void );
	
	void
	setIntegerScaler ( void );
	
	void
	initializeSurface ( SDL_Surface *src, SDL_Surface *dst );
	
	void
	displaySurfaceInformation ( SDL_Surface *surface );
	
	void
	copyToIndexedSurface ( SDL_Surface *source );
	
	void
	upgradeSurfaceAndStream ( void );
};


#endif
