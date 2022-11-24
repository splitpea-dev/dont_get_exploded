/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#include "graphics.h"


Graphics::Graphics ( void )
{
	SDL_Surface *surface;


	// determine best scale factor
	_scaler = 1;
	setIntegerScaler ( );
	// std::cout << _scaler << std::endl;
	
	// create window and renderer
	SDL_CreateWindowAndRenderer ( RENDER_WIDTH * _scaler, RENDER_HEIGHT * _scaler, SDL_WINDOW_SHOWN, &_window, &_renderer );
	SDL_RenderSetLogicalSize ( _renderer, RENDER_WIDTH, RENDER_HEIGHT );
	SDL_SetHint ( SDL_HINT_RENDER_SCALE_QUALITY, "0" );

	// set window title
	SDL_SetWindowTitle ( _window, WINDOW_TITLE );

	// load tiles and create texture
	surface = IMG_Load ( TILES_FILENAME );
	
	// set color key
	// NOTE: If your PNG source uses compression, color key may not work as intended as the colors may not match.
	SDL_SetColorKey ( surface, SDL_TRUE, SDL_MapRGB ( surface->format, 0x00, 0xff, 0xff ) );

	// create texture atlas
	_texture = SDL_CreateTextureFromSurface ( _renderer, surface );

	SDL_FreeSurface ( surface );

	// initialize clip rectangles
	initializeClips ( );
}


Graphics::~Graphics ( void )
{
	// free up SDL data structures
	SDL_DestroyTexture  ( _texture  );
	SDL_DestroyRenderer ( _renderer );
	SDL_DestroyWindow   ( _window   );
}


void Graphics::initializeClips ( void )
{
	uint16_t i;


	// tiles, icons, etc.
	for ( i = 0; i < 30; i++ )
	{
		_clips [ i ].w = 32;
		_clips [ i ].h = 32;
	}
	for ( i = 0; i < 15; i++ )
	{
		_clips [ i ].x = i * 32;
		_clips [ i ].y = 0;
		_clips [ i + 15 ].x = i * 32;
		_clips [ i + 15 ].y = 32;
	}

	// messages
	for ( i = 0; i < 3; i++ )
	{
		_clips [ i + 30 ].w = 480;
		_clips [ i + 30 ].h = 32;
		_clips [ i + 30 ].x = 0;
		_clips [ i + 30 ].y = ( i + 2 ) * 32;
	}
}


void Graphics::clearRenderer ( void )
{
	SDL_SetRenderDrawColor ( _renderer, 0x24, 0x3d, 0x5c, 0xff );
	SDL_RenderClear ( _renderer );
}


void Graphics::render ( Playfield *playfield, Data *data )
{
	clearRenderer ( );
	renderPlayfield ( playfield );
	renderData ( data );
	SDL_RenderPresent ( _renderer );
}


void Graphics::renderData ( Data *data )
{
	uint8_t i;
	SDL_Rect position;


	// render message
	position.x = 0;
	position.y = 640;
	position.w = 480;
	position.h = 32;
	i = data->getMessage ( ) + 30;
	SDL_RenderCopy ( _renderer, _texture, &_clips [ i ], &position );

	// render difficulty
	position.x = 480;
	position.y = 640;
	position.w = 32;
	position.h = 32;
	i = data->getDifficulty ( ) + 15;
	SDL_RenderCopy ( _renderer, _texture, &_clips [ i ], &position );

	// render blank
	position.x = 512;
	position.y = 640;
	position.w = 32;
	position.h = 32;
	SDL_RenderCopy ( _renderer, _texture, &_clips [ 18 ], &position );

	// render flag
	position.x = 544;
	position.y = 640;
	position.w = 32;
	position.h = 32;
	SDL_RenderCopy ( _renderer, _texture, &_clips [ 19 ], &position );

	// render flags remaining
	position.x = 608;
	position.y = 640;
	position.w = 32;
	position.h = 32;
	i = ( ( data->getAvailableFlags ( ) % 10 ) + 20 );
	SDL_RenderCopy ( _renderer, _texture, &_clips [ i ], &position );
	position.x = 576;
	i = ( ( data->getAvailableFlags ( ) / 10 ) + 20 );
	SDL_RenderCopy ( _renderer, _texture, &_clips [ i ], &position );
}


void Graphics::renderPlayfield ( Playfield *playfield )
{
	uint8_t i;
	uint16_t x;
	uint16_t y;
	SDL_Rect position;

	position.w = 32;
	position.h = 32;


	i = 0;
	for ( y = 0; y < playfield->getHeight ( ); y++ )
	{
		for ( x = 0; x < playfield->getWidth ( ); x++ )
		{
			position.x = x * 32;
			position.y = y * 32;
			
			if ( playfield->getAbove ( x, y ) == EXPOSED )
			{
				switch ( playfield->getBelow ( x, y ) )
				{
					case MINE:
						i = 4;
						break;
					case FLAGGED_MINE:
						i = 3;
						break;
					case EXPLODED_MINE:
						i = 5;
						break;
					default:
						i = 6 + playfield->getBelow ( x, y );
						break;
				}
			}
			else
			{
				switch ( playfield->getAbove ( x, y ) )
				{
					case DIRT:
						i = 0;
						break;
					case FLAG:
						i = 1;
						break;
					case INCORRECT_FLAG:
						i = 2;
					default:
						break;
				}
			}
			SDL_RenderCopy ( _renderer, _texture, &_clips [ i ], &position );
		}
	}			
}


uint16_t Graphics::getIntegerScaler ( void )
{
	return _scaler;
}


void Graphics::setIntegerScaler ( void )
{
	SDL_DisplayMode mode;


	if ( SDL_GetCurrentDisplayMode ( 0, &mode ) < 0 )
	{
		// if information is not available, use 1x scale by default
		_scaler = 1;
		return;
	}

	// std::cout << "Display vertical resolution: " << mode.h << std::endl;
	if ( mode.h > ( RENDER_HEIGHT * 2 ) )
	{
		_scaler = 2;
		return;
	}

	_scaler = 1;
}
