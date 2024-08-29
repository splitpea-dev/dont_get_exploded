//
// Don't Get Exploded!
// Copyright 2022 - 2024, Brian Puthuff
//
// See LICENSE.md for details.
//

#include <iostream>


#include "SDL2/SDL.h"


#include "defines.hpp"
#include "game.hpp"


void c_game::init(void)
{
	// initialize things
	set_difficulty(I_LIKE_IT_SPICY);
        playfield.clear();

	input.init();
	video.init();

        input.scale = video.scale;
}


void c_game::play(void)
{
	bool is_running;
	uint8_t kaboom;
        uint64_t tick;
        double elapsed_ms;


        kaboom = 0;
        is_running = true;
	while (is_running == true) {
                // start frame tick
                tick = SDL_GetPerformanceCounter();
		input.update();
		if (input.get(ESCAPE) == 1) {
			is_running = false;
                        continue;
                }
                handle_palette_change();
		check_function_resets();
                handle_right_click();
                kaboom = handle_left_click();

                // game logic
                if (kaboom == 1) {
                        explode();
                        kaboom = 0;
                }

                if (is_win() == true) {
                        victory();
                }

		render();
	
                // end tick; add delay if necessary
                do {
                        elapsed_ms = (double)(SDL_GetPerformanceCounter() - tick) / (double)SDL_GetPerformanceFrequency() * 1000.0f;
                } while (elapsed_ms < (double)(1000.0f / (double)60));
	}

        video.clean_up();
}


uint8_t c_game::handle_left_click(void)
{
	uint16_t x;
	uint16_t y;
        uint16_t i;
        

	if (state == GAME_ENDED) {
		return 0;
        }

	if (input.get(LEFT_MOUSE_BUTTON) == 0) {
                return 0;
        }

	if (input.is_mouse_in_bounds(0, 0, RENDER_WIDTH, RENDER_WIDTH) == false) {
                return 0;
        }


	x = input.get_tile_x();
	y = input.get_tile_y();
        i = (PLAYFIELD_WIDTH * y) + x;

	if (state == PLAYING_FIRST_MOVE) {
		playfield.generate(i, mines);
		state = PLAYING;
	}

	sweep((int16_t)x, (int16_t)y);

	if (playfield.cells[i].below == MINE) {
                playfield.cells[i].below = EXPLODED_MINE;
		return 1;
	}

	return 0;
}


void c_game::handle_right_click(void)
{
	uint16_t x;
	uint16_t y;
        uint16_t i;


	if ((state == GAME_ENDED) || (state == PLAYING_FIRST_MOVE)) {
		return;
        }

        if (input.get(RIGHT_MOUSE_BUTTON) == 0) {
                return;
        }
        
        if (input.is_mouse_in_bounds(0, 0, RENDER_WIDTH, RENDER_WIDTH) == false) {
                return;
        }

	x = input.get_tile_x();
	y = input.get_tile_y();
        i = (PLAYFIELD_WIDTH * y) + x;

	if (playfield.cells[i].above == DIRT) {
		if (set_flag() == true) {
			playfield.cells[i].above = FLAG;
                }
	} else if (playfield.cells[i].above == FLAG) {
		if (restore_flag() == true) {
			playfield.cells[i].above = DIRT;
                }
	} else;
}


void c_game::handle_palette_change(void)
{
	if (input.get(COMMA) == 1) {
		video.prev_palette();
        }

	if (input.get(PERIOD) == 1) {
		video.next_palette();
        }
}


void c_game::check_function_resets(void)
{
	bool fk_pressed = false;


	if (input.get(F1) == 1) {
		set_difficulty(EASY_PEASY);
		fk_pressed = true;
	}

	if (input.get(F2) == 1) {
		set_difficulty(I_LIKE_IT_SPICY);
		fk_pressed = true;
	}

	if (input.get(F3) == 1 ) {
		set_difficulty(WHY_SO_SERIOUS);
		fk_pressed = true;
	}

	if(input.get(F9)) {
		reset();
		fk_pressed = true;
	}

	if (fk_pressed == true) {
		playfield.clear();
		state = PLAYING_FIRST_MOVE;
	}
}


void c_game::sweep(int16_t x, int16_t y)
{
	int16_t c;
	int16_t r;
        uint16_t i;


        // if out of bounds, break
	if ((x < 0) || (x >= PLAYFIELD_WIDTH)) {
		return;
        }
	if ((y < 0) || (y >= PLAYFIELD_HEIGHT)) {
		return;
        }

        i = (PLAYFIELD_WIDTH * y) + x;
	// if playfield is already exposed, break
	if (playfield.cells[i].above == EXPOSED) {
		return;
        }

        // ...
	if (playfield.cells[i].above == FLAG) {
		restore_flag();
        }

	// expose playfield
	playfield.cells[i].above = EXPOSED;

	// if not empty below, we are done
	if (playfield.cells[i].below > EMPTY) {
		return;
        }

	for (r = -1; r < 2; r += 1) {
		for (c = -1; c < 2; c += 1) {
			sweep((x + c), (y + r));
		}
	}
}


uint8_t c_game::correct_flags(void)
{
	uint16_t i;
        uint8_t count;


        count = 0;
	for (i = 0; i < PLAYFIELD_AREA; i += 1) {
		if ((playfield.cells[i].above == FLAG) && (playfield.cells[i].below == MINE)) {
			count += 1;
                }
	}
        return count;
}


bool c_game::is_win (void)
{
	if (correct_flags() == mines) {
		return true;
        }

	return false;
}


void c_game::explode(void)
{
	message = YOU_GOT_EXPLODED;
	playfield.explode();
	state = GAME_ENDED;
}


void c_game::victory(void)
{
	message = YOU_FLAGGED_ALL_THE_MINES;
	state = GAME_ENDED;
}


void c_game::render(void)
{
	video.clear_renderer();
	render_data();
        render_playfield();
	video.present_renderer();
}


void c_game::render_data(void)
{
	video.render_tile((message + MESSAGE_OFFSET), 0, 640);
        video.render_tile((difficulty + DIFFICULTY_OFFSET), 480, 640);
        video.render_tile(SPACER_OFFSET, 512, 640);
        video.render_tile(FLAG_OFFSET, 544, 640);
        video.render_tile(((flags % 10) + NUMBER_OFFSET), 608, 640);
        video.render_tile(((flags / 10) + NUMBER_OFFSET), 576, 640);
}


void c_game::render_playfield(void)
{
	uint8_t i;
        //uint8_t b;
        //uint8_t a;
	uint16_t x;
	uint16_t y;
        uint16_t p;


	i = 0;
	for (y = 0; y < PLAYFIELD_HEIGHT; y += 1) {
		for (x = 0; x < PLAYFIELD_WIDTH; x += 1) {
                        p = (PLAYFIELD_WIDTH * y) + x;
                        //a = playfield.cells[p].above;
                        //b = playfield.cells[p].below;	
			if (playfield.cells[p].above == EXPOSED) {
				switch (playfield.cells[p].below) {
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
					i = 6 + playfield.cells[p].below;
					break;
				}
			} else {
				switch (playfield.cells[p].above)  {
                                default:
				case DIRT:
					i = 0;
					break;
				case FLAG:
					i = 1;
					break;
				case INCORRECT_FLAG:
					i = 2;
                                        break;
				}
			}
                        video.render_tile(i, (x * 32), (y * 32));
		}
	}			
}


void c_game::set_difficulty(uint8_t setting)
{
	if (setting > WHY_SO_SERIOUS) {
		setting = WHY_SO_SERIOUS;
        }

	difficulty = setting;
	switch (difficulty) {
	case EASY_PEASY:
		mines = 30;
		break;
	case I_LIKE_IT_SPICY:
		mines = 60;
		break;
	case WHY_SO_SERIOUS:
		mines = 90;
		break;
	}
        reset();
}


void c_game::reset(void)
{
	message = DONT_GET_EXPLODED;
	flags = mines;
        state = PLAYING_FIRST_MOVE;
}


bool c_game::set_flag(void)
{
	if (flags > 0) {
		flags -= 1;
		return true;
	}

	return false;
}


bool c_game::restore_flag(void)
{
	if (flags < mines) {
		flags += 1;
		return true;
	}

	return false;
}