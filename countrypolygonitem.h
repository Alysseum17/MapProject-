#ifndef COUNTRYPOLYGONITEM_H
#define COUNTRYPOLYGONITEM_H

#include <QObject>
#include <QGraphicsItemGroup>
#include "countrydata.h"
#include <QPointF>
#include <QBrush>
#include <QPen>
#include <QPainterPath>


class CountryPolygonItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:
    explicit CountryPolygonItem(const CountryData &countryData,
                                QGraphicsItem *parent = nullptr);
    CountryData data() const;

    void updateAttribute(const QString &key, const QVariant &value);
    void setSelected(bool selected);
    virtual QPainterPath shape() const override;

signals:
    void clicked(CountryPolygonItem *item, const QPointF &scenePos);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    void setChildrenBrush(const QBrush &brush);
    void setChildrenPen(const QPen &pen);

    CountryData m_data;
    QBrush m_defaultBrush;
    QPen   m_defaultPen;
    QBrush m_selectedBrush;
    QPen   m_hoverPen;
    QBrush  m_hoverBrush;
    bool   m_isSelected = false;
    QPainterPath m_shape;
};

#endif
