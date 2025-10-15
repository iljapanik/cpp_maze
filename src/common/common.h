#pragma once
#include <string>
enum class MapType
{
	Maze,
	Cave
};

enum class FileOperationType
{
	None,
	Export,
	Import
};

enum class UserAction
{
	Generate,
	FileOperation,
	FindPath,
	Update,
	None,
};

enum class DeathLimit
{
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven
};

enum class BirthLimit
{
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven
};

struct UserInput
{
	MapType type{MapType::Maze};

	// for generation
	int rows{0};
	int cols{0};

	// for finding a path
	int pointA_x{0};
	int pointA_y{0};
	int pointB_x{0};
	int pointB_y{0};

	FileOperationType file_operation_type{FileOperationType::Export};
	std::string filename;

	UserAction user_action{UserAction::None};

	DeathLimit death_limit;
	BirthLimit birth_limit;
	int frequency{100}; // частота отрисовки итераций при нажатии на клавишу.

	int chance; // сюда можешь добавить доп переменные по пещерам, которых не хватает
};
