#include "Vertex.h"
#include "macros.h"
#include <ostream>

bool Vertex::isHigherThan(const Vertex& other) const
{
    return (m_y > other.m_y);
}

bool Vertex::isRighterThan(const Vertex& other) const
{
    return (m_x > other.m_x);
}

bool Vertex::isValid() const
{
    return m_x >= 0 && m_x <= MAX_X && m_y >= 0 && m_y <= MAX_Y;
}
/*
std::ostream & operator<<(std::ostream & output, const Vertex& vert)
{
	output << vert.m_x << "," << vert.m_y << "\n";
	return output;
}*/
