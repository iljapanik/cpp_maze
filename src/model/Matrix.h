#ifndef S21_MATRIX_BACK_OPP_H
#define S21_MATRIX_BACK_OPP_H

#include <stdexcept>

class Matrix
{

  public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(const Matrix& other);
	~Matrix();
	int getRows() { return rows_; }
	int getCols() { return cols_; }
	Matrix operator=(const Matrix &other);
	int &operator()(int i, int j);
	bool checkMatrix();
	void resize(int rows, int cols);
	void clear();

  private:
	int rows_, cols_;
	int **matrix_;
};

#endif
