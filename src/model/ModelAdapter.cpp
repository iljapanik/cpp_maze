#include "ModelAdapter.h"

ModelAdapter::ModelAdapter(QObject *parent) : QObject(parent)
{
    	error_handler = std::make_unique<ErrorHandler>();
		m_model = std::make_unique<Model>(createErrorHandler(), createWallMapUpdatedHandler(), createStackPathConfiguredHandler());

}

void ModelAdapter::HandleUpdateState(UserInput user_input)
{
	m_model->HandleUpdateState(user_input);
}
void ModelAdapter::HandleFileOperation(UserInput user_input)
{
	m_model->HandleFileOperation(user_input);
}