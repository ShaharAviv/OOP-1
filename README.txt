Object Oriented Programming ; 2018 a

ex2 : Michael Shriki 305599417 , Kfir Matityahu 205425960

//~~~המטלה הוגשה באיחור של יומיים באישור המרצה עקב מילואים~~~//

This program mimic the PacMan Game via CMD
Warring: we only exept 5 Levels! no less or more, the Levels txt in the project (Board.txt)
the player need to follow the Instructions!!

================================================================================================
Design
------

PACMAN 
Symbole : @. 
Role    : The charcacter that in the control of the user, starts with 3 lives.

DEAMON
Symbole : %. 
Role    : The charcacter that in the control of the "CPU", start appearing from the 2nd level.
          from Level 2 onwards ,the number of the demons grow by 1.

WALL
Symbole : #. 
Role    : A perimeter of the map, used as an obstacle, which the player cant go through it

COOKIE
Symbole : *. 
Role    : The Player's food. Player must finish to eat all the cookies on the level in
          order to get pass to next one

================================================================================================
Files:
------

Board.txt:
The file that includes all the maps for the Game.

main.cpp :
The main Game that we execute.

VectorInt.h:
A struct of 2-size integer vector (x ,y).

settings.h: 
Defines of all the Characters/Keys/text Colors of the game.

messeges.h:
Defines (most of) the Messeges the game ouputs.

util.cpp & util.h:
Include operarions on VectorInt-s.

Board.cpp & Board.h:
Load the board for the current Level and manges drawings.

Demon.cpp & Damon.h:
Class of Deamon, manges the his operaitions.

Player.cpp & Player.h:
Class of the player (Pacman), manges the his operaitions.

Game.cpp & Game.h:
Class of The Game manager. In charge of the all game and movment character on the board ,refresh the board when neseccery.

================================================================================================
Remarkable Algorithms:
----------------------

in util: 
2 Algorithems for a Demon movment
VectorInt shotestDist(VectorInt pac_v, VectorInt deam_v, Board _b);
VectorInt shotestNeib(VectorInt v1, Board _b);
VectorInt copyPlayer(VectorInt v1, VectorInt v2, VectorInt v3, Board _b);

================================================================================================
Known bugs:

None.

================================================================================================
Other notes:

few feature:
Key 's' - skip to the next Level
Key 'r' - restart the current Level
Key 'l' - add one more life to player

================================================================================================