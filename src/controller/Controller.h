#pragma once
#include <QObject>
class ModelAdapter;
class View;
class Controller : public QObject
{
  public:
	Controller(ModelAdapter &model, View &view, QObject *object = nullptr);
	void Run();

	//   private slots:
	void HandleStateChanged();

  private:
	ModelAdapter &m_model;
	View &m_view;

	void Initialize();
};
