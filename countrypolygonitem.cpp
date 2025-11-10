#include "countrypolygonitem.h"
#include <QCursor>
#include <QGraphicsSceneMouseEvent>

CountryPolygonItem::CountryPolygonItem(const QPolygonF &polygon, const CountryData &countryData, QGraphicsItem *parent)
    : QObject(nullptr),
    QGraphicsPolygonItem(polygon, parent),
    m_data(countryData)
{
    m_defaultBrush = QBrush(QColor(0xaed6f1));
    m_selectedBrush = QBrush(QColor(0x3498db));
    m_defaultPen = QPen(QColor(0x1a5276));
    m_defaultPen.setWidthF(0.1);

    setBrush(m_defaultBrush);
    setPen(m_defaultPen);

    setAcceptHoverEvents(true);
    setCursor(Qt::PointingHandCursor);
}

CountryData CountryPolygonItem::data() const
{
    return m_data;
}
void CountryPolygonItem::setSelected(bool selected)
{
    m_isSelected = selected;
    if (selected) {
        setBrush(m_selectedBrush);
    } else {
        setBrush(m_defaultBrush);
    }
}

void CountryPolygonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();

    emit clicked(this, event->scenePos());
}

void CountryPolygonItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QBrush(QColor(0xf1c40f)));
    setPen(QPen(QColor(0xb58900), 0.2));
}

void CountryPolygonItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (m_isSelected) {
        setBrush(m_selectedBrush);
        setPen(m_defaultPen);
    } else {
        setBrush(m_defaultBrush);
        setPen(m_defaultPen);
    }
}

void CountryPolygonItem::updateAttribute(const QString &key, const QVariant &value)
{
    m_data.m_attributes.insert(key, value);
}
