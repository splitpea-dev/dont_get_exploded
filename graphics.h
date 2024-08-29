/*
** Don't Get Exploded!
<<<<<<< HEAD
** Copyright 2022, Brian Puthuff
=======
** Copyright 2022 - 2024, Brian Puthuff
>>>>>>> 41dc873 (General refactoring.)
**
** See LICENSE.md for details.
*/


<<<<<<< HEAD
#ifndef GRAPHICS_H
#define GRAPHICS_H
=======
#pragma once
>>>>>>> 41dc873 (General refactoring.)


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
<<<<<<< HEAD
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
=======
	Graphics(void);
	~Graphics(void);
	
	void
	render(Playfield *playfield, Data *data); 	
	
	uint16_t
	getIntegerScaler(void);
	
	void
	setPalette(uint8_t palette_index);
	
	void
	prevPalette(void);
	
	void
	nextPalette(void);
>>>>>>> 41dc873 (General refactoring.)

	private:
	uint8_t _palette;
	uint16_t _scaler;
	Palettes *_palettes;
	SDL_Surface *_surface;
	SDL_Surface *_tiles_surface;
	SDL_Texture *_texture;
	SDL_Renderer *_renderer;
	SDL_Window *_window;
<<<<<<< HEAD
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
=======
	SDL_Rect _clips[33];

	void
	initializeClips(void);
	
	void
	renderPlayfield(Playfield *playfield);
	
	void
	renderData(Data *data);
	
	void
	clearRenderer(void);
	
	void
	setIntegerScaler(void);
	
	void
	initializeSurface(SDL_Surface *src, SDL_Surface *dst);
	
	void
	displaySurfaceInformation(SDL_Surface *surface);
	
	void
	copyToIndexedSurface(SDL_Surface *source);
	
	void
	upgradeSurfaceAndStream(void);
};

>>>>>>> 41dc873 (General refactoring.)
