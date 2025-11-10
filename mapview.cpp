#include "mapview.h"
#include <QWheelEvent>
#include <QtMath>

MapView::MapView(QWidget *parent)
    : QGraphicsView(parent)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    scale(1, -1);
}

void MapView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() != 0) {
        double scaleFactor = qPow(1.0015, event->angleDelta().y());
        scale(scaleFactor, scaleFactor);
        event->accept();
    } else {
        QGraphicsView::wheelEvent(event);
    }
}
