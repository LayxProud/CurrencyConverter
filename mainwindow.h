#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDoubleValidator>
#include <QComboBox>
#include <QDebug>

#include "converter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Converter *converter;

    QString firstCurrency;
    QString secondCurrency;

private:
    void initCurrencies();

private slots:
    void onConvertButtonPressed();
    void showResult(double result);
    void currencyChanged();
    void convertionError();
};
#endif // MAINWINDOW_H
