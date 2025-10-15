#include "Matrix.h"

Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

Matrix::Matrix(int rows, int cols)
{
	rows_ = rows;
	cols_ = cols;
	matrix_ = new int *[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix_[i] = new int[cols]();
	}
}

Matrix::~Matrix()
{
	if (matrix_)
	{
		for (int i = 0; i < rows_; i++)
		{
			delete[] matrix_[i];
		}
		delete[] matrix_;
		matrix_ = nullptr;
	}
}

Matrix::Matrix(const Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new int*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new int[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

Matrix Matrix::operator=(const Matrix &other)
{
	this->~Matrix();
	rows_ = other.rows_;
	cols_ = other.cols_;
	matrix_ = new int *[rows_];
	for (int i = 0; i < rows_; i++)
	{
		matrix_[i] = new int[cols_];
		for (int j = 0; j < cols_; j++)
		{
			matrix_[i][j] = other.matrix_[i][j];
		}
	}

	return *this;
}

int &Matrix::operator()(int i, int j) { return matrix_[i][j]; }

bool Matrix::checkMatrix()
{
	bool check = true;

	if (rows_ <= 0 || rows_ > 50)
	{
		check = false;
	}
	else if (cols_ <= 0 || cols_ > 50)
	{
		check = false;
	}
	else
	{
		for (int i = 0; i < rows_; i++)
		{
			for (int j = 0; j < cols_; i++)
			{
				if (matrix_[i][j] != 0 || matrix_[i][j] != 1)
				{
					check = false;
					throw std::invalid_argument("Incorrect value");
				}
			}
		}
	}

	return check;
}

void Matrix::resize(int rows, int cols)
{
	if (matrix_)
	{
		for (int i = 0; i < rows_; ++i)
			delete[] matrix_[i];
		delete[] matrix_;
	}

	rows_ = rows;
	cols_ = cols;
	matrix_ = new int *[rows_];
	for (int i = 0; i < rows_; ++i)
	{
		matrix_[i] = new int[cols_]{};
	}
}

void Matrix::clear()
{
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			matrix_[i][j] = 0;
		}
	}
}