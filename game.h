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
#ifndef GAME_H
#define GAME_H
=======
#pragma once

>>>>>>> 41dc873 (General refactoring.)


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
<<<<<<< HEAD
	Game ( void );
	~Game ( void );
	
	void
	play ( void );
=======
	Game(void);
	~Game(void);
	
	void
	play(void);
>>>>>>> 41dc873 (General refactoring.)
	
	private:
	uint8_t _state;
	uint8_t _correct_flags;
	Data *_data;
	Input *_input;
	Graphics  *_graphics;
	Playfield *_playfield;
	Ticks *_ticks;

	void
<<<<<<< HEAD
	handlePaletteChange ( void );
	
	uint8_t
	handleLeftClick ( void );
	
	void
	handleRightClick ( void );
	
	void
	checkFunctionResets ( void );
	
	void
	sweep ( int16_t x, int16_t y );
	
	void
	calculateCorrectFlags ( void );
	
	bool
	isWin ( void );
	
	void
	explode ( void );
	
	void
	victory ( void );
};


#endif
=======
	handlePaletteChange(void);
	
	uint8_t
	handleLeftClick(void);
	
	void
	handleRightClick(void);
	
	void
	checkFunctionResets(void);
	
	void
	sweep(int16_t x, int16_t y);
	
	void
	calculateCorrectFlags(void);
	
	bool
	isWin(void);
	
	void
	explode (void);
	
	void
	victory (void);
};
>>>>>>> 41dc873 (General refactoring.)
