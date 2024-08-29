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


#include "input.h"


<<<<<<< HEAD
Input::Input ( void )
{
	_flag_2x = false;
	resetFlags ( );
=======
Input::Input(void)
{
	_flag_2x = false;
	resetFlags();
>>>>>>> 41dc873 (General refactoring.)

}


<<<<<<< HEAD
Input::~Input ( void )
=======
Input::~Input(void)
>>>>>>> 41dc873 (General refactoring.)
{
	// Nothing to see here.
}


void
<<<<<<< HEAD
Input::update ( void )
=======
Input::update(void)
>>>>>>> 41dc873 (General refactoring.)
{
	SDL_Event event;


<<<<<<< HEAD
	while ( SDL_PollEvent ( &event ) > 0 )
	{
		switch ( event.type )
		{
			case SDL_QUIT:
				_flag_exit = true;
				break;

			case SDL_KEYDOWN:
				if ( event.key.keysym.sym == SDLK_F1 )
				{
					_flag_f1 = true;
				}

				if ( event.key.keysym.sym == SDLK_F2 )
				{
					_flag_f2 = true;
				}

				if ( event.key.keysym.sym == SDLK_F3 )
				{
					_flag_f3 = true;
				}

				if ( event.key.keysym.sym == SDLK_F9 )
				{
					_flag_f9 = true;
				}
				
				if ( event.key.keysym.sym == SDLK_COMMA )
				{
					_flag_comma = true;
				}

				if ( event.key.keysym.sym == SDLK_PERIOD )
				{
					_flag_period = true;
				}
				
				if ( event.key.keysym.sym == SDLK_TAB )
				{
					_flag_tab = true;
				}
				break;


			case SDL_KEYUP:
				if ( event.key.keysym.sym == SDLK_F1 )
				{
					_flag_f1 = false;
				}

				if ( event.key.keysym.sym == SDLK_F2 )
				{
					_flag_f2 = false;
				}

				if ( event.key.keysym.sym == SDLK_F3 )
				{
					_flag_f3 = false;
				}

				if ( event.key.keysym.sym == SDLK_F9 )
				{
					_flag_f9 = false;
				}
				
				if ( event.key.keysym.sym == SDLK_COMMA )
				{
					_flag_comma = false;
				}

				if ( event.key.keysym.sym == SDLK_PERIOD )
				{
					_flag_period = false;
				}
				
				if ( event.key.keysym.sym == SDLK_TAB )
				{
					_flag_tab = false;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				if ( event.button.button == SDL_BUTTON_LEFT )
				{
					_mouse_button_left = true;
				}

				if ( event.button.button == SDL_BUTTON_RIGHT )
				{
					_mouse_button_right = true;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				if ( event.button.button == SDL_BUTTON_LEFT )
				{
					_mouse_button_left = false;
				}

				if ( event.button.button == SDL_BUTTON_RIGHT )
				{
					_mouse_button_right = false;
				}

				break;

			case SDL_MOUSEMOTION:
				SDL_GetMouseState ( ( int *) &_mouse_x, ( int * ) &_mouse_y );
				if ( _flag_2x == true )
				{
					_mouse_x = _mouse_x / 2;
					_mouse_y = _mouse_y / 2;
				}
				break;
=======
	while (SDL_PollEvent(&event) > 0) {
		switch (event.type) {
		case SDL_QUIT:
			_flag_exit = true;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_F1)
				_flag_f1 = true;

			if (event.key.keysym.sym == SDLK_F2)
				_flag_f2 = true;

			if (event.key.keysym.sym == SDLK_F3)
				_flag_f3 = true;

			if (event.key.keysym.sym == SDLK_F9)
			        _flag_f9 = true;
				
			if (event.key.keysym.sym == SDLK_COMMA)
			        _flag_comma = true;

			if (event.key.keysym.sym == SDLK_PERIOD)
				_flag_period = true;
				
			if (event.key.keysym.sym == SDLK_TAB)
				_flag_tab = true;

			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_F1)
				_flag_f1 = false;

			if (event.key.keysym.sym == SDLK_F2)
				_flag_f2 = false;

                        if (event.key.keysym.sym == SDLK_F3)
			        _flag_f3 = false;

			if (event.key.keysym.sym == SDLK_F9)
				_flag_f9 = false;
				
			if (event.key.keysym.sym == SDLK_COMMA)
				_flag_comma = false;

			if (event.key.keysym.sym == SDLK_PERIOD)
				_flag_period = false;
				
			if (event.key.keysym.sym == SDLK_TAB)
				_flag_tab = false;

			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				_mouse_button_left = true;

			if ( event.button.button == SDL_BUTTON_RIGHT)
					_mouse_button_right = true;

			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				_mouse_button_left = false;

			if (event.button.button == SDL_BUTTON_RIGHT)
				_mouse_button_right = false;

			break;

		case SDL_MOUSEMOTION:
			SDL_GetMouseState((int *) &_mouse_x, (int *) &_mouse_y);
			if (_flag_2x == true) {
				_mouse_x = (_mouse_x / 2);
				_mouse_y = (_mouse_y / 2);
			}
			break;
>>>>>>> 41dc873 (General refactoring.)
		}
	}
}


void
<<<<<<< HEAD
Input::resetFlags ( void )
=======
Input::resetFlags(void)
>>>>>>> 41dc873 (General refactoring.)
{
	_flag_exit = false;
	_flag_f1 = false;
	_flag_f2 = false;
	_flag_f3 = false;
	_flag_f9 = false;
	_flag_comma = false;
	_flag_period = false;
	_flag_tab = false;
	_mouse_button_left = false;
	_mouse_button_right = false;
	_mouse_x = 0;
	_mouse_y = 0;
}


bool
<<<<<<< HEAD
Input::isSet ( uint8_t trigger )
{
	switch ( trigger )
	{
		case MOUSE_BUTTON_LEFT:
			if ( _mouse_button_left == true )
			{
				_mouse_button_left = false;
				return true;
			}
			break;

		case MOUSE_BUTTON_RIGHT:
			if ( _mouse_button_right == true )
			{
				_mouse_button_right = false;
				return true;
			}
			break;

		case KEY_F1:
			if ( _flag_f1 == true )
			{
				_flag_f1 = false;
				return true;
			}
			break;

		case KEY_F2:
			if ( _flag_f2 == true )
			{
				_flag_f2 = false;
				return true;
			}
			break;

		case KEY_F3:
			if ( _flag_f3 == true )
			{
				_flag_f3 = false;
				return true;
			}
			break;

		case KEY_F9:
			if ( _flag_f9 == true )
			{
				_flag_f9 = false;
				return true;
			}
			break;

		case KEY_COMMA:
			if ( _flag_comma == true )
			{
				_flag_comma = false;
				return true;
			}
			break;

		case KEY_PERIOD:
			if ( _flag_period == true )
			{
				_flag_period = false;
				return true;
			}
			break;

		case KEY_TAB:
			if ( _flag_tab == true )
			{
				_flag_tab = false;
				return true;
			}
			break;
		case EXIT:
			return _flag_exit;
			break;

		default:
			break;
=======
Input::isSet(uint8_t trigger)
{
	switch (trigger) {
	case MOUSE_BUTTON_LEFT:
		if (_mouse_button_left == true) {
			_mouse_button_left = false;
			return true;
		}
		break;

	case MOUSE_BUTTON_RIGHT:
		if (_mouse_button_right == true) {
			_mouse_button_right = false;
			return true;
		}
		break;

	case KEY_F1:
		if (_flag_f1 == true) {
			_flag_f1 = false;
			return true;
		}
		break;

	case KEY_F2:
		if (_flag_f2 == true) {
			_flag_f2 = false;
			return true;
                }
		break;

	case KEY_F3:
		if (_flag_f3 == true) {
			_flag_f3 = false;
			return true;
		}
		break;

	case KEY_F9:
		if (_flag_f9 == true) {
			_flag_f9 = false;
			return true;
		}
		break;

	case KEY_COMMA:
		if (_flag_comma == true) {
			_flag_comma = false;
			return true;
		}
		break;

	case KEY_PERIOD:
		if (_flag_period == true) {
			_flag_period = false;
			return true;
		}
		break;

	case KEY_TAB:
		if (_flag_tab == true) {
		        _flag_tab = false;
			return true;
	        }
		break;
	
        case EXIT:
		return _flag_exit;
		break;

	default:
		break;
>>>>>>> 41dc873 (General refactoring.)
	}

	return false;
}


int16_t
<<<<<<< HEAD
Input::getMouseX ( void )
=======
Input::getMouseX(void)
>>>>>>> 41dc873 (General refactoring.)
{
	return _mouse_x;
}


int16_t
<<<<<<< HEAD
Input::getMouseY ( void )
=======
Input::getMouseY(void)
>>>>>>> 41dc873 (General refactoring.)
{
	return _mouse_y;
}


uint16_t
<<<<<<< HEAD
Input::getTileX ( void )
{
	return ( uint16_t ) ( floor ( _mouse_x / 32 ) );
=======
Input::getTileX(void)
{
	return (uint16_t) (floor(_mouse_x / 32));
>>>>>>> 41dc873 (General refactoring.)
}


uint16_t
<<<<<<< HEAD
Input::getTileY ( void )
{
	return ( uint16_t) ( floor ( _mouse_y / 32 ) );
=======
Input::getTileY(void)
{
	return (uint16_t) (floor (_mouse_y / 32));
>>>>>>> 41dc873 (General refactoring.)
}


bool
<<<<<<< HEAD
Input::isMouseInBounds ( uint16_t x, uint16_t y, uint16_t w, uint16_t h )
{
	if ( _mouse_x < x || _mouse_x > x + w )
	{
		return false;
	}	

	if ( _mouse_y < y || _mouse_y > y + h )
	{
		return false;
	}
=======
Input::isMouseInBounds(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	if ((_mouse_x < x) || (_mouse_x > (x + w)))
		return false;

	if ((_mouse_y < y) || (_mouse_y > (y + h)))
		return false;
>>>>>>> 41dc873 (General refactoring.)

	return true;
}


void
<<<<<<< HEAD
Input::setScaleFlag ( bool flip )
=======
Input::setScaleFlag(bool flip)
>>>>>>> 41dc873 (General refactoring.)
{
	_flag_2x = flip;
}

