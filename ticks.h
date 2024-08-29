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
#ifndef TICKS_H
#define TICKS_H
=======
#pragma once
>>>>>>> 41dc873 (General refactoring.)


#include <iostream>
#include "SDL2/SDL.h"


class Ticks
{
	public:
<<<<<<< HEAD
	Ticks      ( void );
	~Ticks     ( void );

	void
	start ( void );
	
	void
	end ( void );
=======
	Ticks(void);
	~Ticks(void);

	void
	start(void);
	
	void
	end(void);
>>>>>>> 41dc873 (General refactoring.)

	private:
	uint64_t _pc_start;
	uint64_t _pc_end;
<<<<<<< HEAD
	double   _elapsed_ms;
};


#endif
=======
	double _elapsed_ms;
};

>>>>>>> 41dc873 (General refactoring.)
