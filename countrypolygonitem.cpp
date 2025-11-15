#include "countrypolygonitem.h"
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPolygonItem>


CountryPolygonItem::CountryPolygonItem(const CountryData &countryData, QGraphicsItem *parent)
    : QObject(nullptr),
    QGraphicsItemGroup(parent),
    m_data(countryData)
{
    m_defaultBrush = QBrush(QColor(0xaed6f1));
    m_selectedBrush = QBrush(QColor(0x3498db));
    m_defaultPen = QPen(QColor(0x1a5276), 0.1);
    m_hoverPen = QPen(QColor(0xb58900), 0.2);
    m_hoverBrush = QBrush(QColor(0xf1c40f));

    QPainterPath tempPath;

    for (const QPolygonF &poly : std::as_const(m_data.m_polygons)) {

        QGraphicsPolygonItem* childPoly = new QGraphicsPolygonItem(poly);
        childPoly->setBrush(m_defaultBrush);
        childPoly->setPen(m_defaultPen);

        this->addToGroup(childPoly);

        tempPath.addPolygon(poly);
    }
    m_shape = tempPath.simplified();
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
        setChildrenBrush(m_selectedBrush);
    } else {
        setChildrenBrush(m_defaultBrush);
    }
}

void CountryPolygonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();

    emit clicked(this, event->scenePos());
}

void CountryPolygonItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    (void)event;
    setChildrenBrush( m_hoverBrush);
    setChildrenPen(m_hoverPen);
}

void CountryPolygonItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    (void)event;
    if (m_isSelected) {
        setChildrenBrush(m_selectedBrush);
    } else {
        setChildrenBrush(m_defaultBrush);
    }
    setChildrenPen(m_defaultPen);
}

void CountryPolygonItem::updateAttribute(const QString &key, const QVariant &value)
{
    m_data.m_attributes.insert(key, value);
}

void CountryPolygonItem::setChildrenBrush(const QBrush &brush)
{
    for (QGraphicsItem* item : this->childItems()) {
        QGraphicsPolygonItem* polyItem = qgraphicsitem_cast<QGraphicsPolygonItem*>(item);
        if (polyItem) {
            polyItem->setBrush(brush);
        }
    }
}
void CountryPolygonItem::setChildrenPen(const QPen &pen)
{
    for (QGraphicsItem* item : this->childItems()) {
        QGraphicsPolygonItem* polyItem = qgraphicsitem_cast<QGraphicsPolygonItem*>(item);
        if (polyItem) {
            polyItem->setPen(pen);
        }
    }
}

QPainterPath CountryPolygonItem::shape() const
{
    return m_shape;
}
