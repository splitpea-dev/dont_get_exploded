# Don't Get Exploded!

## Description

Flag those mines and don't get exploded! **Don't Get Exploded** is a single player logic puzzle game involving mines, deductive reasoning, and flags. You know this game. It goes by many names, usually with the word "mine" in the forefront. If for some incredible reason, you are not familiar with this type of game, here's the basic game play rules:

Start the game by selecting a random tile. If the underlying feature is an empty cell, it will expose more tiles until it reaches proximity count tiles. Use the information provided by these proximity count tiles to deduce where the hidden mines are located. Place a flag on the unexposed tile where you believe a mine is resting underneath.

If you expose a tile that has a mine underneath, the game is over. The goal is to correctly flag all assumed mine locations. A counter in the lower right corner indicates how many flags are available to place (based on the difficulty setting). If there are no more available flags to place, and the game hasn't ended in your favor, then some placed flags are incorrect. You may remove placed flags at any time.

![Sample Screenshot](./sample_screenshot.png)

## Input

The mouse is used as primary input. Click the **LEFT BUTTON** to expose what lies beneath a top level tile. Click the **RIGHT BUTTON** to place a flag on the unexposed top level tile. To remove a flag that has been place, click the **RIGHT BUTTON** on the flag.

The game is set to medium difficulty by default. You can reset the game to an alternate difficulty setting by using the **F1**, **F2**, and **F3** keys on the keyboard.

``F1``- New game at **EASY PEASY** difficulty setting. Flag 30 mines.

``F2``- New game at **I LIKE IT SPICY!** difficulty setting. Flag 60 mines.

``F3``- New game at **WHY SO SERIOUS?** difficulty setting. Flag 90 mines.

``F9``- New game (**RESET**) at the currently selected difficulty setting.

To exit the game completely, close the game window.

<br>

## Compiling notes

SDL2 and SDL2_image (https://www.libsdl.org) development libraries are required to compile/build. Assuming you have both the SDL2 and SDL2_image development libraries installed, the makefile included should build the game.

Simply type ``make`` and press ``ENTER``.

That should build an executable called ``dge``.

**NOTE:** SDL2 and SDL2_image shared object files are required to run the final program.

<br>

## License

This program employes the BSD 3-clause license. See the ``LICENSE.md`` file for details.

