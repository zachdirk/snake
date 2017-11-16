This is a project I did for fun to learn SDL2 in CPP. It's the snake game that everyone is familiar with.
It's my first project using SDL2 so things are not good. But they work.

Quirky design choices:
    -Hitting the edge of the screen wraps you around instead of killing you.
    -You can move diagonally by holding a vertical and horizontal direction at the same time. 
     Crossing over the snake this way will not kill you (assuming you don't land in a snake square anyways)

To run (dunno why you would) you'll need SDL2.dll which is downloadable from the SDL website.
The program can be executed two ways:
    -no arguments defaults to a 24 by 24 grid with grid cells that are 20 pixels wide and tall
    -3 arguments can be given that define the number of rows, number of columns and cell size in that order

Controls:
    -arrow keys to move
    -spacebar to pause/unpause
    -esc to reset (even after loss)

Problems:
    -using a cell size less than 5 pixels wrecks the graphics

Things I would add if I had more time:
    -win screen
    -start menu with difficulties
    -pause menu
    -sounds
