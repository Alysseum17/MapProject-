#include "geojsonparser.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QDebug>

static bool g_debugPrintDone = false;

GeoJsonParser::GeoJsonParser(QObject *parent) : QObject(parent)
{

}

QList<CountryData> GeoJsonParser::parse(const QString& filePath)
{
    QList<CountryData> countries;
    qDebug() << "Starting parser for file:" << filePath;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Failed to open file:" << filePath;
        return countries;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    if (doc.isNull() || !doc.isObject()) {
        qCritical() << "Failed to parse JSON from file.";
        return countries;
    }

    QJsonObject rootObject = doc.object();

    QJsonArray featuresArray = rootObject["features"].toArray();
    qDebug() << "Found" << featuresArray.count() << "features.";

    for (const QJsonValue &featureValue : featuresArray) {
        if (featureValue.isObject()) {
            CountryData country = parseFeature(featureValue.toObject());
            if (!country.m_name.isEmpty()) {
                countries.append(country);
            }
        }
    }

    qDebug() << "Parsing finished. Successfully parsed countries:" << countries.size();
    return countries;
}

CountryData GeoJsonParser::parseFeature(const QJsonObject& feature)
{
    CountryData data;

    QJsonObject properties = feature["properties"].toObject();

    if (!g_debugPrintDone) {
        qDebug() << "===== DEBUG: Property Keys =====";
        qDebug() << properties.keys();
        qDebug() << "================================";
        g_debugPrintDone = true;
    }

    for (auto it = properties.constBegin(); it != properties.constEnd(); ++it) {
        data.m_attributes.insert(it.key(), it.value().toVariant());
    }

     data.m_name = properties["name"].toString();
    QJsonObject geometry = feature["geometry"].toObject();
    if (!geometry.isEmpty()) {
        data.m_polygons = parseGeometry(geometry);
    }

    return data;
}

QList<QPolygonF> GeoJsonParser::parseGeometry(const QJsonObject& geometry)
{
    QString type = geometry["type"].toString();
    QJsonArray coordinates = geometry["coordinates"].toArray();

    if (type == "Polygon") {
        return QList<QPolygonF>() << parsePolygon(coordinates);
    }

    if (type == "MultiPolygon") {
        return parseMultiPolygon(coordinates);
    }

    return QList<QPolygonF>();
}

QPolygonF GeoJsonParser::parsePolygon(const QJsonArray& coordinates)
{
    QPolygonF polygon;
    if (coordinates.isEmpty()) return polygon;

    QJsonArray outerRing = coordinates.at(0).toArray();
    for (const QJsonValue &pointValue : outerRing) {
        QJsonArray point = pointValue.toArray();
        if (point.size() >= 2) {
            polygon.append(QPointF(point.at(0).toDouble(), point.at(1).toDouble()));
        }
    }
    return polygon;
}

QList<QPolygonF> GeoJsonParser::parseMultiPolygon(const QJsonArray& coordinates)
{
    QList<QPolygonF> polygons;
    for (const QJsonValue &polygonValue : coordinates) {
        polygons.append(parsePolygon(polygonValue.toArray()));
    }
    return polygons;
}
