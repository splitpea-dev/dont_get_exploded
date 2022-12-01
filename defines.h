/*
** Don't Get Exploded!
** Copyright 2022, Brian Puthuff
**
** See LICENSE.md for details.
*/


#ifndef DEFINES_H
#define DEFINES_H


// GRAPHICS_H
// renderer dimensions
#define RENDER_WIDTH              640
#define RENDER_HEIGHT             672

// window title
#define WINDOW_TITLE              "Don't Get Exploded!"

// graphics file
#define TILES_FILENAME            "./tiles.png"
#define ICON_FILENAME             "./icon.png"

// GAME_H
// game states
#define PLAYING_FIRST_MOVE        ( uint8_t ) 0
#define PLAYING                   ( uint8_t ) 1
#define GAME_ENDED                ( uint8_t ) 2

// playfield dimensions
#define PLAYFIELD_WIDTH           20
#define PLAYFIELD_HEIGHT          20


// DATA_H
// difficulty modes
#define EASY_PEASY                ( uint8_t ) 0
#define I_LIKE_IT_SPICY           ( uint8_t ) 1
#define WHY_SO_SERIOUS            ( uint8_t ) 2

// message states
#define DONT_GET_EXPLODED         ( uint8_t ) 0
#define YOU_FLAGGED_ALL_THE_MINES ( uint8_t ) 1
#define YOU_GOT_EXPLODED          ( uint8_t ) 2

// PLAYFIELD_H
// top layer types
#define EXPOSED                   ( uint8_t ) 0
#define DIRT                      ( uint8_t ) 1
#define FLAG                      ( uint8_t ) 2
#define INCORRECT_FLAG            ( uint8_t ) 3

// bottom layer types
#define EMPTY                     ( uint8_t ) 0
#define MINE                      ( uint8_t ) 9
#define FLAGGED_MINE              ( uint8_t ) 10
#define EXPLODED_MINE             ( uint8_t ) 11

// INPUT_H
// input identifiers
#define MOUSE_BUTTON_LEFT         ( uint8_t ) 0
#define MOUSE_BUTTON_RIGHT        ( uint8_t ) 1
#define KEY_F1                    ( uint8_t ) 2
#define KEY_F2                    ( uint8_t ) 3
#define KEY_F3                    ( uint8_t ) 4
#define KEY_F9                    ( uint8_t ) 5
#define KEY_TAB                   ( uint8_t ) 6
#define KEY_COMMA		  ( uint8_t ) 7
#define KEY_PERIOD                ( uint8_t ) 8 
#define EXIT                      ( uint8_t ) 9

// PALETTES_H
// palette limits
#define PALETTES_FILENAME         "./palettes.hex"
#define PALETTES_LIMIT            ( uint8_t ) 16
#define COLORS_LIMIT              ( uint8_t ) 4

#endif
