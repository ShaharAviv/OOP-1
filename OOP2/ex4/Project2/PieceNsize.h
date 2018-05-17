#pragma once
#include "Piece.h"

template<int sizeN>
class PieceNSize : public Piece
{
public:
	PieceNSize(const sf::Vector2i &pixelPosition = { 0,0 },
		short rotationMod = 0)
		:Piece(pixelPosition, rotationMod)
	{

	}

	virtual short getRot() const override  { return m_currRotation; }

	void rotate(int d) override;
	void draw(sf::RenderWindow &target) const override;
	void move(int x, int y) override;
	void move(sf::Vector2i newPos);
	void moveToOffset(const sf::Vector2i& offset);
	void moveToCoords(const sf::Vector2i &coordsOfTopLeftBlock);
	sf::Vector2i coordinatesofBlock(size_t BlockNum);
	void moveBlocksToNewPositions(const sf::Vector2i& offset);
	void init(const sf::Texture &blockTexture, sf::Vector2i offsetPos);
	bool canMove(const Board & pit, OPERATION dir) override;

	void dropPiece(const Board & pit) override;

protected:
	std::vector < std::array<sf::Vector2i, sizeN>> m_rotatations;
};


template<int sizeN>
void PieceNSize<sizeN>::rotate(int d)
{
	m_currRotation += d;
	m_currRotation %= m_rotatations.size();
	moveBlocksToNewPositions(m_offset);
}

template<int sizeN>
void PieceNSize<sizeN>::draw(sf::RenderWindow &target) const 
{

	for (const auto &block : m_blocks)
		block.draw(target);

}

template<int sizeN>
void PieceNSize<sizeN>::move(int x, int y)
{
	move({ x,y });
}

template<int sizeN>
void PieceNSize<sizeN>::move(sf::Vector2i newPos)
{
	for (auto& blockPositions : m_rotatations)
		for (auto& blockPosition : blockPositions)
			blockPosition += newPos;

	moveBlocksToNewPositions(m_offset);
}

template<int sizeN>
void PieceNSize<sizeN>::moveToOffset(const sf::Vector2i& offset)
{
	m_offset = offset;
	moveBlocksToNewPositions(m_offset);
}

template<int sizeN>
void PieceNSize<sizeN>::moveToCoords(const sf::Vector2i &topLeftBlockCoords)
{
	sf::Vector2i coordOffset;
	coordOffset.x = topLeftBlockCoords.x - m_rotatations[m_currRotation][0].x;
	coordOffset.y = topLeftBlockCoords.y - m_rotatations[m_currRotation][0].y;

	for (auto& rotation : m_rotatations)
		for (auto& coords : rotation)
		{
			coords.x += coordOffset.x;
			coords.y += coordOffset.y;
		}

	moveBlocksToNewPositions(m_offset);
}

template<int sizeN>
sf::Vector2i PieceNSize<sizeN>::coordinatesofBlock(size_t BlockNum)
{
	return m_rotatations[m_currRotation][BlockNum];
}

template<int sizeN>
void PieceNSize<sizeN>::moveBlocksToNewPositions(const sf::Vector2i& offset)
{
	for (size_t i = 0; i < m_blocks.size(); i++)
	{
		auto rotationPosition = m_rotatations[m_currRotation];
		m_blocks[i].moveAbsolute(rotationPosition[i], offset);
	}
}

template<int sizeN>
void PieceNSize<sizeN>::init(const sf::Texture &blockTexture, sf::Vector2i offsetPos)
{

	for (int i = 0; i < sizeN; i++)
	{
		m_blocks.emplace_back(
			Block(blockTexture,
				offsetPos + m_rotatations[m_currRotation][i] * 20,
				m_rotatations[m_currRotation][i]));

	}
}

template<int sizeN>
bool PieceNSize<sizeN>::canMove(const Board & pit, OPERATION dir)
{
	auto tmpPiece = std::make_shared<PieceNSize<sizeN>>(*this);
	switch (dir)
	{
	case MOVE_DOWN:       tmpPiece->move(0, 1);    break;
	case MOVE_LEFT:       tmpPiece->move(-1, 0);   break;
	case MOVE_RIGHT:      tmpPiece->move(1, 0);    break;
	case ROTATE_LEFT:     tmpPiece->rotate(-1);    break;
	case ROTATE_RIGHT:    tmpPiece->rotate(1);     break;
	default:								      break;
	}


	return pit.canMovePiece(tmpPiece.get());

}

template<int sizeN>
void PieceNSize<sizeN>::dropPiece(const Board & pit)
{
	while (canMove(pit, MOVE_DOWN))
		move(0, 1);

	m_isStopped = true;
}


