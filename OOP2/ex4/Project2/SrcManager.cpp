
#include "SrcManager.h"
static const std::string IMAGE_PATH = R"(res\images\)";
static const std::string FONT_PATH = R"(res\fonts\)";

//---------------------------------------------------------------------------//
/*
 *
 */
SrcManager::SrcManager()
{
	setFonts(FONT_PATH, 1); // 2 instead of NUM_OF_FONTS
	setBoard(IMAGE_PATH);
	setTexture(IMAGE_PATH + "bg", m_backgrounds, 1);
	setTexture(IMAGE_PATH + "tile", m_Tiles, 7); // 12 instead of NUM_OF_BUTTONS 

}

//---------------------------------------------------------------------------//
/*
 *	this function return one pointer to this class
 */

std::shared_ptr<SrcManager> SrcManager::instance()
{
	static std::shared_ptr<SrcManager> m_src(new SrcManager());
	return m_src;
}

//---------------------------------------------------------------------------//
/*
 *	this function return Button from the vector
 */

const sf::Texture* SrcManager::getTile(int i) const
{
	try {
		(&(m_Tiles.at(i)));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(1);
	}
	return (&(m_Tiles.at(i)));
}

//---------------------------------------------------------------------------//
/*
 *	this function return Font from the vector
 */
const sf::Font* SrcManager::getFont() const
{
	try {
		return (&(m_Fonts.at(0)));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(1);
	}
}

//---------------------------------------------------------------------------//
const sf::Texture * SrcManager::getBoard() const
{
	return (&(m_boardTex));
}

//---------------------------------------------------------------------------//
const sf::Texture * SrcManager::getBackGround(int x) const
{
	try {
		return (&(m_backgrounds.at(0)));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(1);
	}
}



///////////////////// setters /////////////////////////////
//---------------------------------------------------------------------------//
/*
 *
 */
void SrcManager::setSprits(const char* path, std::vector<sf::Sprite> &vector, int size)
{
	for (int i = 0; i < size; ++i)
	{
		sf::Sprite tmp;
		sf::Texture tx;
		tx.loadFromFile(path + std::to_string(i) + ".png");
		tmp.setTexture(std::move(tx));
		vector.emplace_back(std::move(tmp));
	}
}

//---------------------------------------------------------------------------//
/*
 *
 */
void SrcManager::setTexture(std::string path, std::vector<sf::Texture> &vector, int size)
{
	for (int i = 0; i < size; ++i)
	{
		sf::Texture tmp;
		tmp.loadFromFile(path + std::to_string(i) + ".png");
		vector.emplace_back(std::move(tmp));
	}

}


//---------------------------------------------------------------------------//
/*
 *	this function set Fonts Object to his vector
 */

void SrcManager::setFonts(std::string path, int size)
{
	sf::Font tmp;

	tmp.loadFromFile(std::string(path) + "simplistic_regular.ttf");
	m_Fonts.emplace_back(std::move(tmp));

}

void SrcManager::setBoard(std::string path)
{
	sf::Texture tmp;
	tmp.loadFromFile(path + "board.png");
	m_boardTex = std::move(tmp);
}



