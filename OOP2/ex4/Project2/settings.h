#pragma once
#include "SFML/Graphics/Texture.hpp"


const auto PAUSE_KEY = sf::Keyboard::Escape;

constexpr int HEIGHT = 20;			// default = 20
constexpr int WIDTH = 10;			// default = 10

constexpr int PIT_WALL_WIDTH = 5;   //how many pixels is the wall of the pit?
const sf::Vector2i PIT_OFFSET = { 250, 65 };

const sf::Vector2i PIECE_SPAWN_OFFSET = 
{ PIT_OFFSET.x + PIT_WALL_WIDTH, PIT_OFFSET.y + PIT_WALL_WIDTH };

const sf::Vector2i NEXT_PIECE_OFFSET = { PIT_OFFSET.x - 180, PIT_OFFSET.y + 75 };
const sf::Vector2i SCORE_POSITION = 
{ NEXT_PIECE_OFFSET.x - 310, NEXT_PIECE_OFFSET.y };