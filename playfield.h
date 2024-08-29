/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


<<<<<<< HEAD
#ifndef PLAYFIELD_H
#define PLAYFIELD_H


#include <iostream>
=======
#pragma once


#include <iostream>
#include <cstdint>
>>>>>>> 41dc873 (General refactoring.)
#include <cassert>
#include "defines.h"


class Cell
{
	public:
	uint8_t above;
	uint8_t below;
};


class Playfield
{
	public:
<<<<<<< HEAD
	Playfield ( uint8_t width, uint8_t height );
	~Playfield ( void );
	
	void
	clearPlayfield ( void );
	
	void
	generatePlayfield ( uint8_t x, uint8_t y, uint16_t number_of_mines );
	
	void
	generatePlayfield ( uint16_t position, uint16_t number_of_mines );
	
	void
	explodePlayfield ( void );
	
	uint8_t
	getAbove ( uint8_t x, uint8_t y );
	
	uint8_t
	getAbove ( uint16_t position );
	
	uint8_t
	getBelow ( uint8_t x, uint8_t y );
	
	uint8_t
	getBelow ( uint16_t position );
	
	void
	setAbove ( uint8_t x, uint8_t y, uint8_t type );
	
	void
	setAbove ( uint16_t position, uint8_t type );
	
	void
	setBelow ( uint8_t x, uint8_t y, uint8_t type );
	
	void
	setBelow ( uint16_t position, uint8_t type );
	
	void
	printPlayfield ( void );
	
	uint8_t
	getWidth ( void );
	
	uint8_t
	getHeight ( void );
	
	uint16_t
	getArea ( void );
=======
	Playfield(uint8_t width, uint8_t height);
	~Playfield(void);
	
	void
	clearPlayfield(void);
	
	void
	generatePlayfield(uint8_t x, uint8_t y, uint16_t number_of_mines);
	
	void
	generatePlayfield(uint16_t position, uint16_t number_of_mines);
	
	void
	explodePlayfield(void);
	
	uint8_t
	getAbove(uint8_t x, uint8_t y);
	
	uint8_t
	getAbove(uint16_t position);
	
	uint8_t
	getBelow(uint8_t x, uint8_t y);
	
	uint8_t
	getBelow(uint16_t position);
	
	void
	setAbove(uint8_t x, uint8_t y, uint8_t type);
	
	void
	setAbove(uint16_t position, uint8_t type);
	
	void
	setBelow(uint8_t x, uint8_t y, uint8_t type);
	
	void
	setBelow(uint16_t position, uint8_t type);
	
	void
	printPlayfield(void);
	
	uint8_t
	getWidth(void);
	
	uint8_t
	getHeight(void);
	
	uint16_t
	getArea(void);
>>>>>>> 41dc873 (General refactoring.)

	private:
	uint8_t _w;
	uint8_t _h;
	uint16_t _a;
	Cell *_cells;

	void
<<<<<<< HEAD
	addProximityCounts ( void );
	
	uint8_t
	mineCheck ( int16_t x, int16_t y );
};


#endif
=======
	addProximityCounts(void);
	
	uint8_t
	mineCheck(int16_t x, int16_t y);
};
>>>>>>> 41dc873 (General refactoring.)
