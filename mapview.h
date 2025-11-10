#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QObject>

class QWheelEvent;

class MapView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = nullptr);

protected:
    virtual void wheelEvent(QWheelEvent *event) override;
};

#endif
