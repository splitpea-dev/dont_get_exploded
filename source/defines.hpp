<<<<<<< HEAD:defines.h
/*
** Don't Get Exploded!
<<<<<<< HEAD
** Copyright 2022, Brian Puthuff
=======
** Copyright 2022 - 2024, Brian Puthuff
>>>>>>> 41dc873 (General refactoring.)
**
** See LICENSE.md for details.
*/
=======
//
// Don't Get Exploded!
// Copyright 2022 - 2024, Brian Puthuff
//
// See LICENSE.md for details.
//
>>>>>>> aab6ec1 (Refactored.):source/defines.hpp


<<<<<<< HEAD
#ifndef DEFINES_H
#define DEFINES_H
=======
#pragma once
>>>>>>> 41dc873 (General refactoring.)


// GRAPHICS_H
// renderer dimensions
#define RENDER_WIDTH              640
#define RENDER_HEIGHT             672

// window title
#define WINDOW_TITLE              "Don't Get Exploded!"

// graphics file
<<<<<<< HEAD:defines.h
#define TILES_FILENAME            "./tiles.png"
#define ICON_FILENAME             "./icon.png"

<<<<<<< HEAD
// GAME_H
// game states
#define PLAYING_FIRST_MOVE        ( uint8_t ) 0
#define PLAYING                   ( uint8_t ) 1
#define GAME_ENDED                ( uint8_t ) 2
=======
// special tiles
#define TILE_DIRT                 18
#define TILE_FLAG                 19
=======
#define TILES_FILENAME            "./tiles/tiles.png"
#define ICON_FILENAME             "./tiles/icon.png"
>>>>>>> aab6ec1 (Refactored.):source/defines.hpp

#define CLIPS                     33

// GAME_H
// game states
#define PLAYING_FIRST_MOVE        (uint8_t) 0
#define PLAYING                   (uint8_t) 1
#define GAME_ENDED                (uint8_t) 2
>>>>>>> 41dc873 (General refactoring.)

// playfield dimensions
#define PLAYFIELD_WIDTH           20
#define PLAYFIELD_HEIGHT          20
#define PLAYFIELD_AREA            400


// DATA_H
// clip offsets
#define DIFFICULTY_OFFSET         15
#define SPACER_OFFSET             18
#define FLAG_OFFSET               19
#define NUMBER_OFFSET             20
#define MESSAGE_OFFSET            30

// difficulty modes
<<<<<<< HEAD
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
=======
#define EASY_PEASY                (uint8_t) 0
#define I_LIKE_IT_SPICY           (uint8_t) 1
#define WHY_SO_SERIOUS            (uint8_t) 2

// message states
#define DONT_GET_EXPLODED         (uint8_t) 0
#define YOU_FLAGGED_ALL_THE_MINES (uint8_t) 1
#define YOU_GOT_EXPLODED          (uint8_t) 2


// PLAYFIELD_H
// top layer types
#define EXPOSED                   (uint8_t) 0
#define DIRT                      (uint8_t) 1
#define FLAG                      (uint8_t) 2
#define INCORRECT_FLAG            (uint8_t) 3

// bottom layer types
#define EMPTY                     (uint8_t) 0
#define MINE                      (uint8_t) 9
#define FLAGGED_MINE              (uint8_t) 10
#define EXPLODED_MINE             (uint8_t) 11

// INPUT_H
// input identifiers
<<<<<<< HEAD:defines.h
#define MOUSE_BUTTON_LEFT         (uint8_t) 0
#define MOUSE_BUTTON_RIGHT        (uint8_t) 1
#define KEY_F1                    (uint8_t) 2
#define KEY_F2                    (uint8_t) 3
#define KEY_F3                    (uint8_t) 4
#define KEY_F9                    (uint8_t) 5
#define KEY_TAB                   (uint8_t) 6
#define KEY_COMMA		  (uint8_t) 7
#define KEY_PERIOD                (uint8_t) 8 
#define EXIT                      (uint8_t) 9
>>>>>>> 41dc873 (General refactoring.)

// PALETTES_H
// palette limits
#define PALETTES_FILENAME         "./palettes.hex"
<<<<<<< HEAD
#define PALETTES_LIMIT            ( uint8_t ) 16
#define COLORS_LIMIT              ( uint8_t ) 4

#endif
=======
#define PALETTES_LIMIT            (uint8_t) 16
#define COLORS_LIMIT              (uint8_t) 4
>>>>>>> 41dc873 (General refactoring.)
=======
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

// PALETTES_H
// palette limits
#define PALETTES_FILENAME         "./palettes/palettes.hex"
#define PALETTES                  16
#define COLORS                    4
>>>>>>> aab6ec1 (Refactored.):source/defines.hpp
