//
// Don't Get Exploded!
// Copyright 2022 - 2024, Brian Puthuff
//
// See LICENSE.md for details.
//


#include <iostream>


#include "playfield.hpp"


void c_playfield::clear(void)
{
	uint16_t i;


	for (i = 0; i < PLAYFIELD_AREA; i += 1) {
		cells[i].above = DIRT;
		cells[i].below = EMPTY;
	}
}


void c_playfield::generate(uint16_t position, uint8_t number_of_mines)
{	
	uint16_t i;
	uint16_t r;


	clear();

	// add mines
	for (i = 0; i < number_of_mines; i += 1) {
		do {
			r = rand() % PLAYFIELD_AREA;
		}
		while ((cells[r].below > EMPTY) || (r == position));
		cells[r].below = MINE;
	}
	
	add_proximity_counts();
}


void c_playfield::add_proximity_counts(void)
{
	uint8_t count;
	int16_t x;
	int16_t y;
	uint16_t i;


	for (y = 0; y < PLAYFIELD_HEIGHT; y += 1) {
		for (x = 0; x < PLAYFIELD_WIDTH; x += 1) {
			count = 0;
			i = (uint16_t)((y * PLAYFIELD_WIDTH) + x);
			if (cells[i].below == EMPTY) {
				count += mine_check(x - 1, y - 1);
				count += mine_check(x, y - 1);
				count += mine_check(x + 1, y - 1);
				count += mine_check(x - 1, y);
				count += mine_check(x + 1, y);
				count += mine_check(x - 1, y + 1);
				count += mine_check(x, y + 1);
				count += mine_check(x + 1, y + 1);
				cells[i].below = count;
			}
		}
	}		
}


uint8_t c_playfield::mine_check(int16_t x, int16_t y)
{
	// out of bounds
	if ((x < 0) || (y < 0)) {
		return 0;
        }

	// outof bounds
	if ((x >= PLAYFIELD_WIDTH) || (y >= PLAYFIELD_HEIGHT)) {
		return 0;
        }

	// in bounds check for mine
	if (cells[((y * PLAYFIELD_WIDTH) + x)].below == MINE) {
		return 1;
        }

	return 0;
}


void c_playfield::explode(void)
{
	uint16_t i;
	

	for (i = 0; i < PLAYFIELD_AREA; i += 1) {
		if (cells[i].above == FLAG) {
			if (cells[i].below == MINE) {
				cells[i].below = FLAGGED_MINE;
				cells[i].above = EXPOSED;
			} else {
				cells[i].above = INCORRECT_FLAG;
			}
		}
		
		// expose all hidden mines that were not flagged
		if (cells[i].above == DIRT) {
			if (cells[i].below == MINE) {
				cells[i].above = EXPOSED;
                        }
		}
	}
}


void c_playfield::print(void)
{
	uint8_t x;
	uint8_t y;
	uint16_t p;


	for (y = 0; y < PLAYFIELD_HEIGHT; y += 1) {
		for (x = 0; x < PLAYFIELD_WIDTH; x += 1) {
			p = (uint16_t)((y * PLAYFIELD_WIDTH) + x);
			std::cout << (int)cells[p].below;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

