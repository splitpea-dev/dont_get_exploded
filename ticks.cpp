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


#include "ticks.h"


<<<<<<< HEAD
Ticks::Ticks ( void )
=======
Ticks::Ticks(void)
>>>>>>> 41dc873 (General refactoring.)
{
	_pc_start   = 0;
	_pc_end     = 0;
	_elapsed_ms = 0.0f;
}


<<<<<<< HEAD
Ticks::~Ticks ( void )
=======
Ticks::~Ticks(void)
>>>>>>> 41dc873 (General refactoring.)
{
	// Nothing to see here.
}


void
<<<<<<< HEAD
Ticks::start ( void )
{
	_pc_start = SDL_GetPerformanceCounter ( );
=======
Ticks::start(void)
{
	_pc_start = SDL_GetPerformanceCounter();
>>>>>>> 41dc873 (General refactoring.)
}


void
<<<<<<< HEAD
Ticks::end ( void )
{
	do
	{
		_pc_end = SDL_GetPerformanceCounter ( );
		_elapsed_ms = ( double ) ( _pc_end - _pc_start ) / ( double ) SDL_GetPerformanceFrequency ( ) * 1000.0f;
	}
	while ( _elapsed_ms < ( double ) ( 1000.0f / ( double ) 60 ) );
=======
Ticks::end(void)
{
	do {
		_pc_end = SDL_GetPerformanceCounter();
		_elapsed_ms = (double) (_pc_end - _pc_start) / (double) SDL_GetPerformanceFrequency() * 1000.0f;
	} while (_elapsed_ms < (double) (1000.0f / (double) 60));
>>>>>>> 41dc873 (General refactoring.)
}
