/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#include "game.h"


Game::Game ( void )
{
	// instantiate things ...
	_data = new Data ( );
	_input = new Input ( );
	_graphics = new Graphics ( );
	_playfield = new Playfield ( PLAYFIELD_WIDTH, PLAYFIELD_HEIGHT );
	_ticks = new Ticks ( );

	// set initial variables
	_state = PLAYING_FIRST_MOVE;
	_correct_flags = 0;

	// set input scaler from display scale settings
	if ( _graphics->getIntegerScaler ( ) == 2 )
	{
		_input->setScaleFlag ( true );
	}
}


Game::~Game ( void )
{
	delete _data;
	delete _input;
	delete _graphics;
	delete _playfield;
	delete _ticks;
}


void
Game::play ( void )
{
	uint8_t kaboom = 0;
	bool is_running = true;


	while ( is_running == true )
	{
		// start frame
		_ticks->start ( );

		// update input buffers
		_input->update ( );

		// check for exit
		if ( _input->isSet ( EXIT ) == true )
		{
			is_running = false;
			break;
		}
	
		// handle palette change
		handlePaletteChange ( );
	
		// check for function reset keys
		checkFunctionResets ( );
		
		// check for mouse click (left)
		if ( _input->isSet ( MOUSE_BUTTON_LEFT ) == true )
		{
			// is the click on the playfield?
			if ( _input->isMouseInBounds ( 0, 0, RENDER_WIDTH, RENDER_WIDTH ) )
			{
				kaboom = handleLeftClick ( );
			}
		}
		
		// check for mouse click (right)
		if ( _input->isSet ( MOUSE_BUTTON_RIGHT ) )
		{
			if ( _input->isMouseInBounds ( 0, 0, RENDER_WIDTH, RENDER_WIDTH ) )
			{
				handleRightClick ( );
			}
		}

		// game over checks
		if ( kaboom == 1 )
		{
			// death by mine
			explode ( );

			// reset the trigger
			kaboom = 0;
		}

		if ( isWin ( ) == true )
		{
			victory ( );
		}

		// render game
		_graphics->render ( _playfield, _data );

		// end frame
		_ticks->end ( );
	}
}


uint8_t
Game::handleLeftClick ( void )
{
	uint16_t x = _input->getTileX ( );
	uint16_t y = _input->getTileY ( );


	// do nothing if game over
	if ( _state == GAME_ENDED )
	{
		return 0;
	}

	// only first move, generate playfield
	if ( _state == PLAYING_FIRST_MOVE )
	{
		_playfield->generatePlayfield ( x, y, _data->getNumberOfMines ( ) );
		_state = PLAYING;
	}

	// both first move and in progress
	sweep ( ( int16_t ) x, ( int16_t ) y );

	// check for mine
	if ( _playfield->getBelow ( x, y ) == MINE )
	{
		_playfield->setBelow ( x, y, EXPLODED_MINE );
		return 1;
	}

	return 0;
}


void
Game::handleRightClick ( void )
{
	uint8_t x = _input->getTileX ( );
	uint8_t y = _input->getTileY ( );


	// do nothing if game over
	if ( ( _state == GAME_ENDED ) || ( _state == PLAYING_FIRST_MOVE ) )
	{
		return;
	}

	if ( _playfield->getAbove ( x, y ) == DIRT )
	{
		// can we place a flag?
		if ( _data->setFlag ( ) == true )
		{
			_playfield->setAbove ( x, y, FLAG );
		}
	}
	else if ( _playfield->getAbove ( x, y ) == FLAG )
	{
		if ( _data->restoreFlag ( ) == true )
		{
			_playfield->setAbove ( x, y, DIRT );
		}
	}
	else;
}


void
Game::handlePaletteChange ( void )
{
	if ( _input->isSet ( KEY_COMMA ) == true )
	{
		_graphics->prevPalette ( );
	}

	if ( _input->isSet ( KEY_PERIOD ) == true )
	{
		_graphics->nextPalette ( );
	}
}


void
Game::checkFunctionResets ( void )
{
	bool fk_pressed = false;


	if ( _input->isSet ( KEY_F1 ) == true )
	{
		_data->setDifficulty ( EASY_PEASY );
		fk_pressed = true;
	}

	if ( _input->isSet ( KEY_F2 ) == true )
	{
		_data->setDifficulty ( I_LIKE_IT_SPICY );
		fk_pressed = true;
	}

	if ( _input->isSet ( KEY_F3 ) == true )
	{
		_data->setDifficulty ( WHY_SO_SERIOUS );
		fk_pressed = true;
	}

	if ( _input->isSet ( KEY_F9 ) )
	{
		_data->reset ( );
		fk_pressed = true;
	}

	if ( fk_pressed == true )
	{
		_playfield->clearPlayfield ( );
		_state = PLAYING_FIRST_MOVE;
	}
}


void
Game::sweep ( int16_t x, int16_t y )
{
	int16_t c;
	int16_t r;


	// out of bounds? return
	if ( ( x < 0 ) || ( x > ( _playfield->getWidth ( ) - 1 ) ) )
	{
		return;
	}
	
	if ( ( y < 0 ) || ( y > ( _playfield->getHeight ( ) - 1 ) ) )
	{
		return;
	}

	// if playfield is already exposed, do nothing
	if ( _playfield->getAbove ( x, y ) == EXPOSED )
	{
		return;
	}

	if ( _playfield->getAbove ( x, y ) == FLAG )
	{
		_data->restoreFlag ( );
	}

	// expose playfield
	_playfield->setAbove ( x, y, EXPOSED );

	// if not empty below, we are done
	if ( _playfield->getBelow ( x, y ) > EMPTY )
	{
		return;
	}

	for ( r = -1; r < 2; r++ )
	{
		for ( c = -1; c < 2; c++ )
		{
			sweep ( x + c, y + r );
		}
	}
}


void
Game::calculateCorrectFlags ( void )
{
	uint16_t i;


	_correct_flags = 0;

	for ( i = 0; i < _playfield->getArea ( ); i++ )
	{
		if ( ( _playfield->getAbove ( i ) == FLAG ) && ( _playfield->getBelow ( i ) == MINE ) )
		{
			_correct_flags++;
		}
	}
}


bool
Game::isWin ( void )
{
	calculateCorrectFlags ( );

	if ( _correct_flags == _data->getNumberOfMines ( ) )
	{
		return true;
	}

	return false;
}


void
Game::explode ( void )
{
	_data->setMessage ( YOU_GOT_EXPLODED );
	_playfield->explodePlayfield ( );
	_state = GAME_ENDED;
}


void
Game::victory ( void )
{
	_data->setMessage ( YOU_FLAGGED_ALL_THE_MINES );
	_state = GAME_ENDED;
}


