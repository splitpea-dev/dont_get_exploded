/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#include "graphics.h"


Graphics::Graphics ( void )
{
	uint32_t r_mask;
	uint32_t g_mask;
	uint32_t b_mask;
	uint32_t a_mask;
	SDL_Surface *loaded_surface;
	SDL_Surface *icon;


	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	r_mask = 0xff000000;
	g_mask = 0x00ff0000;
	b_mask = 0x0000ff00;
	a_mask = 0x000000ff;
	#else
	r_mask = 0x000000ff;
	g_mask = 0x0000ff00;
	b_mask = 0x00ff0000;
	a_mask = 0xff000000;
	#endif

	// determine best scale factor
	_scaler = 1;
	setIntegerScaler ( );
	
	// create window and renderer
	SDL_CreateWindowAndRenderer ( RENDER_WIDTH * _scaler, RENDER_HEIGHT * _scaler, SDL_WINDOW_SHOWN, &_window, &_renderer );
	SDL_RenderSetLogicalSize ( _renderer, RENDER_WIDTH, RENDER_HEIGHT );
	SDL_SetHint ( SDL_HINT_RENDER_SCALE_QUALITY, "0" );

	// set window title
	SDL_SetWindowTitle ( _window, WINDOW_TITLE );

	// palettes
	_palette = 0;
	_palettes = new Palettes ( PALETTES_LIMIT, COLORS_LIMIT );
	_palettes->load ( PALETTES_FILENAME );


	// load icon and set
	icon = IMG_Load ( ICON_FILENAME );
	SDL_SetColorKey ( icon, SDL_TRUE, SDL_MapRGBA ( icon->format, 0x00, 0xff, 0xff, 0xff ) );
	SDL_SetWindowIcon ( _window, icon );
	SDL_FreeSurface ( icon );

	// load tiles and create texture
	loaded_surface = IMG_Load ( TILES_FILENAME );
	_surface = SDL_CreateRGBSurface ( 0, loaded_surface->w, loaded_surface->h, 8, 0, 0, 0, 0 );
	_tiles_surface = SDL_CreateRGBSurface ( 0, _surface->w, _surface->h, 32, r_mask, g_mask, b_mask, a_mask );
	copyToIndexedSurface ( loaded_surface );
	SDL_FreeSurface ( loaded_surface );
	SDL_SetPaletteColors ( _surface->format->palette, _palettes->getPalette ( _palette ), 0, 4 );
	
	// create texture atlas
	_texture = SDL_CreateTexture ( _renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, _surface->w, _surface->h );
	upgradeSurfaceAndStream ( );
	
	// initialize clip rectangles
	initializeClips ( );
}

void
Graphics::displaySurfaceInformation ( SDL_Surface *surface )
{
	if ( surface == NULL )
	{
		return;
	}

	std::cout << "Flags: " << surface->flags << std::endl;
	std::cout << "BytesPerPixel: " << ( int ) surface->format->BytesPerPixel << std::endl;
	std::cout << "Pitch: " << surface->pitch << std::endl;
	std::cout << "Width: " << surface->w << std::endl;
	std::cout << "Height: " << surface->h << std::endl;
}


Graphics::~Graphics ( void )
{
	// free up SDL data structures
	delete _palettes;
	SDL_FreeSurface     ( _tiles_surface );
	SDL_FreeSurface     ( _surface  ); 
	SDL_DestroyTexture  ( _texture  );
	SDL_DestroyRenderer ( _renderer );
	SDL_DestroyWindow   ( _window   );
}


void
Graphics::initializeClips ( void )
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


void
Graphics::clearRenderer ( void )
{
	SDL_SetRenderDrawColor ( _renderer, 0x24, 0x3d, 0x5c, 0xff );
	SDL_RenderClear ( _renderer );
}


void
Graphics::render ( Playfield *playfield, Data *data )
{
	clearRenderer ( );
	renderPlayfield ( playfield );
	renderData ( data );
	SDL_RenderPresent ( _renderer );
}


void
Graphics::renderData ( Data *data )
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


void
Graphics::renderPlayfield ( Playfield *playfield )
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
				switch ( playfield->getBelow ( ( uint8_t ) x, ( uint8_t ) y ) )
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
						i = 6 + playfield->getBelow ( ( uint8_t ) x, ( uint8_t ) y );
						break;
				}
			}
			else
			{
				switch ( playfield->getAbove ( ( uint8_t ) x, ( uint8_t ) y ) )
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


uint16_t
Graphics::getIntegerScaler ( void )
{
	return _scaler;
}


void
Graphics::setIntegerScaler ( void )
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


void
Graphics::copyToIndexedSurface ( SDL_Surface *source )
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t p;
	uint16_t x;
	uint16_t y;
	uint32_t *sp = ( uint32_t * ) source->pixels;
	uint8_t *dp = ( uint8_t * ) _surface->pixels;
	uint32_t color;


	for ( y = 0; y < source->h; y++ )
	{
		for ( x = 0; x < source->w; x++ )
		{
			color = sp [ ( ( y * source->w ) + x ) ];
			SDL_GetRGB ( color, source->format, &r, &g, &b ); 
			if ( r < 64 )
			{
				p = 0;
			}
			else if ( r < 128 )
			{
				p = 1;
			}
			else if ( r < 192 )
			{
				p = 2;
			}
			else
			{
				p = 3;
			}

			//std::cout << "( "<< x << ", " << y << " )" << color << ", " << ( int ) p << std::endl;
			dp [ ( ( y * _surface->w ) + x ) ] = p;
		}
	}
}


void
Graphics::upgradeSurfaceAndStream ( void )
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t p;
	uint16_t x;
	uint16_t y;
	uint8_t *p1 = ( uint8_t * ) _surface->pixels;
	uint32_t *p2 = ( uint32_t * ) _tiles_surface->pixels;


	// paint indexed surface to tiles_surface
	for ( y = 0; y < _surface->h; y++ )
	{
		for ( x = 0; x < _surface->w; x++ )
		{
			p = p1 [ ( ( y * _surface->w ) + x ) ];
			r = _palettes->getRed ( _palette, p );
			g = _palettes->getGreen ( _palette, p );
			b = _palettes->getBlue ( _palette, p );
			p2 [ ( ( y * _tiles_surface->w ) + x ) ] = SDL_MapRGB ( _tiles_surface->format, r, g, b );
		}
	}

	// update stream texture
	SDL_UpdateTexture ( _texture, NULL, _tiles_surface->pixels, _tiles_surface->w * sizeof ( uint32_t ) );
}


void
Graphics::setPalette ( uint8_t palette_index )
{
	if ( palette_index >= _palettes->getPaletteCount ( ) )
	{
		return;
	}
	
	_palette = palette_index;
	SDL_SetPaletteColors ( _surface->format->palette, _palettes->getPalette ( _palette ), 0, COLORS_LIMIT );
	upgradeSurfaceAndStream ( );
}


void
Graphics::nextPalette ( void )
{
	_palette++;

	if ( _palette >= _palettes->getPaletteCount ( ) )
	{
		_palette = 0;
	}

	SDL_SetPaletteColors ( _surface->format->palette, _palettes->getPalette ( _palette ), 0, COLORS_LIMIT );
	upgradeSurfaceAndStream ( );
}


void
Graphics::prevPalette ( void )
{
	if ( _palette > 0 )
	{
		_palette--;
	}
	else
	{
		_palette = _palettes->getPaletteCount ( ) - 1;
	}

	SDL_SetPaletteColors ( _surface->format->palette, _palettes->getPalette ( _palette ), 0, COLORS_LIMIT );
	upgradeSurfaceAndStream ( );
}

