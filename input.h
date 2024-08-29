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
#ifndef INPUT_H
#define INPUT_H
=======
#pragma once
>>>>>>> 41dc873 (General refactoring.)


#include <iostream>
#include "SDL2/SDL.h"
#include "defines.h"


class Input
{
	public:
<<<<<<< HEAD
	Input ( void );
	~Input ( void );

	void
	setScaleFlag ( bool flip );
	
	void
	update ( void );
	
	void
	resetFlags ( void );
	
	bool
	isSet ( uint8_t trigger );
	
	int16_t
	getMouseX ( void );
	
	int16_t
	getMouseY ( void );
	
	uint16_t
	getTileX ( void );
	
	uint16_t
	getTileY ( void );
	
	bool
	isMouseInBounds ( uint16_t x, uint16_t y, uint16_t w, uint16_t h );
=======
	Input(void);
	~Input(void);

	void
	setScaleFlag(bool flip);
	
	void
	update (void);
	
	void
	resetFlags(void);
	
	bool
	isSet(uint8_t trigger);
	
	int16_t
	getMouseX(void);
	
	int16_t
	getMouseY(void);
	
	uint16_t
	getTileX(void);
	
	uint16_t
	getTileY(void);
	
	bool
	isMouseInBounds(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
>>>>>>> 41dc873 (General refactoring.)

	private:
	bool _flag_2x;
	bool _flag_exit;
	bool _flag_f1;
	bool _flag_f2;
	bool _flag_f3;
	bool _flag_f9;
	bool _flag_tab;
	bool _flag_comma;
	bool _flag_period;
	bool _mouse_button_left;
	bool _mouse_button_right;
	int16_t _mouse_x;
	int16_t _mouse_y;
};

<<<<<<< HEAD

#endif
=======
>>>>>>> 41dc873 (General refactoring.)
