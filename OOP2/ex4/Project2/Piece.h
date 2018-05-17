#pragma once
#include "Block.h"

enum OPERATION
{
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT
};


class Piece
{
public:
	Piece(const sf::Vector2i &pixelPosition = { 0,0 },
		short rotationMod = 0, bool f = true);

	virtual sf::Vector2i coordinatesofBlock(size_t BlockNum) = 0;

	virtual void rotate(int d) = 0;
	virtual void move(int x, int y) = 0;
	virtual void init(const sf::Texture &blockTexture,/* const*/ sf::Vector2i /*&*/offsetPosition) = 0;

	virtual void moveToOffset(const sf::Vector2i& offset) = 0; //moves piece to a pixel position
	virtual void moveToCoords(const sf::Vector2i  &coordsOfTopLeftBlock) = 0;
	virtual void draw(sf::RenderWindow &target) const = 0;

	virtual size_t size() const;
	virtual Block operator[](size_t blockNum) const;


	virtual bool canMove(const Board & pit, OPERATION dir) = 0;
	virtual void dropPiece(const Board& pit) = 0;

	virtual void setStop(bool flag) { m_isStopped = false; }
	virtual bool isStopped() const { return m_isStopped; }

	virtual void moveBlocksToNewPositions(const sf::Vector2i& offset) = 0;
	virtual void move(sf::Vector2i) = 0;
	virtual short getRot() const = 0;


protected:
	short m_currRotation;
	sf::Vector2i m_offset;
	std::vector<Block> m_blocks;

	bool m_isStopped;
	bool m_canDestroy = true;

};