#pragma once

#include <QApplication>
#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>

class CellItem : public QGraphicsItemGroup
{
  private:
	int m_x{};
	int m_y{};

	QGraphicsRectItem *m_rect;
	QGraphicsRectItem *m_right_wall;
	QGraphicsRectItem *m_bottom_wall;
	QGraphicsRectItem *m_left_wall;
	QGraphicsRectItem *m_top_wall;

  public:
	CellItem(int cellSize, int wallThickness, bool bottom, bool right, int x, int y)
	{
		m_rect = new QGraphicsRectItem(0, 0, cellSize, cellSize);
		m_rect->setBrush(Qt::white);
		m_rect->setOpacity(1);
		m_rect->setPen(QPen(Qt::black));

		m_right_wall = new QGraphicsRectItem(cellSize - wallThickness, 0,
											 wallThickness, cellSize);
		if (right)
		{
			m_right_wall->setBrush(Qt::black);
		}
		else
		{
			m_right_wall->setBrush(Qt::white);
		}

		m_right_wall->setPen(Qt::NoPen);

		m_bottom_wall = new QGraphicsRectItem(0, cellSize - wallThickness,
											  cellSize, wallThickness);

		if (bottom)
		{
			m_bottom_wall->setBrush(Qt::black);
		}
		else
		{
			m_bottom_wall->setBrush(Qt::white);
		}

		m_bottom_wall->setPen(Qt::NoPen);

		m_left_wall = new QGraphicsRectItem(0, 0, wallThickness, cellSize);
		m_left_wall->setBrush(Qt::white);
		m_left_wall->setPen(Qt::NoPen);

		m_top_wall = new QGraphicsRectItem(0, 0, cellSize, wallThickness);
		m_top_wall->setBrush(Qt::white);
		m_top_wall->setPen(Qt::NoPen);

		addToGroup(m_rect);
		addToGroup(m_right_wall);
		addToGroup(m_bottom_wall);
		addToGroup(m_left_wall);
		addToGroup(m_top_wall);

		m_x = x;
		m_y = y;
	}
	void SetRightWall(bool cond)
	{
		if (cond)
			m_right_wall->setBrush(Qt::black);
		else
			m_right_wall->setBrush(Qt::white);
	}
	void SetBottomWall(bool cond)
	{
		if (cond)
			m_bottom_wall->setBrush(Qt::black);
		else
			m_bottom_wall->setBrush(Qt::white);
	}

	void SetLeftWall(bool cond)
	{
		if (cond)
			m_left_wall->setBrush(Qt::black);
		else
			m_left_wall->setBrush(Qt::white);
	}

	void SetTopWall(bool cond)
	{
		if (cond)
			m_top_wall->setBrush(Qt::black);
		else
			m_top_wall->setBrush(Qt::white);
	}

	void ColorizeRed()
	{
		m_rect->setBrush(Qt::red);
		update();
	}

	void ColorizeWhite()
	{
		m_rect->setBrush(Qt::white);
		update();
	}

	int GetXMap()
	{
		return m_x;
	}
	int GetYMap()
	{
		return m_y;
	}
};
