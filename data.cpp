/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#include "data.h"


Data::Data ( void )
{
	setDifficulty ( I_LIKE_IT_SPICY );
}


Data::~Data ( void )
{
	// Nothing to see here
}


uint8_t Data::getNumberOfMines ( void )
{
	return _number_of_mines;
}


uint8_t Data::getDifficulty ( void )
{
	return _difficulty;
}


void Data::setDifficulty ( uint8_t setting )
{
	if ( setting > WHY_SO_SERIOUS )
	{
		setting = WHY_SO_SERIOUS;
	}
	_difficulty = setting;

	switch ( _difficulty )
	{
		case EASY_PEASY:
			_number_of_mines = 30;
			break;
		case I_LIKE_IT_SPICY:
			_number_of_mines = 60;
			break;
		case WHY_SO_SERIOUS:
			_number_of_mines = 90;
			break;
	}
	reset ( );
}


void Data::reset ( void )
{
	_message = DONT_GET_EXPLODED;
	_available_flags = _number_of_mines;
}


uint8_t Data::getMessage ( void )
{
	return _message;
}


void Data::setMessage ( uint8_t setting )
{
	if ( setting > YOU_GOT_EXPLODED )
	{
		setting = YOU_GOT_EXPLODED;
	}
	_message = setting;
}


uint8_t Data::getAvailableFlags ( )
{
	return _available_flags;
}


bool Data::setFlag ( )
{
	if ( _available_flags > 0 )
	{
		_available_flags--;
		return true;
	}
	return false;
}


bool Data::restoreFlag ( void )
{
	if ( _available_flags < ( _number_of_mines - 1 ) )
	{
		_available_flags++;
		return true;
	}
	return false;
}
