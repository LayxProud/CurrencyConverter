#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    converter = new Converter(this);

    // init comboBoxes
    initCurrencies();

    // Set validator to double only
    QDoubleValidator *validator = new QDoubleValidator(this);
    ui->amountInput->setValidator(validator);

    // save currency names on launch
    firstCurrency = ui->currencyCombo_1->currentText().split(" ").at(0);
    secondCurrency = ui->currencyCombo_2->currentText().split(" ").at(0);

    connect(ui->convertButton, &QPushButton::pressed, this, &MainWindow::onConvertButtonPressed);
    connect(ui->currencyCombo_1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::currencyChanged);
    connect(ui->currencyCombo_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::currencyChanged);

    connect(converter, &Converter::resultReady, this, &MainWindow::showResult);
    connect(converter, &Converter::convertError, this, &MainWindow::convertionError);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initCurrencies()
{
    QStandardItemModel *model = new QStandardItemModel(this);
    model->appendRow(new QStandardItem(tr("RUB / Ruble")));
    model->appendRow(new QStandardItem(tr("USD / Dollar")));
    ui->currencyCombo_1->setModel(model);
    ui->currencyCombo_2->setModel(model);
    ui->currencyCombo_2->setCurrentIndex(1);
}

void MainWindow::onConvertButtonPressed()
{
    double amount = ui->amountInput->text().toDouble();
    std::pair<QString, QString> myPair = std::make_pair(firstCurrency, secondCurrency);
    converter->convert(myPair, amount);
}

void MainWindow::showResult(double result)
{
    QString resultString = QString("%1 %2 = %3 %4")
            .arg(ui->amountInput->text())
            .arg(firstCurrency)
            .arg(QString::number(result))
            .arg(secondCurrency);
    ui->resultLabel->setText(resultString);
}

void MainWindow::currencyChanged()
{
    QComboBox* boxSender = qobject_cast<QComboBox*>(sender()); // recieve which combo box was changed
    if (boxSender == ui->currencyCombo_1)
    {
        if (boxSender->currentIndex() == ui->currencyCombo_2->currentIndex())
        {
            if (ui->currencyCombo_2->currentIndex() - 1 >= 0)
            {
                ui->currencyCombo_2->setCurrentIndex(ui->currencyCombo_2->currentIndex() - 1);
            }
            else
            {
                ui->currencyCombo_2->setCurrentIndex(ui->currencyCombo_2->currentIndex() + 1);
            }
        }
    }
    else if (boxSender == ui->currencyCombo_2)
    {
        if (boxSender->currentIndex() == ui->currencyCombo_1->currentIndex())
        {
            if (ui->currencyCombo_1->currentIndex() - 1 >= 0)
            {
                ui->currencyCombo_1->setCurrentIndex(ui->currencyCombo_1->currentIndex() - 1);
            }
            else
            {
                ui->currencyCombo_1->setCurrentIndex(ui->currencyCombo_1->currentIndex() + 1);
            }
        }
    }

    firstCurrency = ui->currencyCombo_1->currentText().split(" ").at(0);
    secondCurrency = ui->currencyCombo_2->currentText().split(" ").at(0);
}

void MainWindow::convertionError()
{
    QMessageBox::warning(this, tr("Warning"), tr("Something went wrong during conversion"));
}

