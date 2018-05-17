#pragma once
#include "PieceNsize.h"


class I : public PieceNSize<4>
{
public:
	I(const sf::Texture *texture, const sf::Vector2i &pos, short rotationMod);

};

class J : public PieceNSize<4>
{
public:
	J(const sf::Texture *texture, const sf::Vector2i &pos, short rotationMod = 0);

};

class L : public PieceNSize<4>
{
public:
	L(const sf::Texture *texture, const sf::Vector2i &pos, short rotationMod = 0);

};

class O : public PieceNSize<4>
{
public:
	O(const sf::Texture *texture, const sf::Vector2i &pos);

};

class S : public PieceNSize<4>
{
public:
	S(const sf::Texture *texture, const sf::Vector2i &pos, short rotationMod = 0);

};

class Z : public PieceNSize<4>
{
public:
	Z(const sf::Texture *texture, const sf::Vector2i &pos, short rotationMod = 0);

};

class T : public PieceNSize<4>
{
public:
	T(const sf::Texture *texture, const sf::Vector2i &pos, short rotationMod = 0);

};


enum class PieceTypes
{
	I = 0,
	L,
	O,
	S,
	J,
	Z,
	T,

};

constexpr int NORMAL_PIECE_TYPES = 7;
constexpr int SPECIAL_PIECE_TYPES = 4;
static const int NUM_OF_COLORS = 7;