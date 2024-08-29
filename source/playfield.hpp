//
// Don't Get Exploded!
// Copyright 2022 - 2024, Brian Puthuff
//
// See LICENSE.md for details.
//


#pragma once


#include <cstdint>


#include "defines.hpp"


struct s_cell
{
	uint8_t above;
	uint8_t below;
};


class c_playfield
{
        public:
        s_cell cells[PLAYFIELD_AREA];
        void clear(void);
        void generate(uint16_t position, uint8_t number_of_mines);
        void explode(void);
        void print(void);
        
        private:
        void add_proximity_counts(void);
        uint8_t mine_check(int16_t x, int16_t y);
};




