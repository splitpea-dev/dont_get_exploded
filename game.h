/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#ifndef GAME_H
#define GAME_H


#include <iostream>
#include "SDL2/SDL.h"
#include "data.h"
#include "defines.h"
#include "input.h"
#include "graphics.h"
#include "playfield.h"
#include "ticks.h"


class Game
{
	public:
	Game ( void );
	~Game ( void );
	
	void play ( void );
	
	private:
	uint8_t _state;
	uint8_t _correct_flags;
	Data *_data;
	Input *_input;
	Graphics  *_graphics;
	Playfield *_playfield;
	Ticks *_ticks;

	uint8_t handleLeftClick ( void );
	void handleRightClick ( void );
	void checkFunctionResets ( void );
	void sweep ( int16_t x, int16_t y );
	void calculateCorrectFlags ( void );
	bool isWin ( void );
	void explode ( void );
	void victory ( void );
};


#endif
