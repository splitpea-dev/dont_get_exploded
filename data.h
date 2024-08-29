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
#ifndef DATA_H
#define DATA_H


#include <iostream>
=======
#pragma once


#include <iostream>
#include <cstdint>
>>>>>>> 41dc873 (General refactoring.)
#include "defines.h"


class Data
{
	public:
<<<<<<< HEAD
	Data ( void );
	~Data ( void );

	void
	reset ( void );
	 
	void
	setDifficulty ( uint8_t setting );
	
	uint8_t
	getDifficulty ( void );
	
	uint8_t
	getNumberOfMines ( void );

	uint8_t
	getAvailableFlags ( void );
	
	bool
	setFlag ( void );
	
	bool
	restoreFlag ( void );

	void
	setMessage ( uint8_t message_id );
	
	uint8_t
	getMessage ( void );
=======
	Data(void);
	~Data(void);

	void
	reset(void);
	 
	void
	setDifficulty(uint8_t setting);
	
	uint8_t
	getDifficulty(void);
	
	uint8_t
	getNumberOfMines(void);

	uint8_t
	getAvailableFlags(void);
	
	bool
	setFlag(void);
	
	bool
	restoreFlag(void);

	void
	setMessage(uint8_t message_id);
	
	uint8_t
	getMessage(void);
>>>>>>> 41dc873 (General refactoring.)

	private:
	uint8_t _difficulty;
	uint8_t _number_of_mines;
	uint8_t _available_flags;
	uint8_t _message;
};
<<<<<<< HEAD


#endif
=======
>>>>>>> 41dc873 (General refactoring.)
