#include "attributedock.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>


AttributeDock::AttributeDock(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Атрибути країни");
    setupForm();
}

void AttributeDock::setupForm()
{

    QFormLayout *layout = new QFormLayout(this);

    m_countryNameLabel = new QLabel("... (не вибрано)", this);
    m_populationEdit = new QLineEdit(this);
    m_capitalEdit = new QLineEdit(this);
    m_areaEdit = new QLineEdit(this);
    m_currencyEdit = new QLineEdit(this);
    m_saveButton = new QPushButton("Зберегти", this);
    m_closeButton = new QPushButton("Закрити", this);

    layout->addRow("Країна:", m_countryNameLabel);
    layout->addRow("Населення:", m_populationEdit);
    layout->addRow("Столиця:", m_capitalEdit);
    layout->addRow("Площа (км²):", m_areaEdit);
    layout->addRow("Валюта (код):", m_currencyEdit);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_closeButton);
    layout->addRow(buttonLayout);

    connect(m_saveButton, &QPushButton::clicked, this, &AttributeDock::onSaveButtonClicked);
    connect(m_closeButton, &QPushButton::clicked, this, &AttributeDock::onCloseButtonClicked);
}

void AttributeDock::displayCountry(const CountryData &data)
{
    m_countryNameLabel->setText(data.m_name);

    m_populationEdit->setText(data.m_attributes.value("population").toString());
    m_capitalEdit->setText(data.m_attributes.value("capital").toString());
    m_areaEdit->setText(data.m_attributes.value("area").toString());
    m_currencyEdit->setText(data.m_attributes.value("currency").toString());
    m_currentCountryName = data.m_name;
}

void AttributeDock::onSaveButtonClicked()
{
    QString populationText = m_populationEdit->text().trimmed();
    QString capitalText = m_capitalEdit->text().trimmed();
    QString areaText = m_areaEdit->text().trimmed();
    QString currencyText = m_currencyEdit->text().trimmed();


    if (!populationText.isEmpty()) {
        bool isNumberOk;
        populationText.toLongLong(&isNumberOk);

        if (!isNumberOk) {
            QMessageBox::warning(this, "Некоректний ввід",
                                 "Поле 'Населення' має містити лише цифри.");
            return;
        }
    }

    if (!capitalText.isEmpty()) {
        QRegularExpression capitalRegex("^[\\p{L}\\s'-]+$");

        if (!capitalRegex.match(capitalText).hasMatch()) {
            QMessageBox::warning(this, "Некоректний ввід",
                                 "Поле 'Столиця' має містити лише літери або спеціальні символи(пробіл,дефіс,апостроф).");
            return;
        }
    }
    if (!areaText.isEmpty()) {
        bool isAreaOk;
        areaText.toLongLong(&isAreaOk);
        if (!isAreaOk) {
            QMessageBox::warning(this, "Некоректний ввід", "Поле 'Площа' має містити лише цифри.");
            return;
        }
    }

    if (!currencyText.isEmpty()) {
        QRegularExpression currencyRegex("^[A-Z]{3}$");
        if (!currencyRegex.match(currencyText).hasMatch()) {
            QMessageBox::warning(this, "Некоректний ввід", "Код валюти має складатися з 3 великих літер (напр., UAH).");
            return;
        }
    }

    qDebug() << "Save clicked for:" << m_currentCountryName;

    emit attributesSaved(m_currentCountryName,
                         populationText,
                         capitalText,
                         areaText,
                         currencyText);
    accept();
}
void AttributeDock::onCloseButtonClicked()
{
   reject();
}
