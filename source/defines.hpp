//
// Don't Get Exploded!
// Copyright 2022 - 2024, Brian Puthuff
//
// See LICENSE.md for details.
//


#pragma once


// GRAPHICS_H
// renderer dimensions
#define RENDER_WIDTH              640
#define RENDER_HEIGHT             672


// window title
#define WINDOW_TITLE              "Don't Get Exploded!"


// graphics file
#define TILES_FILENAME            "./tiles/tiles.png"
#define ICON_FILENAME             "./tiles/icon.png"


// game states
#define PLAYING_FIRST_MOVE        0
#define PLAYING                   1
#define GAME_ENDED                2


// playfield dimensions
#define PLAYFIELD_WIDTH           20
#define PLAYFIELD_HEIGHT          20
#define PLAYFIELD_AREA            400


// clips
#define CLIPS                     33
#define DIFFICULTY_OFFSET         15
#define SPACER_OFFSET             18
#define FLAG_OFFSET               19
#define NUMBER_OFFSET             20
#define MESSAGE_OFFSET            30


// difficulty modes
#define EASY_PEASY                0
#define I_LIKE_IT_SPICY           1
#define WHY_SO_SERIOUS            2


// message states
#define DONT_GET_EXPLODED         0
#define YOU_FLAGGED_ALL_THE_MINES 1
#define YOU_GOT_EXPLODED          2


// top layer types
#define EXPOSED                   0
#define DIRT                      1
#define FLAG                      2
#define INCORRECT_FLAG            3


// bottom layer types
#define EMPTY                     0
#define MINE                      9
#define FLAGGED_MINE              10
#define EXPLODED_MINE             11


// input
#define LEFT_MOUSE_BUTTON         1
#define RIGHT_MOUSE_BUTTON        2
#define F1                        4
#define F2                        8
#define F3                        16
#define F9                        32
#define TAB                       64
#define COMMA                     128
#define PERIOD                    256
#define UNUSED_A                  512
#define UNUSED_B                  1024
#define UNUSED_C                  2048
#define UNUSED_D                  4096
#define UNUSED_E                  8192
#define ESCAPE                    16384


// palette limits
#define PALETTES_FILENAME         "./palettes/palettes.hex"
#define PALETTES                  16
#define COLORS                    4

