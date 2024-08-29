//
// Don't Get Exploded!
// Copyright 2022 - 2024, Brian Puthuff
//
// See LICENSE.md for details.
//


#include <iostream>


#include "SDL2/SDL.h"


#include "defines.hpp"
#include "input.hpp"


void c_input::init(void)
{
        scale = 1;
        reset();
}


void c_input::update(void)
{
	SDL_Event event;


	while (SDL_PollEvent(&event) > 0) {
		switch (event.type) {
		case SDL_QUIT:
                        set(ESCAPE, 1);
			break;
		case SDL_KEYDOWN:
                case SDL_KEYUP:
                        handle_key(event.type, event.key.keysym.sym);
			break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                        handle_mouse_button(event.type, event.button.button);
                        break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState((int *) &mouse_x, (int *) &mouse_y);
			if (scale == 2) {
				mouse_x >>= 1;
				mouse_y >>= 1;
			}
			break;
                default:
                        break;
		}
	}
}


void c_input::handle_mouse_button(uint32_t type, uint8_t button)
{
        uint8_t s;


        s = 0;
        if(type == SDL_MOUSEBUTTONDOWN) {
                s = 1;
        }
	
        if(button == SDL_BUTTON_LEFT) {
                set(LEFT_MOUSE_BUTTON, s);
        }

	if (button == SDL_BUTTON_RIGHT) {
		set(RIGHT_MOUSE_BUTTON, s);
        }
}


void c_input::handle_key(uint32_t type, int32_t keycode)
{
        uint8_t s;


        s = 0;
        if(type == SDL_KEYDOWN) {
                s = 1;
        }
        
        switch (keycode) {
        case SDLK_F1:
                set(F1, s);
                break;
        case SDLK_F2:
                set(F2, s);
                break;
        case SDLK_F3:
                set(F3, s);
                break;
        case SDLK_F9:
                set(F9, s);
                break;
        case SDLK_COMMA:
                set(COMMA, s);
                break;
        case SDLK_PERIOD:
                set(PERIOD, s);
                break;
        case SDLK_TAB:
                set(TAB, s);
                break;
        case SDLK_ESCAPE:
                set(ESCAPE, s);
                break;
        }
}


void c_input::reset(void)
{
        // reset all but scale
        flags = 0;

	// mouse position
        mouse_x = 0;
	mouse_y = 0;
}


uint8_t c_input::get(uint16_t trigger)
{
        if ((flags & trigger) == trigger) {
                set(trigger, 0);
                return 1;
        }

        return 0;
}

void c_input::set(uint16_t trigger, uint8_t bit)
{
        if (bit > 1) {
                bit = 1;
        }

        if (bit == 0) {
                flags &= ~(trigger);
        } else {
                flags |= trigger;
        }
}


uint16_t c_input::get_tile_x(void)
{
	return (uint16_t)(floor(mouse_x / 32));
}


uint16_t c_input::get_tile_y(void)
{
	return (uint16_t)(floor(mouse_y / 32));
}


bool c_input::is_mouse_in_bounds(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	if ((mouse_x < x) || (mouse_x > (x + w))) {
		return false;
        }

	if ((mouse_y < y) || (mouse_y > (y + h))) {
		return false;
        }

	return true;
}


