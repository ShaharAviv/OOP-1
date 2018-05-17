#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "SrcManager.h"
#include "Utility.h"
#include "Pieces.h"
#include "States.h" 
#include "MainMenu.h"

class Game
{
public:
    Game();
	void openIntro();
	void run();


private:
    std::unique_ptr<Board> m_board;
    std::unique_ptr<Piece> m_nextPiece;
    std::unique_ptr<Piece> m_currentPiece;
    std::unique_ptr<States> m_gameStates;
    std::unique_ptr<sf::Text> m_gameOverText;
	
	std::shared_ptr<SrcManager> m_src;
	std::unique_ptr<MainMenu> m_menu;
	
	bool m_pieceDropped;
	bool m_isRunning;
    bool m_isGameOver;
	sf::Clock m_gameClock;

	// main game's functions
	void initGameState();
	void handleEvent(const sf::Event &e);
	void update(const sf::Time &delta);
	void render() const;
	bool isRunning() const noexcept;

	//prototypes for helper functions
	std::unique_ptr<Piece> generatePiece(const sf::Vector2i& pos);
	void shouldGameEnd();
	void addScore();
	void spawnPiece();
    void handleKeyEvent(const sf::Event &e);
	void resetGameState();

	void openAsk();
};

