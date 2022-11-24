/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#ifndef TICKS_H
#define TICKS_H


#include <iostream>
#include "SDL2/SDL.h"


class Ticks
{
	public:
	Ticks      ( void );
	~Ticks     ( void );

	void start ( void );
	void end   ( void );

	private:
	uint64_t _pc_start;
	uint64_t _pc_end;
	double   _elapsed_ms;
};


#endif
