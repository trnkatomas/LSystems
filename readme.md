# LSystems
This program was originally created as a school project at CTU in Prague.
As the name suggest it is a simple program that creates images of grammars for so called L-Systems. The images are shown with Turtle graphics and are 2D only.

## Usage

The usage of the program is as follows, the symbol on keyboard stands for certain action of the program.

    o	open file
    <	pan left
    >	pan right
    ^	pan up
    v	pan down
    r	rotate by 90deg
    +	zoom in
    -	zoom out
    p	save current canvas as png
    z	reset viewpoint
    space	next generation
    h	this help
    q	quit

## Input files

The input file must have following structure otherwise the program will either draw nonsense graphics or will crash.

    all symols separated by space
    axiom
    rules in form A->B 
    degree for turn

Example of grammar for a plant:

    X F + - [ ]
    X
    X -> F-[[X]+X]+F[+FX]-X
    F -> FF
    25
