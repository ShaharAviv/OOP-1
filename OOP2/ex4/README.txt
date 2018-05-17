Object Oriented Programming ; 2018 b

ex4 : Michael Shriki, Kfir Matityahu

This program is a Tetris Game!!

================================================================================================
Files: 
--------------------------------
(^ X : inheritance from Class X)

Piece.h:
an abstract class for the Pieces.

PieceNsize.cpp & PieceNsize.h:
Template calls that handle all the Pieces. (^ Piece)

Pieces.cpp & Pieces.h:
Contain all the Piece classes (S, I, Z, J, T, L, O). (^ PieceNsize)

Block.cpp & Block.h:
create block.

Board.cpp & Board.h:
Handle the game board.

Game.cpp & Game.h:
Handle the all game

MainMenu.cpp & MainMenu.h:
The manu for the game.

SrcManager.cpp & SrcManager.h:
The source manager for all the images & font.

States.cpp & States.h:
Handle the Piece state on the board

================================================================================================
Data Structures:
-------------------------------
std::vector<Block> m_blocks;
Vector of Block's objects 
std::vector<sf::Texture> m_Tiles;   
blocks' tiles vector
std::vector<sf::Texture> m_backgrounds;   
blocks' tiles vector
sf::Texture m_boardTex;				
board outline texture
std::vector<sf::Font> m_Fonts;     
fonts Vector
std::vector<sf::Text> m_Texts;      
Text Object Vector

================================================================================================
Remarkable Algorithms:
--------------------------------
None.

================================================================================================
Known bugs:
--------------------------------
None.

================================================================================================
Other Notes:
--------------------------------
Windows SDK used in program is 16299

================================================================================================