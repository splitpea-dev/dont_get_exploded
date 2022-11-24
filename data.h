/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#ifndef DATA_H
#define DATA_H


#include <iostream>
#include "defines.h"


class Data
{
	public:
	Data ( void );
	~Data ( void );

	void reset ( void );
	
	// difficulty settings 
	void setDifficulty ( uint8_t setting );
	uint8_t getDifficulty ( void );
	uint8_t getNumberOfMines ( void ); // set by difficulty

	// flag business
	uint8_t getAvailableFlags ( void ); // initially set by difficulty
	bool setFlag ( void ); // subtracts from remaining
	bool restoreFlag ( void ); // adds to remaining

	// display message
	void setMessage ( uint8_t message_id );
	uint8_t getMessage ( void );

	private:
	uint8_t _difficulty;
	uint8_t _number_of_mines;
	uint8_t _available_flags;
	uint8_t _message;
};


#endif
