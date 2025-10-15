#pragma once
#include <map>
#include <string>
enum class ErrorType
{
	IncorrectRowsCols,
};

class ErrorHandler
{
  private:
	std::map<ErrorType, std::string> errorsMap = {
		{ErrorType::IncorrectRowsCols, "Incorrect rows or cols"}};

  public:
	std::string getErrorMessage(ErrorType error) const
	{
		auto it = errorsMap.find(error);
		if (it != errorsMap.end())
		{
			return it->second;
		}
		return "Unknown error";
	}
};