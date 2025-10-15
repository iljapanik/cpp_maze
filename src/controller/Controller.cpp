#include "Controller.h"
#include "ModelAdapter.h"
#include "QApplication"
#include "View.h"
#include "common.h"
Controller::Controller(ModelAdapter &model, View &view, QObject *object) : QObject(object), m_model(model), m_view(view){};

void Controller::Run()
{
	Initialize();
}

void Controller::Initialize()
{
	m_view.InitializeView(m_model.GetModel().GetWallMap());

	connect(&m_view, &View::SendUserInput, &m_model, &ModelAdapter::HandleUpdateState);
	connect(&m_view, &View::FileOperation, &m_model, &ModelAdapter::HandleFileOperation);
	connect(&m_model, &ModelAdapter::WallMapUpdated, &m_view, &View::UpdateScene);
	connect(&m_model, &ModelAdapter::ErrorHandled, &m_view, &View::OnErrorHandled);
	connect(&m_model, &ModelAdapter::StackPathConfigured, &m_view, &View::OnGettingStackCoordinates);
}
