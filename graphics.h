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


class Graphics
{
	public:
	Graphics ( void );
	~Graphics ( void );
	
	void render ( Playfield *playfield, Data *data ); 	
	uint16_t getIntegerScaler ( void );

	private:
	uint16_t _scaler;
	SDL_Texture  *_texture;
	SDL_Renderer *_renderer;
	SDL_Window   *_window;
	SDL_Rect _clips [ 33 ];

	void initializeClips ( void );
	void renderPlayfield ( Playfield *playfield );
	void renderData ( Data *data );
	void clearRenderer ( void );
	void setIntegerScaler ( void );
};


#endif
