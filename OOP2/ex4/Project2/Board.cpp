#include "Board.h"
#include "Pieces.h"

#include <algorithm>
#include <memory>

//---------------------------------------------------------------------------//
/*
*
*/
Board::Board(const sf::Texture &pitTexture, const sf::Vector2i &StartPos)
	:m_sprite(pitTexture), m_dimmentions(WIDTH,HEIGHT)
{
	m_sprite.setPosition(std::move(sf::Vector2f(StartPos)));
	m_sprite.scale(float(WIDTH / 10.f), float(HEIGHT / 20.f));
}

//---------------------------------------------------------------------------//
/*
*
*/
void Board::draw(sf::RenderWindow &target) const
{
	target.draw(m_sprite);

	for (auto& blockRow : m_blocks)
	{
		for (auto& block : blockRow)
			if (block)
				(*block).draw(target);
	}
}

//---------------------------------------------------------------------------//
/*
*
*/
bool Board::canMovePiece(Piece * tmpPiece) const
{
	for (size_t i = 0; i < tmpPiece->size(); i++)
	{
		if (!isBlockInBounds(tmpPiece->coordinatesofBlock(i))
			|| isBlockAtCoordinates(tmpPiece->coordinatesofBlock(i)))
			return false;
	}

	return true;
}

//---------------------------------------------------------------------------//
/*
*
*/
sf::FloatRect Board::boundingRect() const
{
	return m_sprite.getGlobalBounds();
}

//---------------------------------------------------------------------------//
/*
*
*/
bool Board::isBlockInBounds(const sf::Vector2i &coords) const
{
	return (coords.x < WIDTH && coords.x >= 0)
		&& (coords.y >= -3 && coords.y < HEIGHT);
}

//---------------------------------------------------------------------------//
/*
*
*/
bool Board::isBlockAtCoordinates(const sf::Vector2i &coords) const
{
	if (coords.y < 0)
		return m_blocks.at(1).at(coords.x) != nullptr;
	try
	{
		m_blocks.at(coords.y).at(coords.x);
	}
	catch (std::exception&)
	{
		return true;
	}
	return m_blocks.at(coords.y).at(coords.x) != nullptr;
}

//---------------------------------------------------------------------------//
/*
*
*/
void Board::putBlock(const Block& block)
{
	sf::Vector2i coords = block.coordinates();
	try {
		m_blocks.at(coords.y).at(coords.x) = std::make_unique<Block>(block);
		if (isRowFull(m_blocks.at(coords.y)))
			m_locationOfFullRows.push_back(coords.y);
	}
	catch (std::exception&) {
		;
	}
}

//---------------------------------------------------------------------------//
/*
*
*/
void Board::addPieceBlocks(Piece* piece)
{
	for (size_t index = 0; index < piece->size(); index++)
		putBlock((*piece)[index]);

}

//---------------------------------------------------------------------------//
/*
 * clears the board.  used when reseting for a new game
 */
void Board::clear()
{
	for (size_t rowNum = 0; rowNum < HEIGHT; rowNum++)
		std::for_each(m_blocks[rowNum].begin(), m_blocks[rowNum].end(),
			[](std::unique_ptr<Block>& block) {block.reset(); });

}

//---------------------------------------------------------------------------//
/*
 *  deletes and returns number of rows deleted
 */
size_t Board::deleteFullRows()
{
	size_t fullRowsNum = m_locationOfFullRows.size();

	for (auto& rowNum : m_locationOfFullRows)
		deleteRow(rowNum);

	m_locationOfFullRows.clear();

	return fullRowsNum;
}

//---------------------------------------------------------------------------//
/*
*
*/
void Board::deleteRow(int rowNum)
{
	//delete the row
	std::for_each(m_blocks[rowNum].begin(), m_blocks[rowNum].end(),
		[](std::unique_ptr<Block>& block) { block.reset(); });

	//move other rows down
	for (auto it = m_blocks.begin() + rowNum; it != m_blocks.begin(); it--)
	{
		*it = std::move(*(it - 1));

		for (auto& block : *it)
			if (block)
				block->moveDown();
	}
}

//---------------------------------------------------------------------------//
/*
*
*/
bool Board::isRowFull(const std::array<std::unique_ptr<Block>, WIDTH>& row)
{
	return std::all_of(row.begin(), row.end(),
		[](const std::unique_ptr<Block>& it) { return it != nullptr;  });
}
