/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#include "ticks.h"


Ticks::Ticks ( void )
{
	_pc_start   = 0;
	_pc_end     = 0;
	_elapsed_ms = 0.0f;
}


Ticks::~Ticks ( void )
{
	// Nothing to see here.
}


void
Ticks::start ( void )
{
	_pc_start = SDL_GetPerformanceCounter ( );
}


void
Ticks::end ( void )
{
	do
	{
		_pc_end = SDL_GetPerformanceCounter ( );
		_elapsed_ms = ( double ) ( _pc_end - _pc_start ) / ( double ) SDL_GetPerformanceFrequency ( ) * 1000.0f;
	}
	while ( _elapsed_ms < ( double ) ( 1000.0f / ( double ) 60 ) );
}
