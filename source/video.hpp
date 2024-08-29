/*
** Don't Get Exploded!
** Copyright 2022 - 2024, Brian Puthuff
**
** See LICENSE.md for details.
*/


#pragma once


#include "SDL2/SDL.h"
#include "defines.hpp"


class c_video
{
	public:
        uint8_t scale;
        void init(void);
        void clean_up(void);
	void set_palette(uint8_t palette_index);
	void prev_palette(void);
	void next_palette(void);
        void clear_renderer(void);
        void render_tile(uint16_t index, uint16_t x, uint16_t y);
        void present_renderer(void);

        private:
        uint8_t palette;
        SDL_Color palettes[PALETTES][COLORS];
	SDL_Rect clips[CLIPS];
	SDL_Surface *index_surface;
	SDL_Surface *final_surface;
	SDL_Texture *texture;
	SDL_Renderer *renderer;
	SDL_Window *window;

        // atlas clips
	void initialize_clips(void);

        // window and rendering context
	void set_scale(void);
        void create_window_and_renderer(void);
        void set_icon(void);

        // surfaces and textures
        void create_surfaces_and_texture(void);
        void transfer_index_surface(void);
	void display_surface_information(SDL_Surface *surface);
	void create_index_surface(SDL_Surface *source);

        // palettes
        int8_t load_palettes(const char *filename);
        void set_default_palettes(void);
        void set_rgb(uint8_t palette_index, uint8_t color_index, uint8_t r, uint8_t g, uint8_t b);
        uint8_t get_color_value_from_hex_chars(FILE *file);
        int8_t get_nibble(FILE *file);
};

