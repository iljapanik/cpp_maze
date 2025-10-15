#include "FileWorker.h"

bool FileWorker::ParseMap(const std::string &filename, Matrix &matrix)

{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		return false;
	}
	int rows{0};
	int cols{0};
	try
	{
		ParserInputSize(file, &rows, &cols);
		matrix.resize(rows, cols);
		ParseMatrix(file, rows, cols, matrix);
		file.close();
	}
	catch (...)
	{
		file.close();
		return false;
	}
	return true;
}

bool FileWorker::ParseMap(const std::string &filename, Matrix &m1, Matrix &m2)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		return false;
	}
	int rows{0};
	int cols{0};
	try
	{
		ParserInputSize(file, &rows, &cols);
		m1.resize(rows, cols);
		m2.resize(rows, cols);
		ParseMatrix(file, rows, cols, m1);
		ParseMatrix(file, rows, cols, m2);
		file.close();
		return true;
	}
	catch (...)
	{
		file.close();
		return false;
	}

	return true;
}

bool FileWorker::SaveMapToFile(const std::string &filename, Matrix &m)
{
	std::ofstream file(filename);
	try
	{
		WriteMapSize(file, m.getRows(), m.getCols());
		WriteMatrix(file, m);
		file.close();
	}
	catch (...)
	{
		file.close();
		return false;
	}
	return true;
}

bool FileWorker::SaveMapToFile(const std::string &filename, Matrix &m1, Matrix &m2)
{
	std::ofstream file(filename);
	try
	{
		WriteMapSize(file, m1.getRows(), m1.getCols());
		WriteMatrix(file, m1);
		file << "\n";
		WriteMatrix(file, m2);

		file.close();
	}
	catch (...)
	{
		file.close();
		return false;
	}
	return true;
}

void FileWorker::ParserInputSize(std::ifstream &file, int *rows, int *cols)
{
	std::string line;
	getline(file, line);
	size_t posishion = 0;
	*rows = std::stoi(line, &posishion);
	*cols = std::stoi(line.substr(posishion + 1), &posishion);
}

void FileWorker::ParseMatrix(std::ifstream &file, int rows, int cols, Matrix &matrix)
{

	std::string line;
	while (std::getline(file, line))
	{
		if (!line.empty() && line.find_first_not_of(" \t\r\n") != std::string::npos)
		{
			file.seekg(-static_cast<std::streamoff>(line.length()) - 1, std::ios_base::cur);
			break;
		}
	}

	for (int i = 0; i < rows; i++)
	{
		std::string line;
		getline(file, line);
		for (int j = 0, counterChar = 0; j < cols; j++, counterChar += 2)
		{
			if (line.at(counterChar) == '0')
			{
				matrix(i, j) = 0;
			}
			else if (line.at(counterChar) == '1')
			{
				matrix(i, j) = 1;
			}
			else
			{
				throw std::invalid_argument("Incorrect input");
			}
		}
	}
}

void FileWorker::WriteMapSize(std::ofstream &file, int rows, int cols)
{
	file << rows << " " << cols << '\n';
}
void FileWorker::WriteMatrix(std::ofstream &file, Matrix &m)
{
	for (int i = 0; i < m.getRows(); i++)
	{
		for (int j = 0; j < m.getCols() - 1; j++)
		{
			file << m(i, j) << ' ';
		}
		file << m(i, m.getCols() - 1) << '\n';
	}
}
