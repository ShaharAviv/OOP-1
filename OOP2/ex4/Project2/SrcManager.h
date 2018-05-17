#pragma once
#include <SFML/Graphics.hpp> // reload from settings.h
#include <iostream>
#include "Board.h"

#include <memory>


class SrcManager
{
public:

	// function to build one Singleton
	static std::shared_ptr<SrcManager> instance();
	
	const sf::Texture* getTile(int) const;
    const sf::Font* getFont() const; 
	const sf::Texture* getBoard() const;
	const sf::Texture *getBackGround(int x) const;

private:

	
	SrcManager();
	SrcManager(const SrcManager&) = delete;
	SrcManager& operator=(SrcManager&) = delete;
	static std::shared_ptr<SrcManager> m_src; // Pointer to this class

   // databases' setters
	void setSprits(const char*, std::vector<sf::Sprite>&, int); // load Texture to Sprite Vector's
	void setTexture(std::string path, std::vector<sf::Texture>&, int);
	void setFonts(std::string, int); // load Fonts from files
	void setBoard(std::string);
	
	/***   The DataBases   ***/
	std::vector<sf::Texture> m_Tiles;   // blocks' tiles vector
	std::vector<sf::Texture> m_backgrounds;   // blocks' tiles vector
	sf::Texture m_boardTex;				// board outline texture
	std::vector<sf::Font> m_Fonts;      // fonts Vector
	std::vector<sf::Text> m_Texts;      // Text Object Vector


};