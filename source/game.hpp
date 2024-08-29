//
// Don't Get Exploded!
// Copyright 2022 - 2024, Brian Puthuff
//
// See LICENSE.md for details.
//


#pragma once


#include "input.hpp"
#include "video.hpp"
#include "playfield.hpp"


class c_game
{
	public:
        void init(void);
	void play(void);
	
	private:
        uint8_t state;
        uint8_t difficulty;
        uint8_t flags;
        uint8_t mines;
	uint8_t message;
        c_playfield playfield;
	c_input input;
	c_video video;
	void handle_palette_change(void);
	uint8_t handle_left_click(void);
	void handle_right_click(void);
	void check_function_resets(void);
	void sweep(int16_t x, int16_t y);
	uint8_t correct_flags(void);
	bool is_win(void);
	void explode(void);
	void victory(void);

        // data handling
        void reset(void);
        void set_difficulty(uint8_t setting);
        bool set_flag(void);
        bool restore_flag(void);

        // rendering
        void render(void);
        void render_playfield(void);
        void render_data(void);
};
