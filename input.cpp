/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#include "input.h"


Input::Input ( void )
{
	_flag_2x = false;
	resetFlags ( );

}


Input::~Input ( void )
{
	// Nothing to see here.
}


void Input::update ( void )
{
	SDL_Event event;


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
		}
	}
}


void Input::resetFlags ( void )
{
	_flag_exit = false;
	_flag_f1 = false;
	_flag_f2 = false;
	_flag_f3 = false;
	_flag_f9 = false;
	_mouse_button_left = false;
	_mouse_button_right = false;
	_mouse_x = 0;
	_mouse_y = 0;
}


bool Input::isSet ( uint8_t trigger )
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

		case EXIT:
			return _flag_exit;
			break;

		default:
			break;
	}

	return false;
}


int16_t Input::getMouseX ( void )
{
	return _mouse_x;
}


int16_t Input::getMouseY ( void )
{
	return _mouse_y;
}


uint16_t Input::getTileX ( void )
{
	return ( floor ( _mouse_x / 32 ) );
}


uint16_t Input::getTileY ( void )
{
	return ( floor ( _mouse_y / 32 ) );
}


bool Input::isMouseInBounds ( uint16_t x, uint16_t y, uint16_t w, uint16_t h )
{
	if ( _mouse_x < x || _mouse_x > x + w )
	{
		return false;
	}	

	if ( _mouse_y < y || _mouse_y > y + h )
	{
		return false;
	}

	return true;
}


void Input::setScaleFlag ( bool flip )
{
	_flag_2x = flip;
}


