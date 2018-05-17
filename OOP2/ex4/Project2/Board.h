#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Utility.h"
#include "settings.h"

class Piece;
class Block;

class Board 
{
public:
	Board(const sf::Texture &pitTexture, const sf::Vector2i &StartPos);
    
    sf::FloatRect boundingRect() const;
    bool isBlockAtCoordinates(const sf::Vector2i &coords) const;
    bool isBlockInBounds(const sf::Vector2i &coords) const;
    
	void addPieceBlocks(Piece* piece);

    void clear();  
    
    size_t deleteFullRows();
	void deleteRow(int rowNum);
	bool isRowFull(const std::array<std::unique_ptr<Block>, WIDTH>& row);
	void draw(sf::RenderWindow &target) const;

	bool canMovePiece(Piece* tmpPiece) const;
	
	

private:   
    sf::Sprite m_sprite;
	sf::Vector2u m_dimmentions;
	Array2D<std::unique_ptr<Block>, HEIGHT, WIDTH> m_blocks; 

    std::vector<int> m_locationOfFullRows;  //row numbers of the full rows
	void putBlock(const Block& block);

};


