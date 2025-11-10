#ifndef COUNTRYDATA_H
#define COUNTRYDATA_H

#include <QString>
#include <QPolygonF>
#include <QList>
#include <QMap>

struct CountryData
{
    QString m_name;
    QMap<QString, QVariant> m_attributes;
    QList<QPolygonF> m_polygons;
};

#endif
