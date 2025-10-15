#pragma once
#include "Model.h"
#include "QObject"
#include "memory"
class ModelAdapter : public QObject
{
	Q_OBJECT

  private:
	std::unique_ptr<Model> m_model;
	std::unique_ptr<ErrorHandler> error_handler;

  public:
	using ErrorHandlerFunc = std::function<void(ErrorType)>;
	using WallMapUpdatedFunc = std::function<void(void)>;
	using StackPathConfiguredFunc = std::function<void(std::stack<std::pair<int, int>> &)>;
	ModelAdapter(QObject *parent = nullptr);
	Model &GetModel()
	{
		if (!m_model)
		{
			throw std::runtime_error("Model is not initialized");
		}
		return *m_model;
	}
	ErrorHandlerFunc createErrorHandler()
	{
		return [this](ErrorType err)
		{
			emit ErrorHandled(error_handler->getErrorMessage(err));
		};
	}
	WallMapUpdatedFunc createWallMapUpdatedHandler()
	{
		return [this]()
		{
			emit WallMapUpdated();
		};
	}

	StackPathConfiguredFunc createStackPathConfiguredHandler()
	{
		return [this](std::stack<std::pair<int, int>> &stack)
		{
			emit StackPathConfigured(stack);
		};
	}

  public slots:
	void HandleUpdateState(UserInput);
	void HandleFileOperation(UserInput);

  signals:
	void WallMapUpdated();
	void ErrorHandled(const std::string &);
	void StackPathConfigured(std::stack<std::pair<int, int>> &);
};