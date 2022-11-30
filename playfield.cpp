/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#include "playfield.h"


Playfield::Playfield ( uint8_t width, uint8_t height )
{
	assert ( width > 0 && height > 0 );
	_w = width;
	_h = height;
	_a = ( uint16_t ) _w * ( uint16_t ) _h;
	
	_cells = new Cell [ _a ];
	
	clearPlayfield ( );
}


Playfield::~Playfield ( void )
{
	delete _cells;
}


void
Playfield::clearPlayfield ( void )
{
	uint16_t i;


	// clear both layers
	for ( i = 0; i < _a; i++ )
	{
		_cells [ i ].above = DIRT;
		_cells [ i ].below = EMPTY;
	}
}


uint8_t
Playfield::getWidth ( void )
{
	return _w;
}


uint8_t
Playfield::getHeight ( void )
{
	return _h;
}


uint16_t
Playfield::getArea ( void )
{
	return _a;
}


void
Playfield::generatePlayfield ( uint8_t x, uint8_t y, uint16_t number_of_mines )
{
	uint16_t p;

	
	p = ( uint16_t ) ( ( y * _w ) + x ); 
	generatePlayfield ( p, number_of_mines );
}


void
Playfield::generatePlayfield ( uint16_t position, uint16_t number_of_mines )
{	
	uint16_t i;
	uint16_t r;

	clearPlayfield ( );

	// add mines
	for ( i = 0; i < number_of_mines; i++ )
	{
		do
		{
			r = rand ( ) % _a;
		}
		while ( ( _cells [ r ].below > EMPTY ) || ( r == position ) );
		_cells [ r ].below = MINE;
	}
	
	addProximityCounts ( );
}


void
Playfield::addProximityCounts ( void )
{
	uint8_t count;
	int16_t x;
	int16_t y;
	uint16_t i;

	for ( y = 0; y < _h; y++ )
	{
		for ( x = 0; x < _w; x++ )
		{
			count = 0;
			i = ( uint16_t ) ( ( y * _w ) + x );
		
			if ( _cells [ i ].below == EMPTY )
			{
				count += mineCheck ( x - 1, y - 1 );
				count += mineCheck ( x, y - 1 );
				count += mineCheck ( x + 1, y - 1 );
				count += mineCheck ( x - 1, y );
				count += mineCheck ( x + 1, y );
				count += mineCheck ( x - 1, y + 1 );
				count += mineCheck ( x, y + 1 );
				count += mineCheck ( x + 1, y + 1 );
				_cells [ i ].below = count;
			}
		}
	}		
}


uint8_t
Playfield::mineCheck ( int16_t x, int16_t y )
{
	// out of bounds
	if ( ( x < 0 ) || ( y < 0 ) )
	{
		return 0;
	}

	// outof bounds
	if ( ( x >= _w ) || ( y >= _h ) )
	{
		return 0;
	}

	// in bounds check for mine
	if ( _cells [ ( ( y * _w ) + x ) ].below == MINE )
	{
		return 1;
	}

	return 0;
}


void
Playfield::explodePlayfield ( void )
{
	uint16_t i;
	

	for ( i = 0; i < _a; i++ )
	{
		if ( _cells [ i ].above == FLAG )
		{
			if ( _cells [ i ].below == MINE )
			{
				_cells [ i ].below = FLAGGED_MINE;
				_cells [ i ].above = EXPOSED;
			}
			else
			{
				_cells [ i ].above = INCORRECT_FLAG;
			}
		}
		
		// expose all hidden mines that were not flagged
		if ( _cells [ i ].above == DIRT )
		{
			if ( _cells [ i ].below == MINE )
			{
				_cells [ i ].above = EXPOSED;
			}
		}

	}
}


void
Playfield::printPlayfield ( void )
{
	uint8_t x;
	uint8_t y;
	uint16_t p;


	for ( y = 0; y < _h; y++ )
	{
		for ( x = 0; x < _w; x++ )
		{
			p = ( uint16_t ) ( ( y * _w ) + x );
			std::cout << ( int ) _cells [ p ].below;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


uint8_t
Playfield::getAbove ( uint8_t x, uint8_t y )
{
	uint16_t p;


	assert ( x < _w );
	assert ( y < _h );
	p = ( ( y * _w ) + x );

	return getAbove ( p );
}


uint8_t
Playfield::getAbove ( uint16_t position )
{
	assert ( position < _a );

	return _cells [ position ].above;
}


uint8_t
Playfield::getBelow ( uint8_t x, uint8_t y )
{
	uint16_t p;


	assert ( x < _w );
	assert ( y < _h );
	p = ( ( y * _w ) + x );

	return getBelow ( p );
}


uint8_t
Playfield::getBelow ( uint16_t position )
{
	assert ( position < _a );

	return _cells [ position ].below;
}


void
Playfield::setAbove ( uint8_t x, uint8_t y, uint8_t type )
{
	uint16_t p;


	assert ( x < _w );
	assert ( y < _h );
	p = ( ( y * _w ) + x );

	setAbove ( p, type );
}


void
Playfield::setAbove ( uint16_t position, uint8_t type )
{
	assert ( position < _a );
	if ( type > INCORRECT_FLAG )
	{
		type = INCORRECT_FLAG;
	}

	_cells [ position ].above = type;
}


void
Playfield::setBelow ( uint8_t x, uint8_t y, uint8_t type )
{	
	uint16_t p;


	assert ( x < _w );
	assert ( y < _h );
	p = ( ( y * _w ) + x );

	setBelow ( p, type );
}


void
Playfield::setBelow ( uint16_t position, uint8_t type )
{
	assert ( position < _a );
	if ( type > EXPLODED_MINE )
	{
		type = EXPLODED_MINE;
	}

	_cells [ position ].below = type;
}

