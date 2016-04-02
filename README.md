##Don't Get Exploded!

Flag those mines and don't get exploded! **Don't Get Exploded** is a single player logic puzzle game involving mines, deductive reasoning, and flags. You know this game. It goes by many names, usually with the word "mine" in the forefront. If for some incredible reason, you are not familiar with this type of game, here's the basic game play rules.

Start the game by selecting a random tile. If the underlying feature is an empty cell, it will expose more tiles until it reaches proximity count tiles. Use the information provided by these proximity count tiles to deduce where the hidden mines are located. Place a flag on the unexposed tile where you believe a mine to rest underneath.

If you expose a tile that has a mine underneath, the game is over. The goal is to correctly flag all assumed mine locations. A counter in the lower right corner indicates how many flags are available to place (based on the difficulty setting). If there are no more available flags to place, and the game hasn't ended in your favor, then some placed flags are incorrect. You may remove placed flags at any time.

#Input

The mouse is used as primary input. Click the **LEFT BUTTON** to expose what lies beneath a top level tile. Click the **RIGHT BUTTON** to place a flag on the unexposed top level tile. To remove a flag that has been place, click the **RIGHT BUTTON** on the flag.

The game is set to easy difficulty by default. You can reset the game to an alternate difficulty setting by using the **F1**, **F2**, and **F3** keys on the keyboard.

F1: New game at **EASY PEASY** difficulty setting. Flag 30 mines.
F2: New game at **I LIKE IT SPICY!** difficulty setting. Flag 60 mines.
F3: New game at **WHY SO SERIOUS?** difficulty setting. Flag 90 mines.
F9: New game at currently selected difficulty setting.

Don't Get Exploded features a visual design that imitates an LCD display. The background can be changed at any time by using the F5, F6, and F7 keys.

F5: Classic LCD.
F6: Blue LCD.
F7: Red LCD.

To exit the game completely, close the game window.

#Compiling

SDL2 (http://www,libsdl.org) is required to compile. Assuming you have the SDL2 library installed, the makefile included should build the game. 

If you have the files arranged as above, simply execute:
`make`

That should compile and create an executable called `dge`.

#Running
After you get the executable, simply run it:

`./dge`

#Notes
There is still a little clean up work to be done, and one or two more features to implement (i.e. screenshot saving), however the game is fully playable. So, grab the code, build it, and enjoy!

#Colophon
I programmed this game in C++ using [VIM](http://www.vim.org/). The graphics were composed with [GIMP](http://www.gimp.org/). This game was developed in a Linux desktop environment.
