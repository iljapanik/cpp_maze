#pragma once
#include "CellItem.h"
#include <QtWidgets>
class MapGraphicsView : public QGraphicsView
{
	Q_OBJECT
  public:
	using QGraphicsView::QGraphicsView;

  private:
	bool m_clickable{false};

  protected:
	void mousePressEvent(QMouseEvent *event) override
	{
		QPointF scenePos = mapToScene(event->pos());
		QGraphicsItem *item = scene()->itemAt(scenePos, transform());

		if (m_clickable && item)
		{
			if (auto *cell_item = dynamic_cast<CellItem *>(item))
			{
				qDebug() << cell_item->GetXMap() << " " << cell_item->GetYMap();
				emit sendPosCellItem(cell_item->GetXMap(), cell_item->GetYMap());
			}
			else
			{
				auto *group = item->group();
				while (group)
				{
					if (auto *cell_item = dynamic_cast<CellItem *>(group))
					{
						qDebug() << cell_item->GetXMap() << " " << cell_item->GetYMap();
						emit sendPosCellItem(cell_item->GetXMap(), cell_item->GetYMap());
						return;
					}
					group = group->group();
				}

				qDebug() << "clicked not on needed";
			}
		}

		QGraphicsView::mousePressEvent(event);
	}

  signals:
	void sendPosCellItem(int x, int y);

  public slots:
	void OnChangeClickable(bool clickable_state)
	{
		m_clickable = clickable_state;
	}
};
