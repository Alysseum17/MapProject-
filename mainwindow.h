#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "countrydata.h"
#include "mapview.h"
#include "attributedock.h"
#include "geojsonparser.h"
#include "countrypolygonitem.h"
#include "mapview.h"

class CountryPolygonItem;

class AttributeDock;
class QGraphicsScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onCountryClicked(CountryPolygonItem *item, const QPointF &scenePos);
    void onAttributesSaved(const QString &countryName, const QString &population,
                           const QString &capital, const QString &area, const QString &currency);
    void onAttributeDialogFinished();

private:
    void setupUI();
    void loadMapData();

    AttributeDock *m_attributeDock;
    MapView *m_mapView;
    QGraphicsScene *m_scene;
    CountryPolygonItem* m_selectedItem = nullptr;
    QList<CountryPolygonItem*> m_countryItems;
};
#endif
