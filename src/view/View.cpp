#include "View.h"
#include <QMessageBox>
View::View(QWidget *parent) : QWidget(parent)
{
	// resize(550, 550);
}



void View::InitializeView(const std::shared_ptr<WallMap> &wall_map)
{
	SetWallMap(wall_map);

	CreatingObjects();
	PlacingObjects();
	SetUpObjects();
	InitializeMatrix();

	SetConnections();
	this->show();
	this->setFocus();
}

void View::CreatingObjects()
{
	m_common_layout = new QHBoxLayout();
	m_view_matrix = new MapGraphicsView(this);
	m_right_widget = new QWidget(this);
	m_right_layout = new QVBoxLayout();
	m_row_col = new QHBoxLayout();

	m_scene_matrix = new QGraphicsScene(this);
	m_items_group = new QGraphicsItemGroup();

	m_generate_layout = new QVBoxLayout();
	m_maze_mode = new QHBoxLayout();
	m_rows_cols_layout = new QHBoxLayout();
	m_limits_layout = new QHBoxLayout();

	m_rows_layout = new QVBoxLayout();
	m_cols_layout = new QVBoxLayout();
	m_button_maze = new QPushButton("Maze");
	m_button_cave = new QPushButton("Cave");
	m_button_group = new QButtonGroup();

	m_limit_birth_layout = new QVBoxLayout();
	m_limit_death_layout = new QVBoxLayout();
	m_frequency_layout = new QVBoxLayout();
	m_chance_alive_layout = new QVBoxLayout();
	m_label_rows = new QLabel("Rows:", this);
	m_label_cols = new QLabel("Cols:", this);
	m_label_birth = new QLabel("Birth rate:", this);
	m_label_death = new QLabel("Death rate:", this);
	m_label_frequency = new QLabel("Freq:", this);
	m_label_chance_alive = new QLabel("alive, %:", this);
	m_spinbox_rows = new QSpinBox(this);
	m_spinbox_cols = new QSpinBox(this);
	m_spinbox_birth = new QSpinBox(this);
	m_spinbox_death = new QSpinBox(this);
	m_spinbox_frequency = new QSpinBox(this);
	m_spinbox_chance_alive = new QSpinBox(this);
	m_button_generate = new QPushButton("Generate", this);
	m_button_rendering = new QPushButton("Rendering", this);
	m_button_rendering_auto = new QPushButton("Rendering auto", this);

	m_timer = new QTimer(this);
	m_timer_active = false;
	
	m_file_layout = new QVBoxLayout();
	m_file_export_layout = new QHBoxLayout();
	m_file_import_layout = new QHBoxLayout();
	m_button_export = new QPushButton("Export");
	m_button_import = new QPushButton("Import");

	m_findpath_layout = new QVBoxLayout();
	m_button_findpath = new QPushButton("Find a path", this);
}

void View::PlacingObjects()
{
	m_view_matrix->setScene(m_scene_matrix);
	m_view_matrix->resize(550, 550);

	m_scene_matrix->addItem(m_items_group);

	m_right_widget->setFixedSize(300, 500);
	m_right_widget->setLayout(m_right_layout);
	m_common_layout->addWidget(m_view_matrix);

	m_maze_mode->addWidget(m_button_maze);
	m_maze_mode->addWidget(m_button_cave);

	m_rows_layout->addWidget(m_label_rows);
	m_rows_layout->addWidget(m_spinbox_rows);
	m_cols_layout->addWidget(m_label_cols);
	m_cols_layout->addWidget(m_spinbox_cols);
	m_rows_cols_layout->addLayout(m_rows_layout);
	m_rows_cols_layout->addLayout(m_cols_layout);
	m_generate_layout->addLayout(m_rows_cols_layout);
	m_generate_layout->addLayout(m_limits_layout);
	m_generate_layout->addWidget(m_button_generate);
	m_generate_layout->addWidget(m_button_rendering);
	m_generate_layout->addWidget(m_button_rendering_auto);


	m_limit_birth_layout->addWidget(m_label_birth);
	m_limit_birth_layout->addWidget(m_spinbox_birth);
	m_limit_death_layout->addWidget(m_label_death);
	m_limit_death_layout->addWidget(m_spinbox_death);
	m_frequency_layout->addWidget(m_label_frequency);
	m_frequency_layout->addWidget(m_spinbox_frequency);
	m_chance_alive_layout->addWidget(m_label_chance_alive);
	m_chance_alive_layout->addWidget(m_spinbox_chance_alive);
	m_limits_layout->addLayout(m_limit_birth_layout);
	m_limits_layout->addLayout(m_limit_death_layout);
	m_limits_layout->addLayout(m_frequency_layout);
	m_limits_layout->addLayout(m_chance_alive_layout);

	m_file_layout->addWidget(m_button_export);

	m_file_layout->addWidget(m_button_import);

	m_right_layout->addLayout(m_maze_mode);
	m_right_layout->addLayout(m_generate_layout, 0);
	m_right_layout->addWidget(m_button_findpath, 0);
	m_right_layout->addLayout(m_file_layout, 0);
	m_right_layout->addStretch(1);

	m_common_layout->addWidget(m_right_widget);
	;

	this->setLayout(m_common_layout);

	m_common_layout->setContentsMargins(0, 0, 0, 0);
	m_common_layout->setSpacing(0);

	m_right_layout->setContentsMargins(0, 0, 0, 0);
	m_right_layout->setSpacing(0);

	m_generate_layout->setContentsMargins(0, 0, 0, 0);
	m_generate_layout->setSpacing(0);

	m_rows_cols_layout->setContentsMargins(0, 0, 0, 0);
	m_rows_cols_layout->setSpacing(0);

	m_rows_layout->setContentsMargins(0, 0, 0, 0);
	m_rows_layout->setSpacing(0);

	m_cols_layout->setContentsMargins(0, 0, 0, 0);
	m_cols_layout->setSpacing(0);

	m_findpath_layout->setContentsMargins(0, 0, 0, 0);
	m_findpath_layout->setSpacing(0);

	m_file_layout->setContentsMargins(0, 0, 0, 0);
	m_file_layout->setSpacing(0);

	m_file_export_layout->setContentsMargins(0, 0, 0, 0);
	m_file_export_layout->setSpacing(0);

	m_file_import_layout->setContentsMargins(0, 0, 0, 0);
	m_file_import_layout->setSpacing(0);

	m_right_layout->setSpacing(20);
	m_file_layout->setSpacing(5);
	m_generate_layout->setSpacing(5);
}

void View::SetUpObjects()
{
	m_view_matrix->resize(600, 600);
	// m_right_layout->size

	m_spinbox_rows->setMinimum(1);
	m_spinbox_rows->setMaximum(50);

	m_spinbox_cols->setMinimum(1);
	m_spinbox_cols->setMaximum(50);

	m_spinbox_birth->setMinimum(0);
	m_spinbox_birth->setMaximum(7);

	m_spinbox_death->setMinimum(0);
	m_spinbox_death->setMaximum(7);

	m_spinbox_frequency->setMinimum(100);
	m_spinbox_frequency->setMaximum(10000);

	m_spinbox_chance_alive->setMinimum(0);
	m_spinbox_chance_alive->setMaximum(100);

	m_button_maze->setCheckable(true);
	m_button_maze->setChecked(true);
	m_button_cave->setCheckable(true);
	m_button_group->addButton(m_button_maze);
	m_button_group->addButton(m_button_cave);
	m_button_group->setExclusive(true);
	m_label_birth->hide();
	m_label_death->hide();
	m_label_frequency->hide();
	m_label_chance_alive->hide();
	m_spinbox_birth->hide();
	m_spinbox_death->hide();
	m_spinbox_frequency->hide();
}

void View::InitializeMatrix()
{
	if (auto wallmap = m_wall_map.lock())
	{
		if (m_items_group)
		{
			QList<QGraphicsItem *> children = m_items_group->childItems();
			for (QGraphicsItem *child : children)
			{
				m_items_group->removeFromGroup(child);
				delete child;
			}
		}
		m_map_items.clear();
		m_map_items.resize(wallmap->m_walls_right.getRows());
		for (auto &row : m_map_items)
		{
			row.resize(wallmap->m_walls_right.getCols(), nullptr);
		}

		int cell_size = 500 / std::max(wallmap->m_walls_right.getRows(), wallmap->m_walls_right.getCols());

		for (int i = 0; i < wallmap->m_walls_right.getRows(); i++)
		{
			for (int j = 0; j < wallmap->m_walls_right.getCols(); j++)
			{
				m_map_items[i][j] = new CellItem(cell_size, 2, false, false, j, i);
				m_map_items[i][j]->setPos(j * cell_size, i * cell_size);
				m_items_group->addToGroup(m_map_items[i][j]);
			}
		}

		for (int j = 0; j < wallmap->m_walls_right.getCols(); j++)
		{
			m_map_items[0][j]->SetTopWall(true);
		}

		for (int i = 0; i < wallmap->m_walls_right.getRows(); i++)
		{
			m_map_items[i][0]->SetLeftWall(true);
		}
	}
}

void View::DrawMap()
{
	if (auto wallmap = m_wall_map.lock())
	{
		for (int i = 0; i < wallmap->m_walls_right.getRows(); i++)
		{
			for (int j = 0; j < wallmap->m_walls_right.getCols(); j++)
			{
				m_map_items[i][j]->ColorizeWhite();

				if(m_current_state.type == MapType::Maze)
				{
					if (wallmap->m_walls_right(i, j) == 1)
						m_map_items[i][j]->SetRightWall(true);
					else
						m_map_items[i][j]->SetRightWall(false);

					if (wallmap->m_walls_bottom(i, j) == 1)
						m_map_items[i][j]->SetBottomWall(true);
					else
						m_map_items[i][j]->SetBottomWall(false);
				} else 
				{
					if (wallmap->m_walls_right(i, j) == 1) 
					{
						m_map_items[i][j]->ColorizeRed();
					}
				}

			}
		}
	}
}

void View::SetWallMap(const std::shared_ptr<WallMap> &wall_map)
{
	m_wall_map = wall_map;
}

void View::SetConnections()
{
	connect(m_button_generate, &QPushButton::clicked, this, [this]()
			{
				m_current_state.user_action = UserAction::Generate;
				m_current_state.rows = m_spinbox_rows->value();
				m_current_state.cols = m_spinbox_cols->value();
				m_current_state.death_limit = (DeathLimit)m_spinbox_death->value();
				m_current_state.birth_limit = (BirthLimit)m_spinbox_birth->value();
				m_current_state.chance = m_spinbox_chance_alive->value();
				m_current_state.type = (m_button_maze->isChecked() ? MapType::Maze : MapType::Cave);
				emit SendUserInput(m_current_state); });

	connect(this, &View::ChangeClickableState, m_view_matrix, &MapGraphicsView::OnChangeClickable);

	connect(m_button_findpath, &QPushButton::clicked, this, [this]()
			{
				if (m_path_find_status == FindPathStatus::None){
					m_path_find_status = FindPathStatus::InititalizePoints;
					m_points_status = PointStatus::One;
					emit ChangeClickableState(true);
					DrawMap();
				}
				else if (m_path_find_status == FindPathStatus::InititalizePoints)
				{
					m_path_find_status = FindPathStatus::Colored;
					emit ChangeClickableState(false);
					m_current_state.user_action = UserAction::FindPath;
					emit SendUserInput(m_current_state);
				}
				else if (m_path_find_status == FindPathStatus::Colored){
					DrawMap();
					ClearPath();
					m_path_find_status = FindPathStatus::None;
				}
			});

	connect(m_button_rendering, &QPushButton::clicked, this, [this]()
			{
				
				m_current_state.user_action = UserAction::Update;
				m_current_state.death_limit = (DeathLimit)m_spinbox_death->value();
				m_current_state.birth_limit = (BirthLimit)m_spinbox_birth->value();
					
				emit SendUserInput(m_current_state); });

	connect(m_button_rendering_auto, &QPushButton::clicked, this, [this]()
			{
				if (m_timer_active == true) 
				{	
					m_timer->stop();
					m_timer_active = false;
					m_current_state.user_action = UserAction::None;
				} 
				else 
				{
					m_timer->start();
					m_timer_active = true;
					m_current_state.user_action = UserAction::None;
					m_current_state.death_limit = (DeathLimit)m_spinbox_death->value();
					m_current_state.birth_limit = (BirthLimit)m_spinbox_birth->value();
					m_current_state.frequency = m_spinbox_frequency->value();
				}		
					
				emit SendUserInput(m_current_state); });



	connect(m_timer, &QTimer::timeout, this, [this]()
			{
				if (m_timer_active == true) 
				{	
					m_timer->stop();
					m_timer->setInterval(m_current_state.frequency);
					m_timer->start();
					m_current_state.user_action = UserAction::Update;
					m_current_state.death_limit = (DeathLimit)m_spinbox_death->value();
					m_current_state.birth_limit = (BirthLimit)m_spinbox_birth->value();
					m_current_state.frequency = m_spinbox_frequency->value();

				} 
				else 
				{
					m_current_state.user_action = UserAction::None;
				}
				emit SendUserInput(m_current_state); });
				

	connect(m_view_matrix, &MapGraphicsView::sendPosCellItem, this, &View::OnGettingPointCoord);

	m_spinbox_chance_alive->hide();
	m_button_rendering->hide();
	m_button_rendering_auto->hide();
	connect(m_button_group, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),
			this, [&](QAbstractButton *btn, bool checked)
			{if (btn == m_button_maze) {
			m_current_state.type = MapType::Maze;
			m_label_birth->hide();
			m_label_death->hide();
			m_label_frequency->hide();
			m_label_chance_alive->hide();
			m_button_rendering->hide();
			m_button_rendering_auto->hide();

			m_spinbox_birth->hide();
			m_spinbox_death->hide();
			m_spinbox_frequency->hide();
			m_spinbox_chance_alive->hide();
		}
		else if (btn == m_button_cave)
		{
			m_current_state.type = MapType::Cave;
			m_label_birth->show();
			m_label_death->show();
			m_label_frequency->show();
			m_label_chance_alive->show();
			m_button_rendering->show();
			m_button_rendering_auto->show();

			m_spinbox_birth->show();
			m_spinbox_death->show();
			m_spinbox_frequency->show();
			m_spinbox_chance_alive->show();
		} });

	m_button_maze->setStyleSheet(R"(
    QPushButton {
        background-color: lightgray;
        border: 1px solid gray;
        padding: 5px;
    }
    QPushButton:checked {
        background-color: lightblue;
        border: 2px solid blue;
    }
)");

	m_button_cave->setStyleSheet(R"(
    QPushButton {
        background-color: lightgray;
        border: 1px solid gray;
        padding: 5px;
    }
    QPushButton:checked {
        background-color: lightblue;
        border: 2px solid blue;
    }
	)");

	connect(m_button_import, &QPushButton::clicked, this, [this]()
			{ QString fileName = QFileDialog::getOpenFileName(
				  this, "Выберите файл", QString(), ""); 

	if (!fileName.isEmpty())
	{
		m_current_state.filename = fileName.toStdString();
		m_current_state.file_operation_type = FileOperationType::Import;
		emit FileOperation(m_current_state);
	} });

	connect(m_button_export, &QPushButton::clicked, this, [this]()
			{ QString fileName = QFileDialog::getSaveFileName(
				  this, "Назовите файл", QString(), ""); 

	if (!fileName.isEmpty())
	{
		m_current_state.filename = fileName.toStdString();
		m_current_state.file_operation_type = FileOperationType::Export;
		emit FileOperation(m_current_state);
	} });
};

void View::DrawPath(const std::vector<CellItem *> &path)
{
	if (m_pathItem)
	{
		m_scene_matrix->removeItem(m_pathItem);
		delete m_pathItem;
		m_pathItem = nullptr;
	}

	if (path.empty())
		return;

	QPainterPath painterPath;
	painterPath.moveTo(path[0]->mapToScene(path[0]->boundingRect().center()));

	for (size_t i = 1; i < path.size(); ++i)
	{
		painterPath.lineTo(path[i]->mapToScene(path[i]->boundingRect().center()));
	}

	m_pathItem = new QGraphicsPathItem(painterPath);

	m_pathItem->setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	m_scene_matrix->addItem(m_pathItem);
}

void View::ClearPath()
{
	if (m_pathItem)
	{
		m_scene_matrix->removeItem(m_pathItem);
		delete m_pathItem;
		m_pathItem = nullptr;
	}
}

void View::OnGettingPointCoord(int x, int y)
{
	if (m_points_status == PointStatus::One)
	{
		m_current_state.pointA_x = x;
		m_current_state.pointA_y = y;
		m_points_status = PointStatus::Two;

		m_map_items[m_current_state.pointA_y][m_current_state.pointA_x]->ColorizeRed();
	}
	else if (m_points_status == PointStatus::Two)
	{
		m_current_state.pointB_x = x;
		m_current_state.pointB_y = y;
		m_points_status = PointStatus::None;
		m_map_items[m_current_state.pointB_y][m_current_state.pointB_x]->ColorizeRed();
	}
}

void View::OnGettingStackCoordinates(std::stack<std::pair<int, int>> &stack_path)
{
	std::vector<CellItem *> path;
	while (!stack_path.empty())
	{
		auto [x, y] = stack_path.top();
		stack_path.pop();
		path.push_back(m_map_items[y][x]);
	}
	DrawPath(path);
}

void View::UpdateScene()
{
	if (auto wallmap = m_wall_map.lock())
	{
		// if (wallmap->m_walls_right.getRows() != m_map_items.size() || wallmap->m_walls_right.getCols() != m_map_items[0].size())
		InitializeMatrix();

		DrawMap();
	}
}

void View::OnErrorHandled(const std::string &error_msg)
{
	qDebug() << "HER";
	QMessageBox::critical(this, "Error", QString::fromStdString(error_msg));
}
