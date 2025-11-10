#ifndef COUNTRYPOLYGONITEM_H
#define COUNTRYPOLYGONITEM_H

#include <QObject>
#include <QGraphicsPolygonItem>
#include "countrydata.h"

#include <QBrush>
#include <QPen>

class CountryPolygonItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

public:
    explicit CountryPolygonItem(const QPolygonF &polygon, const CountryData &countryData,
                                QGraphicsItem *parent = nullptr);

    CountryData data() const;

    void updateAttribute(const QString &key, const QVariant &value);
    void setSelected(bool selected);

signals:
    void clicked(CountryPolygonItem *item, const QPointF &scenePos);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    CountryData m_data;
    QBrush m_defaultBrush;
    QPen   m_defaultPen;
    QBrush m_selectedBrush;
    bool   m_isSelected = false;
};

#endif
