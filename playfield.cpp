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


#include "playfield.h"


<<<<<<< HEAD
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
=======
Playfield::Playfield(uint8_t width, uint8_t height)
{
	assert(width > 0 && height > 0);
	_w = width;
	_h = height;
	_a = (uint16_t) _w * (uint16_t) _h;
	
	_cells = new Cell[_a];
	
	clearPlayfield();
}


Playfield::~Playfield(void)
>>>>>>> 41dc873 (General refactoring.)
{
	delete _cells;
}


void
<<<<<<< HEAD
Playfield::clearPlayfield ( void )
=======
Playfield::clearPlayfield(void)
>>>>>>> 41dc873 (General refactoring.)
{
	uint16_t i;


	// clear both layers
<<<<<<< HEAD
	for ( i = 0; i < _a; i++ )
	{
		_cells [ i ].above = DIRT;
		_cells [ i ].below = EMPTY;
=======
	for (i = 0; i < _a; i += 1) {
		_cells[i].above = DIRT;
		_cells[i].below = EMPTY;
>>>>>>> 41dc873 (General refactoring.)
	}
}


uint8_t
<<<<<<< HEAD
Playfield::getWidth ( void )
=======
Playfield::getWidth(void)
>>>>>>> 41dc873 (General refactoring.)
{
	return _w;
}


uint8_t
<<<<<<< HEAD
Playfield::getHeight ( void )
=======
Playfield::getHeight(void)
>>>>>>> 41dc873 (General refactoring.)
{
	return _h;
}


uint16_t
<<<<<<< HEAD
Playfield::getArea ( void )
=======
Playfield::getArea(void)
>>>>>>> 41dc873 (General refactoring.)
{
	return _a;
}


void
<<<<<<< HEAD
Playfield::generatePlayfield ( uint8_t x, uint8_t y, uint16_t number_of_mines )
=======
Playfield::generatePlayfield(uint8_t x, uint8_t y, uint16_t number_of_mines)
>>>>>>> 41dc873 (General refactoring.)
{
	uint16_t p;

	
<<<<<<< HEAD
	p = ( uint16_t ) ( ( y * _w ) + x ); 
	generatePlayfield ( p, number_of_mines );
=======
	p = (uint16_t) ((y * _w) + x); 
	generatePlayfield(p, number_of_mines);
>>>>>>> 41dc873 (General refactoring.)
}


void
<<<<<<< HEAD
Playfield::generatePlayfield ( uint16_t position, uint16_t number_of_mines )
=======
Playfield::generatePlayfield(uint16_t position, uint16_t number_of_mines)
>>>>>>> 41dc873 (General refactoring.)
{	
	uint16_t i;
	uint16_t r;

<<<<<<< HEAD
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
=======

	clearPlayfield();

	// add mines
	for (i = 0; i < number_of_mines; i += 1) {
		do {
			r = rand ( ) % _a;
		}
		while ((_cells[r].below > EMPTY) || (r == position));
		_cells[r].below = MINE;
	}
	
	addProximityCounts();
>>>>>>> 41dc873 (General refactoring.)
}


void
<<<<<<< HEAD
Playfield::addProximityCounts ( void )
=======
Playfield::addProximityCounts(void)
>>>>>>> 41dc873 (General refactoring.)
{
	uint8_t count;
	int16_t x;
	int16_t y;
	uint16_t i;

<<<<<<< HEAD
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
=======

	for (y = 0; y < _h; y += 1) {
		for (x = 0; x < _w; x += 1) {
			count = 0;
			i = (uint16_t) ((y * _w) + x);
		
			if (_cells[i].below == EMPTY) {
				count += mineCheck(x - 1, y - 1);
				count += mineCheck(x, y - 1);
				count += mineCheck(x + 1, y - 1);
				count += mineCheck(x - 1, y);
				count += mineCheck(x + 1, y);
				count += mineCheck(x - 1, y + 1);
				count += mineCheck(x, y + 1);
				count += mineCheck(x + 1, y + 1);
				_cells[i].below = count;
>>>>>>> 41dc873 (General refactoring.)
			}
		}
	}		
}


uint8_t
<<<<<<< HEAD
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
=======
Playfield::mineCheck(int16_t x, int16_t y)
{
	// out of bounds
	if ((x < 0) || (y < 0))
		return 0;

	// outof bounds
	if ((x >= _w) || (y >= _h))
		return 0;

	// in bounds check for mine
	if (_cells [((y * _w) + x)].below == MINE)
		return 1;
>>>>>>> 41dc873 (General refactoring.)

	return 0;
}


void
<<<<<<< HEAD
Playfield::explodePlayfield ( void )
=======
Playfield::explodePlayfield(void)
>>>>>>> 41dc873 (General refactoring.)
{
	uint16_t i;
	

<<<<<<< HEAD
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
=======
	for (i = 0; i < _a; i += 1) {
		if (_cells[i].above == FLAG) {
			if (_cells[i].below == MINE) {
				_cells[i].below = FLAGGED_MINE;
				_cells[i].above = EXPOSED;
			} else {
				_cells[i].above = INCORRECT_FLAG;
>>>>>>> 41dc873 (General refactoring.)
			}
		}
		
		// expose all hidden mines that were not flagged
<<<<<<< HEAD
		if ( _cells [ i ].above == DIRT )
		{
			if ( _cells [ i ].below == MINE )
			{
				_cells [ i ].above = EXPOSED;
			}
		}

=======
		if (_cells[i].above == DIRT) {
			if ( _cells[i].below == MINE)
				_cells[i].above = EXPOSED;
		}
>>>>>>> 41dc873 (General refactoring.)
	}
}


void
<<<<<<< HEAD
Playfield::printPlayfield ( void )
=======
Playfield::printPlayfield(void)
>>>>>>> 41dc873 (General refactoring.)
{
	uint8_t x;
	uint8_t y;
	uint16_t p;


<<<<<<< HEAD
	for ( y = 0; y < _h; y++ )
	{
		for ( x = 0; x < _w; x++ )
		{
			p = ( uint16_t ) ( ( y * _w ) + x );
			std::cout << ( int ) _cells [ p ].below;
=======
	for (y = 0; y < _h; y += 1) {
		for (x = 0; x < _w; x += 1) {
			p = (uint16_t) ((y * _w) + x);
			std::cout << (int) _cells[p].below;
>>>>>>> 41dc873 (General refactoring.)
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


uint8_t
<<<<<<< HEAD
Playfield::getAbove ( uint8_t x, uint8_t y )
=======
Playfield::getAbove(uint8_t x, uint8_t y)
>>>>>>> 41dc873 (General refactoring.)
{
	uint16_t p;


<<<<<<< HEAD
	assert ( x < _w );
	assert ( y < _h );
	p = ( ( y * _w ) + x );

	return getAbove ( p );
=======
	assert(x < _w);
	assert(y < _h );
	p = ((y * _w) + x);

	return getAbove(p);
>>>>>>> 41dc873 (General refactoring.)
}


uint8_t
<<<<<<< HEAD
Playfield::getAbove ( uint16_t position )
{
	assert ( position < _a );

	return _cells [ position ].above;
=======
Playfield::getAbove(uint16_t position)
{
	assert(position < _a);

	return _cells[position].above;
>>>>>>> 41dc873 (General refactoring.)
}


uint8_t
<<<<<<< HEAD
Playfield::getBelow ( uint8_t x, uint8_t y )
=======
Playfield::getBelow(uint8_t x, uint8_t y)
>>>>>>> 41dc873 (General refactoring.)
{
	uint16_t p;


<<<<<<< HEAD
	assert ( x < _w );
	assert ( y < _h );
	p = ( ( y * _w ) + x );

	return getBelow ( p );
=======
	assert(x < _w);
	assert(y < _h);
	p = ((y * _w) + x);

	return getBelow(p);
>>>>>>> 41dc873 (General refactoring.)
}


uint8_t
<<<<<<< HEAD
Playfield::getBelow ( uint16_t position )
{
	assert ( position < _a );

	return _cells [ position ].below;
=======
Playfield::getBelow(uint16_t position)
{
	assert(position < _a);

	return _cells[position].below;
>>>>>>> 41dc873 (General refactoring.)
}


void
<<<<<<< HEAD
Playfield::setAbove ( uint8_t x, uint8_t y, uint8_t type )
=======
Playfield::setAbove(uint8_t x, uint8_t y, uint8_t type)
>>>>>>> 41dc873 (General refactoring.)
{
	uint16_t p;


<<<<<<< HEAD
	assert ( x < _w );
	assert ( y < _h );
	p = ( ( y * _w ) + x );

	setAbove ( p, type );
=======
	assert(x < _w);
	assert(y < _h);
	p = ((y * _w) + x);

	setAbove(p, type);
>>>>>>> 41dc873 (General refactoring.)
}


void
<<<<<<< HEAD
Playfield::setAbove ( uint16_t position, uint8_t type )
{
	assert ( position < _a );
	if ( type > INCORRECT_FLAG )
	{
		type = INCORRECT_FLAG;
	}

	_cells [ position ].above = type;
=======
Playfield::setAbove(uint16_t position, uint8_t type)
{
	assert(position < _a);
	if (type > INCORRECT_FLAG)
		type = INCORRECT_FLAG;

	_cells[position].above = type;
>>>>>>> 41dc873 (General refactoring.)
}


void
<<<<<<< HEAD
Playfield::setBelow ( uint8_t x, uint8_t y, uint8_t type )
=======
Playfield::setBelow(uint8_t x, uint8_t y, uint8_t type)
>>>>>>> 41dc873 (General refactoring.)
{	
	uint16_t p;


<<<<<<< HEAD
	assert ( x < _w );
	assert ( y < _h );
	p = ( ( y * _w ) + x );

	setBelow ( p, type );
=======
	assert(x < _w);
	assert(y < _h);
	p = ((y * _w) + x);

	setBelow(p, type);
>>>>>>> 41dc873 (General refactoring.)
}


void
<<<<<<< HEAD
Playfield::setBelow ( uint16_t position, uint8_t type )
{
	assert ( position < _a );
	if ( type > EXPLODED_MINE )
	{
		type = EXPLODED_MINE;
	}

	_cells [ position ].below = type;
=======
Playfield::setBelow(uint16_t position, uint8_t type)
{
	assert(position < _a);
	if (type > EXPLODED_MINE)
		type = EXPLODED_MINE;

	_cells[position].below = type;
>>>>>>> 41dc873 (General refactoring.)
}

