#ifndef GEOJSONPARSER_H
#define GEOJSONPARSER_H

#include <QObject>
#include "countrydata.h"


class GeoJsonParser : public QObject
{
    Q_OBJECT
public:
    explicit GeoJsonParser(QObject *parent = nullptr);

    static QList<CountryData> parse(const QString& filePath);

private:
    static CountryData parseFeature(const QJsonObject& feature);
    static QList<QPolygonF> parseGeometry(const QJsonObject& geometry);
    static QPolygonF parsePolygon(const QJsonArray& coordinates);
    static QList<QPolygonF> parseMultiPolygon(const QJsonArray& coordinates);
};

#endif
