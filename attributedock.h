#ifndef ATTRIBUTEDOCK_H
#define ATTRIBUTEDOCK_H

#include <QDialog>
#include "countrydata.h"

class QLineEdit;
class QLabel;
class QPushButton;

class AttributeDock : public QDialog
{
    Q_OBJECT

public:
    explicit AttributeDock(QWidget *parent = nullptr);


public slots:

    void displayCountry(const CountryData &data);

signals:
    void attributesSaved(const QString &countryName, const QString &population,
                         const QString &capital, const QString &area, const QString &currency);

private slots:
    void onSaveButtonClicked();
    void onCloseButtonClicked();


private:
    void setupForm();

    QLabel *m_countryNameLabel;
    QLineEdit *m_populationEdit;
    QLineEdit *m_capitalEdit;
    QLineEdit *m_areaEdit;
    QLineEdit *m_currencyEdit;
    QPushButton *m_saveButton;
    QPushButton *m_closeButton;
    QString m_currentCountryName;
};

#endif
