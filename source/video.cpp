//
// Don't Get Exploded!
// Copyright 2022 - 2024, Brian Puthuff
//
// See LICENSE.md for details.
//


#include <iostream>


#include "SDL2/SDL_image.h"


#include "video.hpp"


void c_video::init(void)
{
        // window and renderer
	set_scale();
	create_window_and_renderer();
        set_icon();

        // palettes
        set_default_palettes();
        load_palettes(PALETTES_FILENAME);
        
        // surfaces and textures
        create_surfaces_and_texture();

        // clip atlas
	initialize_clips();
}


void c_video::clean_up(void)
{
        // clean up SDL allocated structures
	SDL_FreeSurface(final_surface);
	SDL_FreeSurface(index_surface); 
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}


void c_video::create_window_and_renderer(void)
{
	SDL_CreateWindowAndRenderer(RENDER_WIDTH * scale, RENDER_HEIGHT * scale, SDL_WINDOW_SHOWN, &window, &renderer);
	SDL_RenderSetLogicalSize(renderer, RENDER_WIDTH, RENDER_HEIGHT);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	SDL_SetWindowTitle(window, WINDOW_TITLE);
}


void c_video::set_icon(void)
{
        SDL_Surface *icon;


	icon = IMG_Load(ICON_FILENAME);
	SDL_SetColorKey(icon, SDL_TRUE, SDL_MapRGBA(icon->format, 0x00, 0xff, 0xff, 0xff));
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);
}


void c_video::create_surfaces_and_texture(void)
{
	SDL_Surface *image;
        uint32_t format;


	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
                format = SDL_PIXELFORMAT_RGBA8888       
	#else
                format = SDL_PIXELFORMAT_ABGR8888;
	#endif

        // import and define indexed surface
	image = IMG_Load(TILES_FILENAME);
        create_index_surface(image);
	SDL_FreeSurface(image);
        SDL_SetPaletteColors(index_surface->format->palette, palettes[palette], 0, COLORS);

        // create final surface and texture
	final_surface = SDL_CreateRGBSurfaceWithFormat(0, index_surface->w, index_surface->h, 32, format);
        transfer_index_surface();
	texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, index_surface->w, index_surface->h);
        SDL_UpdateTexture(texture, NULL, final_surface->pixels, final_surface->w * sizeof(uint32_t));
}


void c_video::display_surface_information(SDL_Surface *surface)
{
	if (surface == NULL) {
		return;
        }

	std::cout << "Flags: " << surface->flags << std::endl;
	std::cout << "BytesPerPixel: " << (int) surface->format->BytesPerPixel << std::endl;
	std::cout << "Pitch: " << surface->pitch << std::endl;
	std::cout << "Width: " << surface->w << std::endl;
	std::cout << "Height: " << surface->h << std::endl;
}


void c_video::initialize_clips(void)
{
	size_t i;


	// tiles, icons, etc.
	for (i = 0; i < 30; i += 1) {
		clips[i].w = 32;
		clips[i].h = 32;
	}
	for (i = 0; i < 15; i += 1) {
		clips[i].x = (i * 32);
		clips[i].y = 0;
		clips[(i + 15)].x = (i * 32);
		clips[(i + 15)].y = 32;
	}

	// messages
	for (i = 0; i < 3; i += 1) {
		clips[(i + MESSAGE_OFFSET)].w = 480;
		clips[(i + MESSAGE_OFFSET)].h = 32;
		clips[(i + MESSAGE_OFFSET)].x = 0;
		clips[(i + MESSAGE_OFFSET)].y = ((i + 2) * 32);
	}
}


void c_video::clear_renderer(void)
{
	SDL_SetRenderDrawColor(renderer, 0x24, 0x3d, 0x5c, 0xff);
	SDL_RenderClear(renderer);
}


void c_video::present_renderer(void)
{
        SDL_RenderPresent(renderer);
}


void c_video::render_tile(uint16_t index, uint16_t x, uint16_t y)
{
        SDL_Rect p;
        
        
        p.x = x;
        p.y = y;
        p.w = clips[index].w;
        p.h = clips[index].h;

        SDL_RenderCopy(renderer, texture, &clips[index], &p);        
}


void c_video::set_scale(void)
{
	SDL_DisplayMode mode;


        scale = 1;

        // if information is not available, use 1x scale by default
	if (SDL_GetCurrentDisplayMode(0, &mode) < 0) {
		return;
        }

        // if height can accommodate 2x, then set scale to 2x
	if (mode.h > (RENDER_HEIGHT * 2)) {
		scale = 2;
	}
}


void c_video::create_index_surface(SDL_Surface *source)
{
        uint16_t x;
        uint16_t y;
        uint8_t p;
	uint8_t *dp;
	uint32_t *sp;
        SDL_Color color;


	index_surface = SDL_CreateRGBSurface(0, source->w, source->h, 8, 0, 0, 0, 0);
        sp = (uint32_t *)source->pixels;
        dp = (uint8_t *)index_surface->pixels;
	for (y = 0; y < source->h; y += 1) {
		for (x = 0; x < source->w; x += 1) {
			SDL_GetRGB(sp[((y * source->w) + x)], source->format, &color.r, &color.g, &color.b); 
                        // assumes r = g = b in grayscale source image
                        if (color.r < 64) {
				p = 0;
                        } else if (color.r < 128) {
				p = 1;
                        } else if (color.r < 192) {
				p = 2;
                        } else {
				p = 3;
                        }
			dp[((y * index_surface->w) + x)] = p;
		}
	}
}


void c_video::transfer_index_surface(void)
{
        SDL_Color color;
        uint16_t x;
        uint16_t y;
	uint8_t p;
	uint8_t *ip;
	uint32_t *fp;


        ip = (uint8_t *)index_surface->pixels;
        fp = (uint32_t *)final_surface->pixels;
	for (y = 0; y < index_surface->h; y += 1) {
		for (x = 0; x < index_surface->w; x += 1) {
			p = ip[((y * index_surface->w) + x)];
			color.r = palettes[palette][p].r;
			color.g = palettes[palette][p].g;
			color.b = palettes[palette][p].b;
			fp[((y * final_surface->w) + x)] = SDL_MapRGB(final_surface->format, color.r, color.g, color.b);
		}
	}        
}


void c_video::set_palette(uint8_t palette_index)
{
	if (palette_index >= PALETTES) {
		return;
        }
	
	palette = palette_index;
	SDL_SetPaletteColors(index_surface->format->palette, palettes[palette], 0, COLORS);
	transfer_index_surface();
        SDL_UpdateTexture(texture, NULL, final_surface->pixels, final_surface->w * sizeof(uint32_t));
}


void c_video::next_palette(void)
{
	palette += 1;

	if (palette >= PALETTES) {
		palette = 0;
        }

	SDL_SetPaletteColors(index_surface->format->palette, palettes[palette], 0, COLORS);
	transfer_index_surface();
        SDL_UpdateTexture(texture, NULL, final_surface->pixels, final_surface->w * sizeof(uint32_t));
}


void c_video::prev_palette(void)
{
	if (palette > 0) {
		palette -= 1;
        } else {
		palette = (PALETTES - 1);
        }

	SDL_SetPaletteColors(index_surface->format->palette, palettes[palette], 0, COLORS);
	transfer_index_surface();
        SDL_UpdateTexture(texture, NULL, final_surface->pixels, final_surface->w * sizeof(uint32_t));
}


void c_video::set_rgb(uint8_t palette_index, uint8_t color_index, uint8_t r, uint8_t g, uint8_t b )
{	
        SDL_Color *c;


        c = &palettes[palette_index][color_index];
        c->r = r;
        c->g = g;
        c->b = b;
        c->a = 0xff;
}


int8_t c_video::get_nibble(FILE *file)
{
        int16_t c;


        c = 0;
        do {
                c = fgetc(file);
                
                // if its a comment, spin until newline
                if (c == '#') {
                        do {
                                c = fgetc(file);
                        } while ((c != '\n') && (feof(file) != EOF));
                }

                if (feof(file) == EOF) {
                        return 0;
                }

                if ((c >= 97) && (c <= 102)) {
                        c = toupper(c);
                }
        } while ((c < 48) || ((c > 57) && (c < 65)) || (c > 70));

        return c;     
}


uint8_t c_video::get_color_value_from_hex_chars(FILE *file)
{
	uint8_t i;
	uint8_t c;
	uint8_t combined;


        c = 0;
        combined = 0;
	for (i = 0; i < 2; i += 1) {
		combined <<= 4;
                c = get_nibble(file);	
		if (c < 65) {
			/* 0 through 9 */
			combined |= (uint8_t) (c - 48);
		}
		else {
			/* A through F */
			combined |= (uint8_t) (c - 55);
		}
	}

	return combined;
}


int8_t c_video::load_palettes(const char *filename)
{
	uint8_t p;
	uint8_t c;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	FILE *file;


	file = NULL;
	if ((file = fopen(filename, "rb")) == NULL) {
		//std::cout << "Data file could not be opened." << std::endl;
		return -1;
	}

	/* success! */
	//std::cout << "Palettes file opened." << std::endl;

	p = 0;
	c = 0;
	while ((p < PALETTES) && (feof(file) != EOF)) {
		/* reset r g b values to zero */
		r = 0;
		g = 0;
		b = 0;

		/* get r g b values from text file */
		r = get_color_value_from_hex_chars(file);
		g = get_color_value_from_hex_chars(file);
		b = get_color_value_from_hex_chars(file);

                set_rgb(p, c, r, g, b);

		c += 1;
		if (c == COLORS) {
			c = 0;
			p += 1;
		}
	}
	fclose(file);
	//std::cout << "Palettes file closed." << std::endl;

	return 0;
}


void c_video::set_default_palettes(void)
{
	uint8_t i = 0;


	for (; i < PALETTES; i += 1) {
		set_rgb(i, 0, 0x21, 0x1e, 0x20);
		set_rgb(i, 1, 0x55, 0x55, 0x68);
		set_rgb(i, 2, 0xa0, 0xa0, 0x8b);
		set_rgb(i, 3, 0xe9, 0xef, 0xec);
	}
}
