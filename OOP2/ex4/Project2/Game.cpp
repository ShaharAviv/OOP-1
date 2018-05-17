#include <stdexcept>
#include <iostream>
#include "Game.h"
#include "Utility.h"
#include "Pieces.h"
#include <ctime>
#include "settings.h"


static sf::RenderWindow m_window;		// window of the game
static sf::RenderWindow fullWindow;

//---------------------------------------------------------------------------//
/*
*
*/
Game::Game()
	:m_src(SrcManager::instance()),
	 m_pieceDropped(false),
	 m_isRunning(true),
	 m_isGameOver(false),
	 m_menu(std::make_unique<MainMenu>(sf::Vector2u(800,700)))
{
	srand(unsigned(time(nullptr)));
	initGameState();
	m_window.setFramerateLimit(60);

	m_board = std::make_unique<Board>(*(m_src->getBoard()), PIT_OFFSET);
	auto boardBounds = m_board->boundingRect();
	sf::Vector2i statesPos(int(boardBounds.left + boardBounds.width + 100),
		NEXT_PIECE_OFFSET.y);
	m_gameStates = std::make_unique<States>(*(m_src->getFont()), statesPos);
	m_gameOverText = std::make_unique<sf::Text>
		("\t\tGame Over!\nPress Enter to start a new game.", *(m_src->getFont()));
	m_gameOverText->setPosition(m_window.getSize().x / 4.f, 500.f);

}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::run()
{
	// handle main menu
	auto begin = m_gameClock.getElapsedTime().asSeconds();
	openIntro();
	auto end = m_gameClock.getElapsedTime().asSeconds();
	m_gameStates->addTime((int)std::round(end - begin));

	// handle game's logic
	sf::Event e;
	while (isRunning())
	{
		while (m_window.pollEvent(e))
			handleEvent(e);

		update(m_gameClock.restart());
		render();
		fullWindow.display();
		m_window.display();
	}

	m_window.close();
}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::initGameState()
{
	// reset all game's members 
	sf::VideoMode videoSize = { 800u + (WIDTH - 10u) * 20 ,
								600u + (HEIGHT - 20u) * 20 };

	m_window.create(videoSize, "Tetris", sf::Style::Titlebar);

	
	m_nextPiece = generatePiece(NEXT_PIECE_OFFSET);

	m_currentPiece = generatePiece(PIECE_SPAWN_OFFSET);//std::make_unique<I>(tex, PIECE_SPAWN_OFFSET);
	int r = rand() % (WIDTH - 3 - 3) + 3;

	sf::Vector2i newCoordsPlace = { r,0 };
	m_currentPiece->moveToCoords(std::move(newCoordsPlace));
}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::spawnPiece()
{
	m_currentPiece = std::move(m_nextPiece);
	m_currentPiece->moveToOffset(PIECE_SPAWN_OFFSET);

	int	r = rand() % (WIDTH - 3 - 3) + 3;

	m_currentPiece->moveToCoords(std::move(sf::Vector2i(r, 0)));
	m_nextPiece = generatePiece(NEXT_PIECE_OFFSET);
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Game::resetGameState()
{
	m_board->clear();
	m_gameStates->reset();
	initGameState();
}

//---------------------------------------------------------------------------//
/*
 *
 */
void Game::handleKeyEvent(const sf::Event &e)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		if (m_currentPiece->canMove(*m_board, MOVE_DOWN))
			m_currentPiece->move(0, 1);
	m_pieceDropped = false;

	if (e.type == sf::Event::KeyPressed)
	{
		if (!m_isGameOver)
		{
			switch (e.key.code)
			{
			case sf::Keyboard::Left:
				if (m_currentPiece->canMove(*m_board, MOVE_LEFT))
					m_currentPiece->move(-1, 0);
				break;
			case sf::Keyboard::Right:
				if (m_currentPiece->canMove(*m_board, MOVE_RIGHT))
					m_currentPiece->move(1, 0);
				break;
			case sf::Keyboard::Space:
				m_currentPiece->dropPiece(*m_board);
				m_pieceDropped = true;
				break;
			case sf::Keyboard::Up:
				if (m_currentPiece->canMove(*m_board, ROTATE_RIGHT))
					m_currentPiece->rotate(1);
				break;
			default:
				break;

			}
		}
		// when game is over, you to press enter to continue
		else if (e.key.code == sf::Keyboard::Return)
		{
			m_isGameOver = false;
			resetGameState();
		}
	}

}

//---------------------------------------------------------------------------//
/*
*
*/
bool Game::isRunning() const noexcept
{
	return m_isRunning;
}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::handleEvent(const sf::Event &e)
{
	switch (e.type)
	{
	case sf::Event::Closed:
		m_isRunning = false;
		break;
	case sf::Event::KeyPressed:
		if (e.key.code == PAUSE_KEY)
		{
			auto begin = (int)m_gameClock.getElapsedTime().asSeconds();
			openAsk();
			auto end = (int)m_gameClock.getElapsedTime().asSeconds();

			m_gameStates->addTime((end - begin));
		}
		else
			handleKeyEvent(e);
	default:
		break;

	}
}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::shouldGameEnd()
{
	for (size_t i = 0; i < m_currentPiece->size() && !m_isGameOver; i++)
	{
		if (m_board->isBlockAtCoordinates((*m_currentPiece)[i].coordinates()))
			m_isGameOver = true;
	}
}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::addScore()
{
	int scoreToAdd = 0;
	auto rowsCleared = (int)m_board->deleteFullRows();
	switch (rowsCleared)
	{
		case 1:	scoreToAdd += 50; break;
		case 2: scoreToAdd += 100; break;
		case 3: scoreToAdd += 250; break;
		case 4: scoreToAdd += 700; break;
	}
	if (m_pieceDropped)
		scoreToAdd += 5;

	m_gameStates->setScore(m_gameStates->scoreValue() + scoreToAdd);
}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::update(const sf::Time &delta)
{
	// time Since Last Piece Moved (in seconds)
	static float lastPieceMoved = 0; 
	int scoreToAdd = 0;

	lastPieceMoved += delta.asSeconds();
	if (!m_isGameOver)
	{
		m_gameStates->update(delta);

		//timer is up ,or waiting for a new piece
		if (lastPieceMoved > m_gameStates->getSpeed() ||
			m_currentPiece->isStopped())
		{
			lastPieceMoved = 0.f;

			if (!m_currentPiece->isStopped()
				&& m_currentPiece->canMove(*m_board, MOVE_DOWN))
				m_currentPiece->move(0, 1);		// move down 

			else    // the piece can't move down anymore
			{
				m_currentPiece->setStop(false);

				// adds current Piece's blocks to the pit
				m_board->addPieceBlocks(m_currentPiece.get());

				// if there are full lines, we delete them and add score
				addScore();

				// if there is room, spawn new piece, 
				// else plays lost in the game
				spawnPiece();
				shouldGameEnd();
			}
		}
	}
}

//---------------------------------------------------------------------------//
/*
* Render the game's objects into the game's window
*/
void Game::render() const
{
	m_window.clear(sf::Color(24, 24, 24));

	m_board->draw(m_window);
	m_gameStates->draw(m_window);
	m_nextPiece->draw(m_window);
	m_currentPiece->draw(m_window);

	if (m_isGameOver)
		m_window.draw(*m_gameOverText);

}

//---------------------------------------------------------------------------//
/*
*
*/
std::unique_ptr<Piece> Game::generatePiece(const sf::Vector2i& pos)
{
	auto chosenPiece = PieceTypes(rand() % NORMAL_PIECE_TYPES);
	auto chosenPieceTexture = m_src->getTile(rand() % (NUM_OF_COLORS));
	auto chosenPieceRotation = rand() % 4;

	switch (chosenPiece)
	{
	case PieceTypes::I:
		return std::make_unique<I>(chosenPieceTexture, pos, chosenPieceRotation);
		break;
	case PieceTypes::L:
		return std::make_unique<L>(chosenPieceTexture, pos, chosenPieceRotation);
		break;
	case PieceTypes::O:
		return std::make_unique<O>(chosenPieceTexture, pos);
		break;
	case PieceTypes::S:
		return std::make_unique<S>(chosenPieceTexture, pos, chosenPieceRotation);
		break;
	case PieceTypes::J:
		return std::make_unique<J>(chosenPieceTexture, pos, chosenPieceRotation);
		break;
	case PieceTypes::Z:
		return std::make_unique<Z>(chosenPieceTexture, pos, chosenPieceRotation);
		break;
	case PieceTypes::T:
		return std::make_unique<T>(chosenPieceTexture, pos, chosenPieceRotation);
		break;

	default:
		return nullptr;

	}
}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::openAsk()
{
	const sf::Font f = *(m_src->getFont());
	sf::Text tmp("Are you sure?", f);
	sf::RenderWindow ask(sf::VideoMode(400, 150), "Quit?", sf::Style::Titlebar);
	sf::Event event;
	sf::Text ansY = tmp;
	ansY.setString("Yes");
	sf::Text ansN = tmp;
	ansN.setString("No");
	ansY.setCharacterSize(55);
	ansY.setPosition(75, 30.f);
	ansN.setPosition(250, 30.f);
	ansN.setCharacterSize(55);
	ansY.setFillColor(sf::Color::Red);
	ansN.setFillColor(sf::Color::White);

	while (ask.isOpen())
	{
		while (ask.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Left)
				{
					ansY.setFillColor(sf::Color::Red);
					ansN.setFillColor(sf::Color::White);
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					ansN.setFillColor(sf::Color::Red);
					ansY.setFillColor(sf::Color::White);
				}
				if (event.key.code == sf::Keyboard::Return)
				{
					if (ansY.getFillColor() == sf::Color::Red)
					{
						ask.close();
						m_isRunning = false;
					}
					if (ansN.getFillColor() == sf::Color::Red)
						ask.close();

				}
			}
		}
		ask.draw(ansY);
		ask.draw(ansN);
		ask.display();
		ask.clear();
	}
}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::openIntro()
{
	sf::Event e;

	do {
		while (m_window.pollEvent(e))
		{
			if (e.type == sf::Event::KeyPressed &&
				e.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
				exit(EXIT_SUCCESS);

			}
			if (e.type == sf::Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f currPos = (sf::Vector2f)sf::Mouse::getPosition();
					if (m_menu->isChoosen() == 0)
						return;
					else if (m_menu->isChoosen() == 1)
					{
						m_window.close();
						exit(EXIT_SUCCESS);
					}
				}
			}
		}
		
		m_window.clear();

		m_menu->update(m_window);
		m_menu->draw(m_window);
		m_window.display();
	} while (true);


}