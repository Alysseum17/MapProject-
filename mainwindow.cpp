#include "mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsScene>
#include <QDockWidget>
#include <QDebug>
#include <QtGlobal>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    loadMapData();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    setWindowTitle("Variant 20: Country Borders (C++/Qt)");
    setMinimumSize(1024, 768);

    m_scene = new QGraphicsScene(this);
    m_mapView = new MapView(this);
    m_mapView->setScene(m_scene);

    setCentralWidget(m_mapView);

    m_attributeDock = new AttributeDock(this);

    connect(m_attributeDock, &AttributeDock::attributesSaved,
            this, &MainWindow::onAttributesSaved);

    connect(m_attributeDock, &QDialog::finished,
            this, &MainWindow::onAttributeDialogFinished);
}

void MainWindow::loadMapData()
{
    qDebug() << "Loading map data...";
    QList<CountryData> allData = GeoJsonParser::parse(":/countries.geojson");
    if (allData.isEmpty()) {
        qWarning() << "Map data not loaded. Check resources.qrc";
        return;
    }
    m_countryItems.clear();

    for (const CountryData &country : std::as_const(allData)) {

            CountryPolygonItem *item = new CountryPolygonItem(country);

            connect(item, &CountryPolygonItem::clicked,
                    this, &MainWindow::onCountryClicked);

            m_scene->addItem(item);

            m_countryItems.append(item);
    }

    qDebug() << "Map drawing complete!";
    m_mapView->scale(2.5, 2.5);
    m_mapView->centerOn(30.0, 50.0);
}

void MainWindow::onCountryClicked(CountryPolygonItem *item, const QPointF &scenePos)
{
    if (m_selectedItem && m_selectedItem != item) {
        m_selectedItem->setSelected(false);
    }
    item->setSelected(true);
    m_selectedItem = item;

    CountryData data = item->data();
    qDebug() << "Clicked on:" << data.m_name;
    m_attributeDock->displayCountry(data);

    QPoint globalPos = m_mapView->mapToGlobal(m_mapView->mapFromScene(scenePos));

    m_attributeDock->move(globalPos);

    m_attributeDock->show();
}

void MainWindow::onAttributesSaved(const QString &countryName, const QString &population,
                                   const QString &capital, const QString &area, const QString &currency)
{
    qDebug() << "MainWindow received save for:" << countryName;

    for (CountryPolygonItem *item : std::as_const(m_countryItems)) {
        if (item->data().m_name == countryName) {

            item->updateAttribute("population", population);
            item->updateAttribute("capital", capital);
            item->updateAttribute("area", area);
            item->updateAttribute("currency", currency);

            qDebug() << "Data updated in CountryPolygonItem object.";

            break;
        }
    }
}

void MainWindow::onAttributeDialogFinished()
{
    qDebug() << "Dialog closed, deselecting item.";

    if (m_selectedItem) {
        m_selectedItem->setSelected(false);
        m_selectedItem = nullptr;
    }
}
