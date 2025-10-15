#pragma once
#include "Matrix.h"
#include <fstream>
class FileWorker
{
  public:
	bool ParseMap(const std::string &filename, Matrix &matrix);
	bool ParseMap(const std::string &filename, Matrix &m1, Matrix &m2);

	bool SaveMapToFile(const std::string &filename, Matrix &m);
	bool SaveMapToFile(const std::string &filename, Matrix &m1, Matrix &m2);

  private:
	void ParserInputSize(std::ifstream &file, int *rows, int *cols);
	void ParseMatrix(std::ifstream &file, int rows, int cols, Matrix &matrix);
	void WriteMapSize(std::ofstream &file, int rows, int cols);
	void WriteMatrix(std::ofstream &file, Matrix &m);
};