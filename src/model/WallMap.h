#pragma once
#include "Matrix.h"
class WallMap
{
  public:
	WallMap();
	WallMap(int r, int c);
	Matrix m_walls_right;
	Matrix m_walls_bottom;
	Matrix m_digits_matrix;

	void Clear();
};
