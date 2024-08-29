//
// Don't Get Exploded!
// Copyright 2022 - 2024, Brian Puthuff
//
// See LICENSE.md for details.
//


#pragma once


class c_input
{
        public:
        uint8_t scale;
        uint16_t flags;
	int16_t mouse_x;
	int16_t mouse_y;
        void init(void);
	void update (void);
	void reset(void);
	uint8_t get(uint16_t trigger);
        void set(uint16_t trigger, uint8_t b);
	uint16_t get_tile_x(void);
	uint16_t get_tile_y(void);
	bool is_mouse_in_bounds(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

        private:
        void handle_key(uint32_t type, int32_t keycode);
        void handle_mouse_button(uint32_t type, uint8_t button);
};

