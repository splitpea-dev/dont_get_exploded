#include "palettes.h"


Palettes::Palettes ( uint8_t palettes_count, uint8_t colors_count )
{
	uint8_t i;


	// limit palettes to no less than 1 and no more than 16
	if ( palettes_count == 0 )
	{	
		palettes_count = 1;
	}

	if ( palettes_count > 16 )
	{
		palettes_count = 16;
	}
	
	_palettes_count = palettes_count;

	if ( colors_count == 0 )
	{
		colors_count = 1;
	}
	_colors_count = colors_count;

	for ( i = 0; i < palettes_count; i++ )
	{
		_palettes.push_back ( SDL_AllocPalette ( _colors_count ) );
	}

	// set all palettes to default as safety for load failure
	setDefaultPalettes ( );
}


Palettes::~Palettes ( )
{
	uint8_t i;

	for ( i = 0; i < _palettes_count; i++ )
	{
		SDL_FreePalette ( _palettes [ i ] );
	}

	_palettes.clear ( );
}


SDL_Color *
Palettes::getPalette ( uint8_t palette_index )
{
	if ( palette_index >= _palettes_count )
	{
		palette_index = _palettes_count - 1;
	}
	
	return _palettes [ palette_index ]->colors;
}


SDL_Color *
Palettes::getColor ( uint8_t palette_index, uint8_t color_index )
{
	if ( palette_index >= _palettes_count )
	{
		palette_index = _palettes_count - 1;
	}

	if ( color_index >= _colors_count )
	{
		color_index = _colors_count - 1;
	}

	return &_palettes [ palette_index ]->colors [ color_index ];
}


uint8_t
Palettes::getRed ( uint8_t palette_index, uint8_t color_index )
{
	if ( palette_index >= _palettes_count )
	{
		palette_index = _palettes_count - 1;
	}

	if ( color_index >= _colors_count )
	{
		color_index = _colors_count - 1;
	}

	return _palettes [ palette_index ]->colors [ color_index ].r;
}


uint8_t
Palettes::getGreen ( uint8_t palette_index, uint8_t color_index )
{
	if ( palette_index >= _palettes_count )
	{
		palette_index = _palettes_count - 1;
	}

	if ( color_index >= _colors_count )
	{
		color_index = _colors_count - 1;
	}

	return _palettes [ palette_index ]->colors [ color_index ].g;
}


uint8_t
Palettes::getBlue ( uint8_t palette_index, uint8_t color_index )
{
	if ( palette_index >= _palettes_count )
	{
		palette_index = _palettes_count - 1;
	}

	if ( color_index >= _colors_count )
	{
		color_index = _colors_count - 1;
	}

	return _palettes [ palette_index ]->colors [ color_index ].b;
}


void
Palettes::setRGB ( uint8_t palette_index, uint8_t color_index, uint8_t r, uint8_t g, uint8_t b )
{	
	if ( palette_index >= _palettes_count )
	{
		palette_index = _palettes_count - 1;
	}

	if ( color_index >= _colors_count )
	{
		color_index = _colors_count - 1;
	}

	_palettes [ palette_index ]->colors [ color_index ].r = r;
	_palettes [ palette_index ]->colors [ color_index ].g = g;
	_palettes [ palette_index ]->colors [ color_index ].b = b;
}


uint8_t
Palettes::getColorValueFromHexChars ( FILE *file )
{
	uint8_t i;
	uint8_t combined;
	int16_t c;


	combined = 0x00;
	
	for ( i = 0;  i < 2; i++ )
	{
		// shift the nibble
		combined <<= 4;

		/* read first hex digit (character) */
		do
		{
			/* do, while c is not '0123456789ABCDEF' */
			c = fgetc ( file );
			
			// if its a comment, spin until newline
			if ( c == '#' )
			{
				do
				{
					c = fgetc ( file );
				} while ( c != '\n' );
			}

			// if eof, cancel the call
			if ( feof ( file ) )
			{
				return 0;
			}

			// if c is lowercase a through f, convert to uppercase
			if ( ( c >= 97 ) && ( c <= 102 ) )
			{
				c = toupper ( c );
			}
		} while ( ( c < 48 ) || ( ( c > 57 ) && ( c < 65 ) ) || ( c > 70 ) );	
	
		if ( c < 65 )
		{
			/* 0 through 9 */
			combined |= ( uint8_t ) c - 48;
		}
		else
		{
			/* A through F */
			combined |= ( uint8_t ) c - 55;
		}
	}

	return combined;
}


int8_t
Palettes::load ( const char *filename )
{
	uint8_t p;
	uint8_t c;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	FILE *file;


	file = NULL;
	/* attempt to open file for processing */
	if ( ( file = fopen ( filename, "rb" ) ) == NULL )
	{
		//std::cout << "Data file could not be opened." << std::endl;
		return -1;
	}

	/* success! */
	//std::cout << "Palettes file opened." << std::endl;

	p = 0;
	c = 0;

	while ( ( p < _palettes_count ) && ( feof ( file ) != EOF ) )
	{
		/* reset r g b values to zero */
		r = 0;
		g = 0;
		b = 0;

		/* get r g b values from text file */
		r = getColorValueFromHexChars ( file );
		g = getColorValueFromHexChars ( file );
		b = getColorValueFromHexChars ( file );

		/* set color */
		_palettes [ p ]->colors [ c ].r = r;
		_palettes [ p ]->colors [ c ].g = g;
		_palettes [ p ]->colors [ c ].b = b;
		_palettes [ p ]->colors [ c ].a = 0xff;

		/* set for next color */
		c++;
		if ( c == _colors_count )
		{
			/* reset to color 0 and set to next palette */
			c = 0;
			p++;
		}
	}

	/* close the file */
	fclose ( file );
	std::cout << "Palettes file closed." << std::endl;

	return 0;
}


uint8_t
Palettes::getPaletteCount ( void )
{
	return _palettes_count;
}


uint8_t
Palettes::getColorCount ( void )
{
	return _colors_count;
}


void
Palettes::setDefaultPalettes ( void )
{
	uint8_t i;


	for ( i = 0; i < _palettes_count; i++ )
	{
		setRGB ( i, 0, 0x21, 0x1e, 0x20 );
		setRGB ( i, 1, 0x55, 0x55, 0x68 );
		setRGB ( i, 2, 0xa0, 0xa0, 0x8b );
		setRGB ( i, 3, 0xe9, 0xef, 0xec );
	}
}
