#pragma once
#include "CellItem.h"
#include "Controller.h"
#include "MapGraphicsView.h"
#include "QWidget"
#include "QtWidgets"
#include "QTimer"

#include "WallMap.h"
#include "common.h"
#include "memory"
#include <stack>
enum class FindPathStatus
{
	None,
	InititalizePoints,
	Colored
};

enum class PointStatus
{
	One,
	Two,
	None
};

class View : public QWidget
{
	Q_OBJECT

  public:
	View(QWidget *parent = nullptr);
	void InitializeView(const std::shared_ptr<WallMap> &wall_map);

  private:
	std::vector<std::vector<CellItem *>> m_map_items;
	std::weak_ptr<WallMap> m_wall_map;
	Controller *m_controller;

	UserInput m_current_state;
	FindPathStatus m_path_find_status{FindPathStatus::None};
	PointStatus m_points_status{PointStatus::One};
	bool m_clickable{false};
	bool m_points_configurated{false};

	QHBoxLayout *m_common_layout;
	MapGraphicsView *m_view_matrix;
	QGraphicsScene *m_scene_matrix;
	QGraphicsItemGroup *m_items_group;

	QWidget *m_right_widget;

	QVBoxLayout *m_right_layout;
	QHBoxLayout *m_row_col;

	QVBoxLayout *m_generate_layout;
	QHBoxLayout *m_maze_mode;
	QHBoxLayout *m_rows_cols_layout;
	QVBoxLayout *m_rows_layout;
	QVBoxLayout *m_cols_layout;

	QHBoxLayout *m_limits_layout;
	QVBoxLayout *m_limit_birth_layout;
	QVBoxLayout *m_limit_death_layout;
	QVBoxLayout *m_frequency_layout;
	QVBoxLayout *m_chance_alive_layout;

	QVBoxLayout *m_findpath_layout;

	QVBoxLayout *m_file_layout;
	QHBoxLayout *m_file_export_layout;
	QHBoxLayout *m_file_import_layout;

	QPushButton *m_button_maze;
	QPushButton *m_button_cave;
	QButtonGroup *m_button_group;

	QLabel *m_label_rows;
	QLabel *m_label_cols;
	QLabel *m_label_birth;
	QLabel *m_label_death;
	QLabel *m_label_frequency;
	QLabel *m_label_chance_alive;
	QLabel *m_label_generate;
	QLabel *m_label_findpath;
	QLabel *m_label_export_file;
	QLabel *m_label_import_file;

	QSpinBox *m_spinbox_rows;
	QSpinBox *m_spinbox_cols;
	QSpinBox *m_spinbox_birth;
	QSpinBox *m_spinbox_death;
	QSpinBox *m_spinbox_frequency;
	QSpinBox *m_spinbox_chance_alive;

	QPushButton *m_button_generate;
	QPushButton *m_button_rendering;
	QPushButton *m_button_rendering_auto;

	QTimer *m_timer;
	bool m_timer_active;

	QPushButton *m_button_findpath;
	QPushButton *m_button_export;
	QPushButton *m_button_import;

	QGraphicsPathItem* m_pathItem{nullptr};
	


  private:
	void CreatingObjects();
	void PlacingObjects();
	void SetUpObjects();
	void InitializeMatrix();
	void DrawMap();
	void SetWallMap(const std::shared_ptr<WallMap> &wall_map);
	void SetConnections();
	void DrawPath(const std::vector<CellItem*>&path);
	void ClearPath();

  signals:
	void SendUserInput(UserInput);
	void ChangeClickableState(bool);
	void FileOperation(UserInput);

  public slots:
	void OnGettingPointCoord(int x, int y);
	void OnGettingStackCoordinates(std::stack<std::pair<int, int>>&);
	void UpdateScene();
	void OnErrorHandled(const std::string &);
};
