/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#include "game.h"


<<<<<<< HEAD
Game::Game ( void )
{
	// instantiate things ...
	_data = new Data ( );
	_input = new Input ( );
	_graphics = new Graphics ( );
	_playfield = new Playfield ( PLAYFIELD_WIDTH, PLAYFIELD_HEIGHT );
	_ticks = new Ticks ( );
=======
Game::Game(void)
{
	// instantiate things ...
	_data = new Data();
	_input = new Input();
	_graphics = new Graphics();
	_playfield = new Playfield(PLAYFIELD_WIDTH, PLAYFIELD_HEIGHT);
	_ticks = new Ticks();
>>>>>>> 41dc873 (General refactoring.)

	// set initial variables
	_state = PLAYING_FIRST_MOVE;
	_correct_flags = 0;

	// set input scaler from display scale settings
<<<<<<< HEAD
	if ( _graphics->getIntegerScaler ( ) == 2 )
	{
		_input->setScaleFlag ( true );
=======
	if (_graphics->getIntegerScaler() == 2) {
		_input->setScaleFlag(true);
>>>>>>> 41dc873 (General refactoring.)
	}
}


<<<<<<< HEAD
Game::~Game ( void )
=======
Game::~Game(void)
>>>>>>> 41dc873 (General refactoring.)
{
	delete _data;
	delete _input;
	delete _graphics;
	delete _playfield;
	delete _ticks;
}


void
<<<<<<< HEAD
Game::play ( void )
=======
Game::play(void)
>>>>>>> 41dc873 (General refactoring.)
{
	uint8_t kaboom = 0;
	bool is_running = true;


<<<<<<< HEAD
	while ( is_running == true )
	{	
		// check for exit
		if ( _input->isSet ( EXIT ) == true )
		{
			is_running = false;
		}
		else
		{
			// start frame
			_ticks->start ( );

			// update input buffers
			_input->update ( );

			// check for exit
	
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
=======
	while (is_running == true) {	
		// check for exit
		if (_input->isSet(EXIT) == true) {
			is_running = false;
		} else {
			// start frame
			_ticks->start();

			// update input buffers
			_input->update();
	
			// handle palette change
			handlePaletteChange();
	
			// check for function reset keys
			checkFunctionResets();
		
			// check for mouse click (left)
			if (_input->isSet(MOUSE_BUTTON_LEFT) == true) {
				// is the click on the playfield?
				if (_input->isMouseInBounds(0, 0, RENDER_WIDTH, RENDER_WIDTH))
					kaboom = handleLeftClick();
			}
		
			// check for mouse click (right)
			if (_input->isSet(MOUSE_BUTTON_RIGHT)) {
				if (_input->isMouseInBounds(0, 0, RENDER_WIDTH, RENDER_WIDTH))
					handleRightClick();
			}

			// game over checks
			if (kaboom == 1) {
				// death by mine
				explode();

				// reset the trigger
				kaboom = 0;
			}

			if (isWin() == true)
				victory();

			// render game
			_graphics->render(_playfield, _data);

			// end frame
			_ticks->end();
		}
	}
}


uint8_t
Game::handleLeftClick(void)
{
	uint16_t x = _input->getTileX();
	uint16_t y = _input->getTileY();


	// do nothing if game over
	if (_state == GAME_ENDED)
		return 0;

	// only first move, generate playfield
	if (_state == PLAYING_FIRST_MOVE) {
		_playfield->generatePlayfield((uint8_t) x, (uint8_t) y, _data->getNumberOfMines());
		_state = PLAYING;
	}

	// both first move and in progress
	sweep((int16_t) x, (int16_t) y);

	// check for mine
	if (_playfield->getBelow((uint8_t) x, (uint8_t) y) == MINE) {
		_playfield->setBelow((uint8_t) x, (uint8_t) y, EXPLODED_MINE);
		return 1;
	}

	return 0;
}


void
Game::handleRightClick(void)
{
	uint8_t x = (uint8_t) _input->getTileX();
	uint8_t y = (uint8_t) _input->getTileY();


	// do nothing if game over
	if (( _state == GAME_ENDED) || (_state == PLAYING_FIRST_MOVE))
		return;

	if (_playfield->getAbove ((uint8_t) x, (uint8_t) y) == DIRT) {
		// can we place a flag?
		if ( _data->setFlag() == true)
			_playfield->setAbove ((uint8_t) x, y, (uint8_t) FLAG);
	} else if (_playfield->getAbove((uint8_t) x, (uint8_t) y) == FLAG) {
		if (_data->restoreFlag() == true)
			_playfield->setAbove((uint8_t) x, (uint8_t) y, DIRT);
	} else;
}


void
Game::handlePaletteChange(void)
{
	if (_input->isSet(KEY_COMMA) == true)
		_graphics->prevPalette();

	if ( _input->isSet(KEY_PERIOD) == true)
		_graphics->nextPalette();
}


void
Game::checkFunctionResets(void)
{
	bool fk_pressed = false;


	if (_input->isSet(KEY_F1) == true) {
		_data->setDifficulty(EASY_PEASY);
		fk_pressed = true;
	}

	if (_input->isSet(KEY_F2) == true) {
		_data->setDifficulty(I_LIKE_IT_SPICY);
		fk_pressed = true;
	}

	if (_input->isSet(KEY_F3) == true ) {
		_data->setDifficulty(WHY_SO_SERIOUS);
		fk_pressed = true;
	}

	if(_input->isSet(KEY_F9)) {
		_data->reset();
		fk_pressed = true;
	}

	if (fk_pressed == true) {
		_playfield->clearPlayfield();
		_state = PLAYING_FIRST_MOVE;
>>>>>>> 41dc873 (General refactoring.)
	}
}


<<<<<<< HEAD
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
		_playfield->generatePlayfield ( ( uint8_t ) x, ( uint8_t ) y, _data->getNumberOfMines ( ) );
		_state = PLAYING;
	}

	// both first move and in progress
	sweep ( ( int16_t ) x, ( int16_t ) y );

	// check for mine
	if ( _playfield->getBelow ( ( uint8_t ) x, ( uint8_t ) y ) == MINE )
	{
		_playfield->setBelow ( ( uint8_t ) x, ( uint8_t ) y, EXPLODED_MINE );
		return 1;
	}

	return 0;
}


void
Game::handleRightClick ( void )
{
	uint8_t x = ( uint8_t ) _input->getTileX ( );
	uint8_t y = ( uint8_t ) _input->getTileY ( );


	// do nothing if game over
	if ( ( _state == GAME_ENDED ) || ( _state == PLAYING_FIRST_MOVE ) )
	{
		return;
	}

	if ( _playfield->getAbove ( ( uint8_t ) x, ( uint8_t ) y ) == DIRT )
	{
		// can we place a flag?
		if ( _data->setFlag ( ) == true )
		{
			_playfield->setAbove ( ( uint8_t ) x, y, ( uint8_t ) FLAG );
		}
	}
	else if ( _playfield->getAbove ( ( uint8_t ) x, ( uint8_t ) y ) == FLAG )
	{
		if ( _data->restoreFlag ( ) == true )
		{
			_playfield->setAbove ( ( uint8_t ) x, ( uint8_t ) y, DIRT );
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
=======
void
Game::sweep(int16_t x, int16_t y)
{
>>>>>>> 41dc873 (General refactoring.)
	int16_t c;
	int16_t r;


	// out of bounds? return
<<<<<<< HEAD
	if ( ( x < 0 ) || ( x > ( _playfield->getWidth ( ) - 1 ) ) )
	{
		return;
	}
	
	if ( ( y < 0 ) || ( y > ( _playfield->getHeight ( ) - 1 ) ) )
	{
		return;
	}

	// if playfield is already exposed, do nothing
	if ( _playfield->getAbove ( ( uint8_t ) x, ( uint8_t ) y ) == EXPOSED )
	{
		return;
	}

	if ( _playfield->getAbove ( ( uint8_t ) x, ( uint8_t ) y ) == FLAG )
	{
		_data->restoreFlag ( );
	}

	// expose playfield
	_playfield->setAbove ( ( uint8_t ) x, ( uint8_t ) y, EXPOSED );

	// if not empty below, we are done
	if ( _playfield->getBelow ( ( uint8_t ) x, ( uint8_t ) y ) > EMPTY )
	{
		return;
	}

	for ( r = -1; r < 2; r++ )
	{
		for ( c = -1; c < 2; c++ )
		{
			sweep ( x + c, y + r );
=======
	if ((x < 0) || (x > (_playfield->getWidth() - 1)))
		return;
	
	if ((y < 0) || (y > (_playfield->getHeight() - 1)))
		return;

	// if playfield is already exposed, do nothing
	if (_playfield->getAbove((uint8_t) x, (uint8_t) y) == EXPOSED)
		return;

	if (_playfield->getAbove((uint8_t) x, (uint8_t) y) == FLAG)
		_data->restoreFlag();

	// expose playfield
	_playfield->setAbove((uint8_t) x, (uint8_t) y, EXPOSED);

	// if not empty below, we are done
	if (_playfield->getBelow((uint8_t) x, (uint8_t) y) > EMPTY)
		return;

	for (r = -1; r < 2; r += 1) {
		for (c = -1; c < 2; c += 1) {
			sweep((x + c), (y + r));
>>>>>>> 41dc873 (General refactoring.)
		}
	}
}


void
<<<<<<< HEAD
Game::calculateCorrectFlags ( void )
=======
Game::calculateCorrectFlags(void)
>>>>>>> 41dc873 (General refactoring.)
{
	uint16_t i;


	_correct_flags = 0;

<<<<<<< HEAD
	for ( i = 0; i < _playfield->getArea ( ); i++ )
	{
		if ( ( _playfield->getAbove ( i ) == FLAG ) && ( _playfield->getBelow ( i ) == MINE ) )
		{
			_correct_flags++;
		}
=======
	for (i = 0; i < _playfield->getArea(); i += 1) {
		if (( _playfield->getAbove(i) == FLAG) && (_playfield->getBelow(i) == MINE))
			_correct_flags += 1;
>>>>>>> 41dc873 (General refactoring.)
	}
}


bool
<<<<<<< HEAD
Game::isWin ( void )
{
	calculateCorrectFlags ( );

	if ( _correct_flags == _data->getNumberOfMines ( ) )
	{
		return true;
	}
=======
Game::isWin (void)
{
	calculateCorrectFlags();

	if (_correct_flags == _data->getNumberOfMines())
		return true;
>>>>>>> 41dc873 (General refactoring.)

	return false;
}


void
<<<<<<< HEAD
Game::explode ( void )
{
	_data->setMessage ( YOU_GOT_EXPLODED );
	_playfield->explodePlayfield ( );
=======
Game::explode(void)
{
	_data->setMessage(YOU_GOT_EXPLODED);
	_playfield->explodePlayfield();
>>>>>>> 41dc873 (General refactoring.)
	_state = GAME_ENDED;
}


void
<<<<<<< HEAD
Game::victory ( void )
{
	_data->setMessage ( YOU_FLAGGED_ALL_THE_MINES );
=======
Game::victory(void)
{
	_data->setMessage(YOU_FLAGGED_ALL_THE_MINES);
>>>>>>> 41dc873 (General refactoring.)
	_state = GAME_ENDED;
}


