#include "WallMap.h"

WallMap::WallMap() : m_walls_right(), m_walls_bottom() {}

WallMap::WallMap(int r, int c)
	: m_walls_right(r, c),
	  m_walls_bottom(r, c), m_digits_matrix(r, c)
{
}

void WallMap::Clear()
{
	m_walls_right.clear();
	m_walls_bottom.clear();
	m_digits_matrix.clear();
}
